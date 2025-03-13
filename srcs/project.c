#include "fdf.h"

/*
** ft_rotate_x - X軸周りの回転を適用
** @y: 回転させるY座標
** @z: 回転させるZ座標
** @angle: 回転角度（ラジアン）
**
** Y-Z平面で、指定された角度だけ点を回転させます。
** 回転行列:
** |  1   0      0  |   |x|   |        x        |
** |  0  cos(θ) sin(θ) | * |y| = | y*cos(θ) + z*sin(θ) |
** |  0 -sin(θ) cos(θ) |   |z|   |-y*sin(θ) + z*cos(θ) |
*/
static void	ft_rotate_x(int *y, int *z, double angle)
{
	int	prev_y;

	prev_y = *y;
	*y = prev_y * cos(angle) + *z * sin(angle);
	*z = -prev_y * sin(angle) + *z * cos(angle);
}

/*
** ft_rotate_y - Y軸周りの回転を適用
** @x: 回転させるX座標
** @z: 回転させるZ座標
** @angle: 回転角度（ラジアン）
**
** X-Z平面で、指定された角度だけ点を回転させます。
** 回転行列:
** |  cos(θ)  0  sin(θ) |   |x|   | x*cos(θ) + z*sin(θ) |
** |   0      1   0     | * |y| = |         y         |
** | -sin(θ)  0  cos(θ) |   |z|   |-x*sin(θ) + z*cos(θ) |
*/
static void	ft_rotate_y(int *x, int *z, double angle)
{
	int	prev_x;

	prev_x = *x;
	*x = prev_x * cos(angle) + *z * sin(angle);
	*z = -prev_x * sin(angle) + *z * cos(angle);
}

/*
** ft_rotate_z - Z軸周りの回転を適用（続き）
*/
static void	ft_rotate_z(int *x, int *y, double angle)
{
	int	prev_x;
	int	prev_y;

	prev_x = *x;
	prev_y = *y;
	*x = prev_x * cos(angle) - prev_y * sin(angle);
	*y = prev_x * sin(angle) + prev_y * cos(angle);
}

/*
** ft_isometric - アイソメトリック（等角）投影を適用
** @x: 変換するX座標
** @y: 変換するY座標
** @z: Z座標（高さ）
**
** 3D座標をアイソメトリック表示のための2D座標に変換します。
** アイソメトリック投影では、x軸とy軸は画面上で30度の角度を持ちます。
** 数式: x' = (x - y) * cos(30°), y' = -z + (x + y) * sin(30°)
*/
static void	ft_isometric(int *x, int *y, int z)
{
	int	prev_x;
	int	prev_y;

	prev_x = *x;
	prev_y = *y;
	*x = (prev_x - prev_y) * cos(0.523599);  /* 30度をラジアンで表現 */
	*y = -z + (prev_x + prev_y) * sin(0.523599);
}

/*
** project - マップ上の点を3Dから2D座標に変換
** @x: マップ上のX座標
** @y: マップ上のY座標
** @env: FDF環境構造体
**
** マップの指定位置の点を取得し、必要な変換（スケール、回転、投影）を
** 適用して画面上の座標に変換します。色情報も取得します。
**
** 戻り値: 変換された点の情報（座標と色）
*/
t_point	project(int x, int y, t_fdf *env)
{
	t_point	p;
	int		z;

	p.x = x;  /* 元のX座標を保持 */
	p.y = y;  /* 元のY座標を保持 */
	z = env->map->array[y][x][0];  /* Z座標（高さ）を取得 */
	p.z = z;  /* Z座標を保持 */
	
	/* 点の色を取得（カスタム色があれば使用、なければデフォルト色を計算） */
	p.color = (env->map->array[y][x][1] == -1)
		? get_default_color(z, env->map) : env->map->array[y][x][1];
	
	/* 座標をマップの中心を原点として調整 */
	x -= env->map->width / 2;
	y -= env->map->height / 2;
	
	/* Z値をカメラの高さ設定で調整 */
	z *= env->camera->z_height;
	
	/* カメラのズーム値で座標をスケーリング */
	x *= env->camera->zoom;
	y *= env->camera->zoom;
	z *= env->camera->zoom / 10;  /* Z方向のスケールは縮小 */
	
	/* 3つの軸周りの回転を適用 */
	ft_rotate_x(&y, &z, env->camera->x_angle);
	ft_rotate_y(&x, &z, env->camera->y_angle);
	ft_rotate_z(&x, &y, env->camera->z_angle);
	
	/* アイソメトリック投影を適用（設定されている場合） */
	if (env->camera->iso)
		ft_isometric(&x, &y, z);
	
	/* 画面の中心に表示されるようオフセットを加算 */
	x += WIDTH / 2 + env->camera->x_offset;
	y += HEIGHT / 2 + env->camera->y_offset;
	
	/* 変換後の座標を返す点情報に設定 */
	p.x = x;
	p.y = y;
	
	return (p);
}
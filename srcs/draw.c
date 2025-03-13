#include "fdf.h"

/*
** ft_put_pixel - イメージバッファの指定位置に点を描画
** @env: FDF環境構造体
** @x: X座標
** @y: Y座標
** @color: 描画する色（RGB値）
**
** ウィンドウ内の指定座標にピクセルを描画します。
** 座標がウィンドウ内にあるか確認してからピクセルデータを設定します。
*/
void	ft_put_pixel(t_fdf *env, int x, int y, int color)
{
	int	i;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)  /* ウィンドウ内かチェック */
	{
		/* ピクセルのメモリ位置を計算 */
		i = (x * env->bpp / 8) + (y * env->size_line);
		/* RGBの各バイトを設定 */
		env->data_addr[i] = color;          /* Blue */
		env->data_addr[++i] = color >> 8;   /* Green */
		env->data_addr[++i] = color >> 16;  /* Red */
	}
}

/*
** ft_clear_image - イメージバッファをクリア（黒で塗りつぶし）
** @env: FDF環境構造体
**
** 描画前にイメージバッファをゼロでクリアします（黒色）。
*/
static void	ft_clear_image(t_fdf *env)
{
	ft_bzero(env->data_addr, WIDTH * HEIGHT * (env->bpp / 8));
}

/*
** ft_draw - マップ全体を描画
** @map: マップデータ
** @env: FDF環境構造体
**
** マップ内のすべての点を処理し、グリッドラインを描画します。
** 各点から右と下にラインを引いてグリッドを形成します。
*/
void	ft_draw(t_map *map, t_fdf *env)
{
	int	x;
	int	y;

	ft_clear_image(env);  /* 描画前にイメージをクリア */
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (x < map->width - 1)
				/* 右方向のラインを描画 */
				ft_draw_line(project(x, y, env), project(x + 1, y, env), env);
			if (y < map->height - 1)
				/* 下方向のラインを描画 */
				ft_draw_line(project(x, y, env), project(x, y + 1, env), env);
			x++;
		}
		y++;
	}
	/* 完成したイメージをウィンドウに表示 */
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
}
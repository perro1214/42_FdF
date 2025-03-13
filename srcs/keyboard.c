#include "fdf.h"

/*
** ft_handle_zoom - ズームイン/ズームアウト操作の処理
** @key: 押されたキーのコード
** @env: FDF環境構造体
**
** '+' キーでズームイン、'-' キーでズームアウトします。
** 最小ズームレベルは1に制限されます。
*/
static void	ft_handle_zoom(int key, t_fdf *env)
{
	if (key == PLUS)  /* '+' キー */
		env->camera->zoom += 2;  /* ズームイン */
	else if (key == MINUS)  /* '-' キー */
		env->camera->zoom -= 2;  /* ズームアウト */
		
	/* ズームが1未満にならないようにする */
	if (env->camera->zoom < 1)
		env->camera->zoom = 1;
}

/*
** ft_handle_move - カメラの移動（パン）操作の処理
** @key: 押されたキーのコード
** @env: FDF環境構造体
**
** 矢印キーでマップを上下左右に移動します。
** これはカメラのオフセット値を変更することで実現されます。
*/
static void	ft_handle_move(int key, t_fdf *env)
{
	if (key == ARROW_UP)  /* 上矢印キー */
		env->camera->y_offset -= 10;  /* 上へ移動 */
	else if (key == ARROW_DOWN)  /* 下矢印キー */
		env->camera->y_offset += 10;  /* 下へ移動 */
	else if (key == ARROW_LEFT)  /* 左矢印キー */
		env->camera->x_offset -= 10;  /* 左へ移動 */
	else if (key == ARROW_RIGHT)  /* 右矢印キー */
		env->camera->x_offset += 10;  /* 右へ移動 */
}

/*
** ft_key_press - キーボード押下イベントのハンドラ
** @keycode: 押されたキーのキーコード
** @params: FDF環境構造体へのポインタ
**
** キーボードイベントを処理し、対応するアクションを実行します。
** - ESCキー: プログラムを終了
** - スペース: 投影モード切替（アイソメトリック/平行）
** - Rキー: カメラ設定をリセット
** - +/-キー: ズームイン/ズームアウト
** - 矢印キー: 移動
**
** 戻り値: 常に0（mlx_hookの要求に合わせる）
*/
int	ft_key_press(int keycode, void *params)
{
	t_fdf	*env;

	env = (t_fdf *)params;
	if (keycode == ESCAPE)  /* ESCキーでプログラム終了 */
	{
		mlx_destroy_image(env->mlx, env->img);
		mlx_destroy_window(env->mlx, env->win);
		exit(0);
	}
	else if (keycode == SPACE)  /* スペースで投影モード切替 */
		env->camera->iso = !env->camera->iso;
	else if (keycode == KEY_R)  /* Rキーでカメラリセット */
	{
		env->camera->x_angle = -0.615472907;
		env->camera->y_angle = -0.523599;
		env->camera->z_angle = 0.615472907;
		env->camera->zoom = ft_min(WIDTH / env->map->width / 2,
				HEIGHT / env->map->height / 2);
		env->camera->z_height = 1;
		env->camera->x_offset = 0;
		env->camera->y_offset = 0;
	}
	else if (keycode == PLUS || keycode == MINUS)  /* +/-キーでズーム */
		ft_handle_zoom(keycode, env);
	else if (keycode >= ARROW_LEFT && keycode <= ARROW_UP)  /* 矢印キーで移動 */
		ft_handle_move(keycode, env);
	ft_draw(env->map, env);  /* 変更を反映して再描画 */
	return (0);
}

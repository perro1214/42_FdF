#include "fdf.h"

/*
** ft_mouse_down - マウスボタン押下イベントのハンドラ
** @button: 押されたマウスボタン
** @x: マウスのX座標
** @y: マウスのY座標
** @params: FDF環境構造体へのポインタ
**
** マウスボタンが押されたときの処理を行います。
** - マウスホイール: ズームイン/ズームアウト
** - 左/右ボタン: 押された位置と状態を記録（ドラッグ時の処理のため）
**
** 戻り値: 常に0（mlx_hookの要求に合わせる）
*/
int	ft_mouse_down(int button, int x, int y, void *params)
{
	t_fdf	*env;

	env = (t_fdf *)params;
	if (button == MOUSE_WHEEL_UP)  /* マウスホイール上回転 */
	{
		env->camera->zoom += 2;  /* ズームイン */
		ft_draw(env->map, env);
	}
	else if (button == MOUSE_WHEEL_DOWN)  /* マウスホイール下回転 */
	{
		env->camera->zoom -= 2;  /* ズームアウト */
		if (env->camera->zoom < 1)
			env->camera->zoom = 1;
		ft_draw(env->map, env);
	}
	/* 左/右ボタンが押された場合、その位置を記録 */
	else if (button == MOUSE_CLICK_LEFT || button == MOUSE_CLICK_RIGHT)
	{
		env->mouse->button = button;
		env->mouse->prev_x = x;
		env->mouse->prev_y = y;
	}
	return (0);
}

/*
** ft_mouse_up - マウスボタン解放イベントのハンドラ
** @button: 解放されたマウスボタン
** @x: マウスのX座標（使用しない）
** @y: マウスのY座標（使用しない）
** @params: FDF環境構造体へのポインタ
**
** マウスボタンが放されたときに、ボタン状態をリセットします。
**
** 戻り値: 常に0（mlx_hookの要求に合わせる）
*/
int	ft_mouse_up(int button, int x, int y, void *params)
{
	t_fdf	*env;

	(void)x;  /* 未使用パラメータの警告を抑制 */
	(void)y;
	env = (t_fdf *)params;
	if (button == MOUSE_CLICK_LEFT || button == MOUSE_CLICK_RIGHT)
		env->mouse->button = 0;  /* ボタン状態をリセット */
	return (0);
}

/*
** ft_mouse_move - マウス移動イベントのハンドラ
** @x: 現在のマウスX座標
** @y: 現在のマウスY座標
** @params: FDF環境構造体へのポインタ
**
** マウスが移動したときの処理を行います。
** - 左ボタンドラッグ: モデルの回転
** - 右ボタンドラッグ: マップの移動
**
** 戻り値: 常に0（mlx_hookの要求に合わせる）
*/
int	ft_mouse_move(int x, int y, void *params)
{
	t_fdf	*env;
	int		dx;
	int		dy;

	env = (t_fdf *)params;
	/* ボタンが押されていない場合は何もしない */
	if (!env->mouse->button)
		return (0);
		
	/* 前回位置からの移動量を計算 */
	dx = x - env->mouse->prev_x;
	dy = y - env->mouse->prev_y;
	
	/* 左ボタンドラッグ: モデルを回転 */
	if (env->mouse->button == MOUSE_CLICK_LEFT)
	{
		env->camera->x_angle += dy * 0.002;
		env->camera->y_angle += dx * 0.002;
		ft_draw(env->map, env);
	}
	/* 右ボタンドラッグ: マップを移動 */
	else if (env->mouse->button == MOUSE_CLICK_RIGHT)
	{
		env->camera->x_offset += dx;
		env->camera->y_offset += dy;
		ft_draw(env->map, env);
	}
	
	/* 現在位置を次回のために記録 */
	env->mouse->prev_x = x;
	env->mouse->prev_y = y;
	
	return (0);
}

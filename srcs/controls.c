#include "fdf.h"

/*
** ft_hook_controls - ユーザー入力イベントのフックを設定
** @env: FDF環境構造体
**
** キーボード、マウス、ウィンドウイベントに対応する
** イベントハンドラ関数を登録します。
** このフック設定により、ユーザーはプログラムと対話できるようになります。
*/
void	ft_hook_controls(t_fdf *env)
{
	/* キーボード押下イベントのフック */
	mlx_hook(env->win, 2, 1L << 0, ft_key_press, env);
	
	/* マウスボタン押下イベントのフック */
	mlx_hook(env->win, 4, 1L << 2, ft_mouse_down, env);
	
	/* マウスボタン解放イベントのフック */
	mlx_hook(env->win, 5, 1L << 3, ft_mouse_up, env);
	
	/* マウス移動イベントのフック */
	mlx_hook(env->win, 6, 1L << 6, ft_mouse_move, env);
	
	/* ウィンドウ終了イベントのフック */
	mlx_hook(env->win, 17, 0, ft_close_win, env);
}
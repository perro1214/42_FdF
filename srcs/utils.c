#include "fdf.h"

/*
** エラーメッセージを表示して終了する関数
** system_functionが1の場合はsystem関数エラー(perrorで表示)
** 0の場合は一般エラー
*/
void	ft_return_error(const char *err_msg, int system_function)
{
	if (system_function)
		perror(err_msg);
	else
		ft_putendl_fd((char *)err_msg, 2);
	exit(EXIT_FAILURE);
}

/*
** 二つの整数のうち小さい方を返す関数
*/
int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

/*
** ウィンドウを閉じるイベントハンドラ
** Xボタンが押されたときに呼ばれる
*/
int	ft_close_win(void *params)
{
	t_fdf	*env;

	env = (t_fdf *)params;
	/* 画像とウィンドウのメモリ解放 */
	mlx_destroy_image(env->mlx, env->img);
	mlx_destroy_window(env->mlx, env->win);
	exit(0);
	return (0);
}
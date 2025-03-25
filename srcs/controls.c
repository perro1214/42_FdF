/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhayato@student.42.fr <hhayato>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:40:00 by perro1214         #+#    #+#             */
/*   Updated: 2025/03/25 20:28:03 by hhayato@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

/*
** ft_close - プログラム終了時の処理
*/
int	ft_close(void *param)
{
	t_fdf	*env;

	env = (t_fdf *)param;
	ft_free_env(env);
	exit(0);
	return (0);
}

/*
** key_press - キー入力時の処理
*/
int	key_press(int key, void *param)
{
	t_fdf	*env;

	env = (t_fdf *)param;
	if (key == KEY_ESC)
		ft_close(env);
	return (0);
}

/*
** handle_expose - 再描画イベント時の処理
*/
int	handle_expose(void *param)
{
	t_fdf	*env;

	env = (t_fdf *)param;
	if (!env)
		return (0);
	ft_draw(env->map, env);
	return (0);
}

/*
** hook_controls - イベントフックの設定
*/
void	hook_controls(t_fdf *env)
{
	mlx_hook(env->win, 2, 0, key_press, env);
	mlx_hook(env->win, 17, 0, ft_close, env);
	mlx_expose_hook(env->win, handle_expose, env);
}

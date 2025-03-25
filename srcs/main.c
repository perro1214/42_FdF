/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhayato@student.42.fr <hhayato>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:40:00 by perro1214         #+#    #+#             */
/*   Updated: 2025/03/25 20:28:03 by hhayato@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

/*
** init - 描画環境の初期化
*/
static t_fdf	*init(const char *path)
{
	t_fdf	*env;
	char	*title;

	title = ft_strjoin("FdF - ", path);
	env = (t_fdf *)malloc(sizeof(t_fdf));
	if (!env)
		err_exit("malloc error", 1);
	env->mlx = mlx_init();
	if (!env->mlx)
		err_exit("error connecting to graphics server", 1);
	env->win = mlx_new_window(env->mlx, WIDTH, HEIGHT, title);
	if (!env->win)
		err_exit("error initializing window", 1);
	free(title);
	env->img = mlx_new_image(env->mlx, WIDTH, HEIGHT);
	if (!env->img)
		err_exit("error initializing image", 1);
	env->data_addr = mlx_get_data_addr(env->img, &env->bpp, &env->size_line,
			&env->endian);
	env->map = NULL;
	return (env);
}

/*
** main - プログラムのエントリポイント
*/
int	main(int argc, char *argv[])
{
	t_fdf	*env;

	if (argc == 2)
	{
		env = init(argv[1]);
		env->map = ft_map_init();
		ft_read_map(argv[1], env->map);
		hook_controls(env);
		ft_draw(env->map, env);
		mlx_loop(env->mlx);
	}
	else
		err_exit("Usage: ./fdf <filename>", 0);
	return (0);
}

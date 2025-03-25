/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhayato@student.42.fr <hhayato>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:03:22 by perro1214         #+#    #+#             */
/*   Updated: 2025/03/25 21:02:42 by hhayato@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

/*
** project - 3D座標から2D座標への変換（等角投影）
*/
static void	project(int *x, int *y, int z)
{
	int	previous_x;
	int	previous_y;

	previous_x = *x;
	previous_y = *y;
	*x = (previous_x - previous_y) * cos(0);
	*y = (previous_x + previous_y) * sin(0.8) - z;
}

/*
** setup_p - 点の座標と色を設定
*/
static void	setup_p(t_point *p, int x, int y, t_map *map)
{
	int	z;
	int	zoom;

	zoom = ft_min(WIDTH / map->width / 2, HEIGHT / map->height / 2) * 0.7;
	p->x = x * zoom;
	p->y = y * zoom;
	z = map->array[y][x][0];
	p->z = z * zoom / 10;
	if (map->array[y][x][1] != -1)
		p->color = map->array[y][x][1];
	else
		p->color = get_color(z, map->z_min, map->z_max);
	project(&p->x, &p->y, p->z);
	p->x += WIDTH / 2;
	p->y += HEIGHT / 3;
}

/*
** draw_lns - マップの線を描画
*/
static void	draw_lns(t_map *map, t_fdf *env, int x, int y)
{
	t_point	p1;
	t_point	p2;

	setup_p(&p1, x, y, map);
	if (x < map->width - 1)
	{
		setup_p(&p2, x + 1, y, map);
		draw_line(p1, p2, env);
	}
	if (y < map->height - 1)
	{
		setup_p(&p2, x, y + 1, map);
		draw_line(p1, p2, env);
	}
}

/*
** draw_map - マップ全体の描画
*/
static void	draw_map(t_map *map, t_fdf *env)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			draw_lns(map, env, x, y);
			x++;
		}
		y++;
	}
}

/*
** ft_draw - マップの描画処理
*/
void	ft_draw(t_map *map, t_fdf *env)
{
	if (!map || !env || !env->mlx || !env->win || !env->img)
		return ;
	ft_clear_img(env);
	draw_map(map, env);
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: perro1214 <perro1214@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-24 12:03:22 by perro1214         #+#    #+#             */
/*   Updated: 2025-03-24 12:03:22 by perro1214        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

/*
** ft_clear_image - 画像を黒でクリア
*/
static void	ft_clear_image(t_fdf *env)
{
	int	i;
	int	*img;
	int	max;

	img = (int *)(env->data_addr);
	max = WIDTH * HEIGHT;
	i = 0;
	while (i < max)
		img[i++] = 0;
}

/*
** ft_project - 3D座標から2D座標への変換（等角投影）
*/
static void	ft_project(int *x, int *y, int z)
{
	int	previous_x;
	int	previous_y;

	previous_x = *x;
	previous_y = *y;
	*x = (previous_x - previous_y) * cos(0);
	*y = (previous_x + previous_y) * sin(0.8) - z;
}

/*
** ft_setup_point - 点の座標と色を設定
*/
static void	ft_setup_point(t_point *p, int x, int y, t_map *map)
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
		p->color = ft_get_color_by_height(z, map->z_min, map->z_max);
	
	ft_project(&p->x, &p->y, p->z);
	p->x += WIDTH / 2;
	p->y += HEIGHT / 3;
}

/*
** ft_draw_lines - マップの線を描画
*/
static void	ft_draw_lines(t_map *map, t_fdf *env, int x, int y)
{
	t_point	p1;
	t_point	p2;

	ft_setup_point(&p1, x, y, map);
	
	if (x < map->width - 1)
	{
		ft_setup_point(&p2, x + 1, y, map);
		ft_draw_line(p1, p2, env);
	}
	
	if (y < map->height - 1)
	{
		ft_setup_point(&p2, x, y + 1, map);
		ft_draw_line(p1, p2, env);
	}
}

/*
** ft_draw_map - マップ全体の描画
*/
static void	ft_draw_map(t_map *map, t_fdf *env)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			ft_draw_lines(map, env, x, y);
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
	ft_clear_image(env);
	ft_draw_map(map, env);
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
}

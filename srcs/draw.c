/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: perro1214 <perro1214@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-17 17:40:00 by perro1214         #+#    #+#             */
/*   Updated: 2025-03-17 17:40:00 by perro1214        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

/*
** ft_put_pixel - ピクセルを描画
*/
void	ft_put_pixel(t_fdf *env, int x, int y, int color)
{
	int	i;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		i = (y * env->size_line + x * (env->bpp / 8));
		env->data_addr[i] = color;
		env->data_addr[++i] = color >> 8;
		env->data_addr[++i] = color >> 16;
	}
}

/*
** ft_calculate_delta - 線を描画するための差分を計算
*/
static void	ft_calculate_delta(int *delta, int start, int end)
{
	*delta = end - start;
	if (*delta < 0)
		*delta = -*delta;
}

/*
** ft_get_sign - 増加・減少の方向を決定
*/
static int	ft_get_sign(int start, int end)
{
	if (start < end)
		return (1);
	return (-1);
}

/*
** ft_draw_line - ブレゼンハムアルゴリズムで線を描画
*/
/*
** ft_draw_line - ブレゼンハムアルゴリズムで線を描画
*/
void	ft_draw_line(t_point p1, t_point p2, t_fdf *env)
{
	int	delta_x;
	int	delta_y;
	int	sign_x;
	int	sign_y;
	int	error;
	int	error2;

	ft_calculate_delta(&delta_x, p1.x, p2.x);
	ft_calculate_delta(&delta_y, p1.y, p2.y);
	sign_x = ft_get_sign(p1.x, p2.x);
	sign_y = ft_get_sign(p1.y, p2.y);
	error = delta_x - delta_y;
	ft_put_pixel(env, p2.x, p2.y, p2.color);
	while (p1.x != p2.x || p1.y != p2.y)
	{
		ft_put_pixel(env, p1.x, p1.y, p1.color);
		error2 = error * 2;
		if (error2 > -delta_y)
		{
			error -= delta_y;
			p1.x += sign_x;
		}
		if (error2 < delta_x)
		{
			error += delta_x;
			p1.y += sign_y;
		}
	}
}

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
** ft_draw_map - マップ全体の描画
*/
static void	ft_draw_map(t_map *map, t_fdf *env)
{
	int		x;
	int		y;
	t_point	p1;
	t_point	p2;
	int		zoom;

	zoom = ft_min(WIDTH / map->width / 2, HEIGHT / map->height / 2) * 1;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			p1.x = x * zoom;
			p1.y = y * zoom;
			p1.z = map->array[y][x][0] * zoom / 10;
			
			// 色の設定：マップファイルで色が指定されていなければ高さに基づいた色を設定
			if (map->array[y][x][1] != -1)
				p1.color = map->array[y][x][1];
			else
				p1.color = ft_get_color_by_height(map->array[y][x][0], map->z_min, map->z_max);
			
			ft_project(&p1.x, &p1.y, p1.z);
			p1.x += WIDTH / 2;
			p1.y += HEIGHT / 2;
			
			if (x < map->width - 1)
			{
				p2.x = (x + 1) * zoom;
				p2.y = y * zoom;
				p2.z = map->array[y][x + 1][0] * zoom / 10;
				
				// 色の設定：マップファイルで色が指定されていなければ高さに基づいた色を設定
				if (map->array[y][x + 1][1] != -1)
					p2.color = map->array[y][x + 1][1];
				else
					p2.color = ft_get_color_by_height(map->array[y][x + 1][0], map->z_min, map->z_max);
				
				ft_project(&p2.x, &p2.y, p2.z);
				p2.x += WIDTH / 2;
				p2.y += HEIGHT / 2;
				ft_draw_line(p1, p2, env);
			}
			
			if (y < map->height - 1)
			{
				p2.x = x * zoom;
				p2.y = (y + 1) * zoom;
				p2.z = map->array[y + 1][x][0] * zoom / 10;
				
				// 色の設定：マップファイルで色が指定されていなければ高さに基づいた色を設定
				if (map->array[y + 1][x][1] != -1)
					p2.color = map->array[y + 1][x][1];
				else
					p2.color = ft_get_color_by_height(map->array[y + 1][x][0], map->z_min, map->z_max);
				
				ft_project(&p2.x, &p2.y, p2.z);
				p2.x += WIDTH / 2;
				p2.y += HEIGHT / 2;
				ft_draw_line(p1, p2, env);
			}
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

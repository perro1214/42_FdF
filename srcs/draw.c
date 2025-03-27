/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhayato@student.42.fr <hhayato>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:40:00 by perro1214         #+#    #+#             */
/*   Updated: 2025/03/27 19:55:01 by hhayato@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	ft_clear_img(t_fdf *env)
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

void	put_pixel(t_fdf *env, int x, int y, int color)
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

static void	calc_delta(int *delta, int start, int end)
{
	*delta = end - start;
	if (*delta < 0)
		*delta = -*delta;
}

static int	ft_get_sign(int start, int end)
{
	if (start < end)
		return (1);
	return (-1);
}

void	draw_line(t_point p1, t_point p2, t_fdf *env)
{
	int	delta_x;
	int	delta_y;
	int	error;
	int	error2;

	calc_delta(&delta_x, p1.x, p2.x);
	calc_delta(&delta_y, p1.y, p2.y);
	error = delta_x - delta_y;
	put_pixel(env, p2.x, p2.y, p2.color);
	while (p1.x != p2.x || p1.y != p2.y)
	{
		put_pixel(env, p1.x, p1.y, p1.color);
		error2 = error * 2;
		if (error2 > -delta_y)
		{
			error -= delta_y;
			p1.x += ft_get_sign(p1.x, p2.x);
		}
		if (error2 < delta_x)
		{
			error += delta_x;
			p1.y += ft_get_sign(p1.y, p2.y);
		}
	}
}

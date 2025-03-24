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

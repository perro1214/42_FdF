/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhayato@student.42.fr <hhayato>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 20:30:41 by hhayato@stu       #+#    #+#             */
/*   Updated: 2025/03/25 20:57:20 by hhayato@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static int	get_comp(int start, int end, double percentage)
{
	return (start + (int)((end - start) * percentage));
}

static int	get_grad(int s_color, int end_color, double percentage)
{
	int	r;
	int	g;
	int	b;

	r = get_comp((s_color >> 16) & 0xFF, (end_color >> 16) & 0xFF, percentage);
	g = get_comp((s_color >> 8) & 0xFF, (end_color >> 8) & 0xFF, percentage);
	b = get_comp(s_color & 0xFF, end_color & 0xFF, percentage);
	return ((r << 16) | (g << 8) | b);
}

int	get_color(int z, int z_min, int z_max)
{
	double	percentage;
	int		color;

	if (z_max == z_min)
		return (0x00FFFFFF);
	percentage = (double)(z - z_min) / (z_max - z_min);
	if (percentage < 0.2)
		color = get_grad(0x0000FF, 0x00FFFF, percentage * 5);
	else if (percentage < 0.4)
		color = get_grad(0x00FFFF, 0x00FF00, (percentage - 0.2) * 5);
	else if (percentage < 0.6)
		color = get_grad(0x00FF00, 0xFFFF00, (percentage - 0.4) * 5);
	else if (percentage < 0.8)
		color = get_grad(0xFFFF00, 0xFF7F00, (percentage - 0.6) * 5);
	else
		color = get_grad(0xFF7F00, 0xFF0000, (percentage - 0.8) * 5);
	return (color);
}

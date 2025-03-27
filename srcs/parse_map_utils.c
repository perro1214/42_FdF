/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhayato@student.42.fr <hhayato>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 21:05:12 by hhayato@stu       #+#    #+#             */
/*   Updated: 2025/03/27 19:55:41 by hhayato@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <limits.h>

t_map	*ft_map_init(void)
{
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		err_exit("error initializing map", 1);
	map->width = 0;
	map->height = 0;
	map->array = NULL;
	map->z_max = 0;
	map->z_min = 0;
	return (map);
}

void	update_row_min_max(t_map *map, int y)
{
	int	x;
	int	z;

	x = -1;
	while (++x < map->width)
	{
		if (map->array[y] && map->array[y][x])
		{
			z = map->array[y][x][0];
			if (z < map->z_min)
			{
				map->z_min = z;
			}
			if (z > map->z_max)
			{
				map->z_max = z;
			}
		}
	}
}

void	set_min_max(t_map *map)
{
	int	y;

	if (!map || !map->array)
		return ;
	map->z_min = INT_MAX;
	map->z_max = INT_MIN;
	y = -1;
	while (++y < map->height)
	{
		update_row_min_max(map, y);
	}
	if (map->z_min == map->z_max)
	{
		map->z_min = 0;
		map->z_max = 1;
	}
}

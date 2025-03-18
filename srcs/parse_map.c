/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: perro1214 <perro1214@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-17 17:40:00 by perro1214         #+#    #+#             */
/*   Updated: 2025-03-17 17:40:00 by perro1214        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <limits.h>

/*
** ft_map_init - マップ構造体の初期化
*/
t_map	*ft_map_init(void)
{
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		ft_return_error("error initializing map", 1);
	map->width = 0;
	map->height = 0;
	map->array = NULL;
	map->z_max = 0;
	map->z_min = 0;
	return (map);
}

/*
** ft_set_min_max_z - マップ内のZ値の最小値と最大値を設定
*/
static void	ft_set_min_max_z(t_map *map)
{
	int	x;
	int	y;
	int	z;

	if (!map || !map->array)
		return ;
	map->z_min = INT_MAX;
	map->z_max = INT_MIN;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->array[y] && map->array[y][x])
			{
				z = map->array[y][x][0];
				if (z < map->z_min)
					map->z_min = z;
				if (z > map->z_max)
					map->z_max = z;
			}
			x++;
		}
		y++;
	}
	if (map->z_min == map->z_max)
	{
		map->z_min = 0;
		map->z_max = (map->z_min == 0) ? 1 : map->z_min;
	}
}

/*
** ft_simple_read_map - マップファイル読み込み関数
*/
void	ft_simple_read_map(char *filename, t_map *map)
{
	FILE	*file;
	char	line[1024];
	int		i;
	int		j;
	char	**split;

	file = fopen(filename, "r");
	if (!file)
		ft_return_error("Error opening file", 1);
	map->height = 0;
	while (fgets(line, sizeof(line), file))
		map->height++;
	if (map->height <= 0)
		ft_return_error("Empty map file", 0);
	rewind(file);
	if (!fgets(line, sizeof(line), file))
		ft_return_error("Failed to read first line", 1);
	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	line[i] = '\0';
	split = ft_split(line, ' ');
	if (!split)
		ft_return_error("Memory allocation error", 1);
	map->width = 0;
	while (split[map->width])
		map->width++;
	ft_split_free(split);
	map->array = (int ***)malloc(sizeof(int **) * map->height);
	if (!map->array)
		ft_return_error("Memory allocation error", 1);
	for (i = 0; i < map->height; i++)
	{
		map->array[i] = (int **)malloc(sizeof(int *) * map->width);
		if (!map->array[i])
			ft_return_error("Memory allocation error", 1);
		for (j = 0; j < map->width; j++)
		{
			map->array[i][j] = (int *)malloc(sizeof(int) * 2);
			if (!map->array[i][j])
				ft_return_error("Memory allocation error", 1);
			map->array[i][j][0] = 0;
			map->array[i][j][1] = -1;
		}
	}
	rewind(file);
	i = 0;
	while (i < map->height && fgets(line, sizeof(line), file))
	{
		j = 0;
		while (line[j] && line[j] != '\n')
			j++;
		line[j] = '\0';
		split = ft_split(line, ' ');
		if (!split)
			ft_return_error("Memory allocation error", 1);
		for (j = 0; j < map->width && split[j]; j++)
		{
			map->array[i][j][0] = ft_atoi(split[j]);
			char *color_ptr = ft_strchr(split[j], ',');
			if (color_ptr)
				map->array[i][j][1] = ft_atoi_base(color_ptr + 1, 16);
		}
		ft_split_free(split);
		i++;
	}
	fclose(file);
	ft_set_min_max_z(map);
}

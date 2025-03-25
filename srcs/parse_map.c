/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhayato@student.42.fr <hhayato>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:03:22 by perro1214         #+#    #+#             */
/*   Updated: 2025/03/25 20:26:53 by hhayato@stu      ###   ########.fr       */
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
		err_exit("error initializing map", 1);
	map->width = 0;
	map->height = 0;
	map->array = NULL;
	map->z_max = 0;
	map->z_min = 0;
	return (map);
}

/*
** set_min_max - マップ内のZ値の最小値と最大値を設定
*/
static void	set_min_max(t_map *map)
{
	int	x;
	int	y;
	int	z;

	if (!map || !map->array)
		return ;
	map->z_min = INT_MAX;
	map->z_max = INT_MIN;
	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width)
		{
			if (map->array[y] && map->array[y][x])
			{
				z = map->array[y][x][0];
				map->z_min = (z < map->z_min) ? z : map->z_min;
				map->z_max = (z > map->z_max) ? z : map->z_max;
			}
		}
	}
	if (map->z_min == map->z_max)
		map->z_min = 0, map->z_max = (map->z_min == 0) ? 1 : map->z_min;
}


static int read_first(FILE *file, t_map *map, char *line)
{
    int i = -1;
    char **split;

    if (!fgets(line, 1024, file)) {
        return (0); // Indicate failure
    }
    while (line[++i] && line[i] != '\n');
    line[i] = '\0';

    split = ft_split(line, ' ');
    if (!split) {
        return (0); // Indicate failure
    }

    map->width = 0;
    while (split[map->width]) {
        map->width++;
    }
    free_split(split);
    return (1); // Indicate success
}

/*
** count_dim - マップの幅と高さを計測する
*/
static void	count_dim(char *filename, t_map *map)
{
	FILE	*file;
	char	line[1024];

	file = fopen(filename, "r");
	if (!file)
		err_exit("Error opening file", 1);
	map->height = 0;
	while (fgets(line, sizeof(line), file))
		map->height++;
	if (map->height <= 0)
	{
		fclose(file); // Close file before returning error.
		err_exit("Empty map file", 0);
	}
	rewind(file);
    if(!read_first(file, map, line))
    {
        fclose(file);
        err_exit("Error processing first line", 1);
    }

	fclose(file);
}

/*
** alloc_arr - マップ配列のメモリを確保
*/
static void	alloc_arr(t_map *map)
{
	int	i;
	int	j;

	map->array = (int ***)malloc(sizeof(int **) * map->height);
	if (!map->array)
		err_exit("Memory allocation error", 1);
	i = 0;
	while (i < map->height)
	{
		map->array[i] = (int **)malloc(sizeof(int *) * map->width);
		if (!map->array[i])
			err_exit("Memory allocation error", 1);
		j = 0;
		while (j < map->width)
		{
			map->array[i][j] = (int *)malloc(sizeof(int) * 2);
			if (!map->array[i][j])
				err_exit("Memory allocation error", 1);
			map->array[i][j][0] = 0;
			map->array[i][j][1] = -1;
			j++;
		}
		i++;
	}
}

/*
** parse_line - マップの1行を解析
*/
static void	parse_line(char *line, int y, t_map *map)
{
	char	**split;
	char	*color_ptr;
	int		j;

	split = ft_split(line, ' ');
	if (!split)
		err_exit("Memory allocation error", 1);
	j = 0;
	while (j < map->width && split[j])
	{
		map->array[y][j][0] = ft_atoi(split[j]);
		color_ptr = ft_strchr(split[j], ',');
		if (color_ptr)
			map->array[y][j][1] = ft_atoi_base(color_ptr + 1, 16);
		j++;
	}
	free_split(split);
}

/*
** ft_read_map - マップファイル読み込み関数
*/
void	ft_read_map(char *filename, t_map *map)
{
	FILE	*file;
	char	line[1024];
	int		i;
	int		j;

	count_dim(filename, map);
	alloc_arr(map);
	file = fopen(filename, "r");
	if (!file)
		err_exit("Error opening file", 1);
	i = 0;
	while (i < map->height && fgets(line, sizeof(line), file))
	{
		j = 0;
		while (line[j] && line[j] != '\n')
			j++;
		line[j] = '\0';
		parse_line(line, i, map);
		i++;
	}
	fclose(file);
	set_min_max(map);
}

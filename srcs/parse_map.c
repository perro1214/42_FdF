/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhayato <hhayato@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:03:22 by perro1214         #+#    #+#             */
/*   Updated: 2025/03/27 17:17:10 by hhayato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <limits.h>

static int	read_first(FILE *file, t_map *map, char *line)
{
	int		i;
	char	**split;

	i = -1;
	if (!fgets(line, 65536, file))
		return (0);
	while (line[++i] && line[i] != '\n')
		;
	line[i] = '\0';
	split = ft_split(line, ' ');
	if (!split)
		return (0);
	map->width = 0;
	while (split[map->width])
		map->width++;
	free_split(split);
	return (1);
}

/*
** count_dim - マップの幅と高さを計測する
*/
static void	count_dim(char *filename, t_map *map)
{
	FILE	*file;
	char	line[65536];

	file = fopen(filename, "r");
	if (!file)
		err_exit("Error opening file", 1);
	map->height = 0;
	while (fgets(line, sizeof(line), file))
		map->height++;
	if (map->height <= 0)
	{
		fclose(file);
		err_exit("Empty map file", 0);
	}
	rewind(file);
	if (!read_first(file, map, line))
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
	char	line[65536];
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

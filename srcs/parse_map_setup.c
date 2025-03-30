/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_setup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhayato@student.42.fr <hhayato>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: [Date] by [Author]                    #+#    #+#             */
/*   Updated: [Date] by [Author]                    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h" // fdf.h に dimension/allocation 関数の宣言が必要
#include <fcntl.h>
#include <unistd.h>

// Function 1 (Helper for counting dimensions)
static int	get_width_from_line(char *line)
{
	char	**split;
	int		width;

	width = 0;
	if (!line) // Avoid splitting NULL
		return (0);
	split = ft_split(line, ' ');
	if (!split) // Handle split error more locally
	{
		free(line); // Free line if split failed
		err_exit("Split error during dimension check", 1);
	}
	while (split[width])
		width++;
	free_split(split);
	return (width);
}

// Function 2 (Core dimension counting logic)
// Checks dimensions and width consistency. Returns 1 on success, 0 on failure.
// Errors are printed via err_exit. map->width/height are set on success.
int	check_map_dimensions(char *filename, t_map *map)
{
	int		fd;
	char	*line;
	int		width_check;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		err_exit("Error opening file for dimension check", 1);
	map->width = 0;
	map->height = 0;
	line = get_next_line(fd);
	map->width = get_width_from_line(line); // Also frees line on split error
	if (!line || map->width == 0) // Check if first line was valid
		return (free(line), close(fd), err_exit("Invalid or empty first line", 0), 0);
	free(line);
	map->height = 1;
	while ((line = get_next_line(fd)) != NULL)
	{
		map->height++;
		width_check = get_width_from_line(line); // Also frees line on split error
		free(line);
		if (width_check != map->width)
			return (close(fd), err_exit("Inconsistent line width", 0), 0);
	}
	close(fd);
	if (map->height == 0) // Should be caught earlier, but safeguard
		return (err_exit("Map appears empty after check", 0), 0);
	return (1); // Dimensions are consistent
}

// Function 3 (Helper for freeing partial allocations)
static void	free_partial_allocation(t_map *map, int failed_row, int failed_col)
{
	int	r;
	int	c;

	r = failed_row;
	while (r >= 0)
	{
		if (map->array[r])
		{
			c = (r == failed_row) ? failed_col : map->width - 1;
			while (c >= 0)
			{
				if (map->array[r][c])
					free(map->array[r][c]);
				c--;
			}
			free(map->array[r]);
		}
		r--;
	}
	free(map->array);
	map->array = NULL;
	err_exit("Memory allocation error", 1); // Exit after cleanup
}

// Function 4 (Helper for allocating points in a row)
static void	allocate_points_for_row(t_map *map, int y)
{
	int	x;

	x = 0;
	while (x < map->width)
	{
		map->array[y][x] = (int *)malloc(sizeof(int) * 2);
		if (!map->array[y][x])
			free_partial_allocation(map, y, x - 1);
		map->array[y][x][0] = 0;
		map->array[y][x][1] = -1;
		x++;
	}
}

void	allocate_map_array(t_map *map)
{
	int	y;

	if (map->height <= 0 || map->width <= 0) // Pre-check
		err_exit("Invalid dimensions for allocation", 1);
	map->array = (int ***)malloc(sizeof(int **) * map->height);
	if (!map->array)
		err_exit("Memory allocation error for rows", 1);
	y = 0;
	while (y < map->height)
	{
		map->array[y] = (int **)malloc(sizeof(int *) * map->width);
		if (!map->array[y])
			free_partial_allocation(map, y - 1, -1);
		allocate_points_for_row(map, y);
		y++;
	}
}

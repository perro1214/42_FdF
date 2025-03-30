/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhayato@student.42.fr <hhayato>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:03:22 by perro1214         #+#    #+#             */
/*   Updated: 2025/03/30 12:50:39 by hhayato@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <limits.h>

// Function 1 (Helper for parsing color)
static int	get_color_from_string(char *str_segment)
{
	char	*color_ptr;

	color_ptr = ft_strchr(str_segment, ',');
	if (color_ptr)
		return (ft_atoi_base(color_ptr + 1, 16));
	return (-1); // No color specified, use default flag
}

// Function 2 (Helper for parsing a single line into the map array)
static void	parse_line_data(char *line, int y, t_map *map)
{
	char	**split;
	int		x;

	split = ft_split(line, ' ');
	if (!split)
		err_exit("Memory allocation error during parsing", 1); // Consider cleanup?
	x = 0;
	while (x < map->width && split[x])
	{
		map->array[y][x][0] = ft_atoi(split[x]);
		map->array[y][x][1] = get_color_from_string(split[x]);
		x++;
	}
	// Ensure the correct number of values were read for the line
	if (x != map->width || split[x] != NULL)
	{
		free_split(split);
		// Dimension check should catch this, but safeguard
		err_exit("Inconsistent data in map line during parsing", 1);
	}
	free_split(split);
}

// Function 3 (Helper to read file and populate allocated array)
static void	read_and_populate_data(int fd, t_map *map)
{
	char	*line;
	int		y;

	y = 0;
	while (y < map->height)
	{
		line = get_next_line(fd);
		if (!line) // Handle unexpected EOF or read error
		{
			// Don't close fd here, caller (ft_read_map) will
			ft_free_map(map); // Free map memory allocated previously
			err_exit("Error reading map data or unexpected EOF", 1);
		}
		parse_line_data(line, y, map);
		free(line); // Free the line from get_next_line
		y++;
	}
	// Optional: Check for and ignore any extra lines
	line = get_next_line(fd);
	if (line != NULL)
		free(line);
}

// Function 4 (Main public function to read the map)
// Orchestrates dimension check, allocation, and data reading.
void	ft_read_map(char *filename, t_map *map)
{
	int	fd;

	// Phase 1: Check dimensions (function from parse_map_setup.c)
	if (!check_map_dimensions(filename, map))
		return; // Error handled within the function

	// Phase 2: Allocate memory (function from parse_map_setup.c)
	allocate_map_array(map);

	// Phase 3: Open file again and read data
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_free_map(map); // Free allocated array if open fails
		err_exit("Error opening file (second time)", 1);
	}
	read_and_populate_data(fd, map); // (Function from this file)
	close(fd);

	// Phase 4: Calculate min/max z (Assuming set_min_max exists elsewhere)
	set_min_max(map);
}

// Function 5: (Empty Slot) - Could place set_min_max here if moved
// void	set_min_max(t_map *map) { ... } // Example if moved
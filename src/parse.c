#include "fdf.h"

static void	close_terminal(int fd, char *line)
{
	close(fd);
	terminate(line);
}

static void	free_close_terminal(int fd, char *error, char *line)
{
	free(line);
	close(fd);
	terminate(error);
}

static int	process_map_lines(t_fdf *fdf, int fd, char *line, int y)
{
	while (y < fdf->map_height && line)
	{
		if (line[0] == '\n' || line[0] == '\0')
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (fill_grid_row(y, line, fdf) != 0)
		{
			cleanup(fdf);
			free_close_terminal(fd, "Error: Inconsistent map width found",
				line);
		}
		free(line);
		y++;
		if (y < fdf->map_height)
			line = get_next_line(fd);
		else
			line = NULL;
	}
	if (line)
		free(line);
	return (y);
}

static void	parse_map1(t_fdf *fdf, int fd, char *line)
{
	int	processed_lines;

	allocate_grids(fdf);
	processed_lines = process_map_lines(fdf, fd, line, 0);
	close(fd);
	if (processed_lines != fdf->map_height)
	{
		cleanup(fdf);
		terminate("Error: Actual line count differs from initial count");
	}
	find_z_min_max(fdf);
}

/* @brief Reads map file, validates dimensions, and fills grids */
void	parse_map(const char *filename, t_fdf *fdf)
{
	int		fd;
	char	*line;

	fdf->map_height = count_lines(filename);
	if (fdf->map_height <= 0)
		terminate("Error: Map file is empty or unreadable");
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		terminate("Error: Failed to open map file for parsing");
	line = get_next_line(fd);
	if (!line)
		close_terminal(fd, "Error: Failed to read first line");
	while (line && (line[0] == '\n' || line[0] == '\0'))
	{
		free(line);
		line = get_next_line(fd);
	}
	if (!line)
		close_terminal(fd, "Error: No valid data lines found in map");
	fdf->map_width = get_map_width(line);
	if (fdf->map_width <= 0)
		free_close_terminal(fd, "Error: Invalid map width on first data line",
			line);
	parse_map1(fdf, fd, line);
}

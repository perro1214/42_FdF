#include "fdf.h"

int	get_map_width(char *line)
{
	int		width;
	char	**numbers;

	numbers = ft_split(line, ' ');
	if (!numbers)
		terminate("Error: ft_split failed in get_map_width");
	width = 0;
	while (numbers[width] && numbers[width][0] != '\n'
		&& numbers[width][0] != '\0')
		width++;
	free_split(numbers);
	return (width);
}

int	count_lines(const char *filename)
{
	int		fd;
	int		height;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		terminate("Error: Failed to open map file");
	height = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (line[0] != '\n' && line[0] != '\0')
			height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (height);
}

void	allocate_grids(t_fdf *fdf)
{
	int	i;

	fdf->z_grid = (int **)ft_calloc(fdf->map_height, sizeof(int *));
	fdf->color_grid = (int **)ft_calloc(fdf->map_height, sizeof(int *));
	if (!fdf->z_grid || !fdf->color_grid)
		terminate("Error: Malloc failed for grid rows");
	i = 0;
	while (i < fdf->map_height)
	{
		fdf->z_grid[i] = (int *)ft_calloc(fdf->map_width, sizeof(int));
		fdf->color_grid[i] = (int *)ft_calloc(fdf->map_width, sizeof(int));
		if (!fdf->z_grid[i] || !fdf->color_grid[i])
		{
			while (--i >= 0)
			{
				free(fdf->z_grid[i]);
				free(fdf->color_grid[i]);
			}
			free(fdf->z_grid);
			free(fdf->color_grid);
			terminate("Error: Malloc failed for grid columns");
		}
		i++;
	}
}

static void	fill_grids_from_split(char **values, int y, t_fdf *fdf)
{
	char	*color_str;
	int		x;

	x = 0;
	while (x < fdf->map_width)
	{
		fdf->z_grid[y][x] = ft_atoi(values[x]);
		color_str = ft_strchr(values[x], ',');
		if (color_str)
		{
			fdf->color_grid[y][x] = ft_atoi_hex(color_str + 1);
		}
		else
		{
			fdf->color_grid[y][x] = -1;
		}
		x++;
	}
	free_split(values);
}

int	fill_grid_row(int y, char *line, t_fdf *fdf)
{
	char	**values;
	int		actual_width;

	values = ft_split(line, ' ');
	if (!values)
		terminate("Error: ft_split failed while filling grid");
	actual_width = 0;
	while (values[actual_width] && values[actual_width][0] != '\n'
		&& values[actual_width][0] != '\0')
		actual_width++;
	if (actual_width != fdf->map_width)
	{
		free_split(values);
		ft_putendl_fd("Error: Map line has inconsistent width", STDERR_FILENO);
		return (1);
	}
	fill_grids_from_split(values, y, fdf);
	return (0);
}

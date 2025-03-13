#include "fdf.h"
#include <limits.h> /* INT_MAX, INT_MIN用に明示的に含める */

static int	ft_get_height(char *filename)
{
	char	*line;
	int		fd;
	int		height;

	height = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		ft_return_error("Error opening file", 1);
	/* get_next_lineの使用方法を修正 */
	line = get_next_line(fd);
	while (line != NULL)
	{
		height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (height);
}

static int	ft_get_width(char *filename)
{
	char	*line;
	int		fd;
	int		width;
	char	**split;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		ft_return_error("Error opening file", 1);
	/* get_next_lineの使用方法を修正 */
	line = get_next_line(fd);
	if (!line)
		ft_return_error("Empty file", 0);
	split = ft_split(line, ' ');
	width = 0;
	while (split[width])
		width++;
	free(line);
	while (split[width - 1] && !ft_strlen(split[width - 1]))
		width--;
	ft_split_free(split);
	close(fd);
	return (width);
}

static void	ft_fill_map(int *data_line, char *line, int width)
{
	char	**split;
	int		i;
	char	*ptr;

	split = ft_split(line, ' ');
	i = 0;
	while (i < width && split[i])
	{
		data_line[i] = ft_atoi(split[i]);
		ptr = ft_strchr(split[i], ',');
		if (ptr)
			data_line[i + width] = ft_atoi_base(ptr + 1, 16);
		else
			data_line[i + width] = -1;
		i++;
	}
	ft_split_free(split);
}

static void	ft_set_min_max_z(t_map *map)
{
	int	x;
	int	y;
	int	z;

	map->z_min = INT_MAX;
	map->z_max = INT_MIN;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			z = map->array[y][x][0];
			if (z < map->z_min)
				map->z_min = z;
			if (z > map->z_max)
				map->z_max = z;
			x++;
		}
		y++;
	}
}

void	ft_check_valid(char *filename, t_map *map)
{
	int		fd;
	char	*line;
	int		i;
	int		j;

	map->height = ft_get_height(filename);
	map->width = ft_get_width(filename);
	map->array = (int ***)malloc(sizeof(int **) * map->height);
	if (!map->array)
		ft_return_error("malloc error", 1);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		ft_return_error("Error opening file", 1);
	i = 0;
	/* get_next_lineの使用方法を修正 */
	line = get_next_line(fd);
	while (line != NULL)
	{
		map->array[i] = (int **)malloc(sizeof(int *) * map->width);
		if (!map->array[i])
			ft_return_error("malloc error", 1);
		j = -1;
		while (++j < map->width)
			map->array[i][j] = (int *)malloc(sizeof(int) * 2);
		ft_fill_map((int *)map->array[i], line, map->width);
		free(line);
		i++;
		line = get_next_line(fd);
	}
	close(fd);
	ft_set_min_max_z(map);
}
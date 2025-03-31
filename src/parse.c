#include "fdf.h"

/* @brief Gets the width of the map from a line (count numbers) */
int	get_map_width(char *line)
{
	int		width;
	char	**numbers;

	numbers = ft_split(line, ' ');
	if (!numbers)
		terminate("Error: ft_split failed in get_map_width");
	width = 0;
	while (numbers[width] && numbers[width][0] != '\n') // Stop at newline if present
		width++;
	free_split(numbers); // Use a libft helper or loop to free
	return (width);
}

/* @brief Counts the number of lines (height) in the file */
int count_lines(const char *filename)
{
    int     fd;
    int     height;
    char    *line; // read_bytes は不要

    fd = open(filename, O_RDONLY);
    if (fd < 0)
        terminate("Error: Failed to open map file");
    height = 0;
    line = get_next_line(fd); // 最初の行を読む
    while (line != NULL) // 戻り値が NULL でなければ読み込み成功 (EOF含む場合あり)
    {
        height++;
        free(line); // 読み込んだ行のメモリを解放
        line = get_next_line(fd); // 次の行を読む
    }
    close(fd);
    if (height == 0 && line)
        free(line);
    return (height);
}

/* @brief Allocates memory for the z_grid and color_grid */
static void allocate_grids(t_fdf *fdf)
{
	int i;

	fdf->z_grid = (int **)malloc(sizeof(int *) * fdf->map_height);
	if (!fdf->z_grid)
		terminate("Error: Malloc failed for z_grid rows");
	fdf->color_grid = (int **)malloc(sizeof(int *) * fdf->map_height);
	if (!fdf->color_grid)
	{
		free(fdf->z_grid);
		terminate("Error: Malloc failed for color_grid rows");
	}
	i = 0;
	while (i < fdf->map_height)
	{
		fdf->z_grid[i] = (int *)malloc(sizeof(int) * fdf->map_width);
		fdf->color_grid[i] = (int *)malloc(sizeof(int) * fdf->map_width);
		if (!fdf->z_grid[i] || !fdf->color_grid[i])
		{
			// Proper cleanup needed here if allocation fails mid-way
			while (--i >= 0) { free(fdf->z_grid[i]); free(fdf->color_grid[i]); }
			free(fdf->z_grid); free(fdf->color_grid);
			terminate("Error: Malloc failed for grid columns");
		}
		i++;
	}
}

/* @brief Fills a row of the grid with z and color values */
static void	fill_grid_row(int y, char *line, t_fdf *fdf)
{
	char	**values;
	char	*color_str;
	int		x;

	values = ft_split(line, ' ');
	if (!values)
		terminate("Error: ft_split failed while filling grid");
	x = 0;
	while (x < fdf->map_width)
	{
		if (!values[x]) // Check if line is shorter than expected width
		{
			free_split(values);
			terminate("Error: Map line has inconsistent width");
		}
		fdf->z_grid[y][x] = ft_atoi(values[x]);
		color_str = ft_strchr(values[x], ',');
		if (color_str)
			fdf->color_grid[y][x] = ft_atoi_hex(color_str + 1); // Use helper
		else
			fdf->color_grid[y][x] = -1; // Indicate no color specified
		x++;
	}
	// Optional: Check if there are more values than expected width
	if (values[x] && values[x][0] != '\n')
	{
		free_split(values);
		terminate("Error: Map line has inconsistent width (too long)");
	}
	free_split(values);
}


/* @brief Parses the map file into the fdf data structure */
void parse_map(const char *filename, t_fdf *fdf)
{
    int     fd;
    char    *line;
    int     y;
    // int     gnl_ret; // 不要

    fdf->map_height = count_lines(filename);
    if (fdf->map_height <= 0)
        terminate("Error: Map file is empty or could not be read");
    fd = open(filename, O_RDONLY);
    if (fd < 0)
        terminate("Error: Failed to open map file for parsing");
    line = get_next_line(fd); // 最初の行を読む
    if (!line) // 最初の行が読めない（空ファイルなど）
    {
        close(fd);
        terminate("Error: Failed to read first line or empty map");
    }
    fdf->map_width = get_map_width(line); // 最初の行から幅を取得
    if (fdf->map_width <= 0)
        terminate("Error: Invalid map width");
    allocate_grids(fdf);
    y = 0;
    while (line != NULL && y < fdf->map_height) // line が NULL になるまでループ
    {
        fill_grid_row(y, line, fdf);
        free(line); // 行を処理したら解放
        y++;
        if (y < fdf->map_height) // 無駄な読み込みを防ぐ
            line = get_next_line(fd); // 次の行を読む
        else
            line = NULL; // ループを抜けるために NULL を設定
    }
     if (line) // ループが予期せず終了した場合に残っている line を解放
         free(line);
    // GNL のエラーハンドリングが必要な場合は追加
    close(fd);
    find_z_min_max(fdf); // find_z_min_max を呼び出す（プロトタイプが必要）
}
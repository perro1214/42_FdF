#include "fdf.h"
#include <limits.h>

/*
** 安全なメモリアロケーションラッパー関数
*/
static void	*safe_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		ft_return_error("Memory allocation failed", 1);
	return (ptr);
}

/*
** ファイル存在チェックと安全なオープン
*/
static int	safe_open(char *filename)
{
	int		fd;

	if (!filename)
		ft_return_error("Filename is NULL", 0);

	// ファイルの存在を確認
	if (access(filename, F_OK) == -1)
		ft_return_error("File does not exist", 0);

	// 読み取り権限を確認
	if (access(filename, R_OK) == -1)
		ft_return_error("File cannot be read (permission denied)", 0);

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		ft_return_error("Error opening file", 1);

	return (fd);
}

/*
** ft_get_height - マップファイルの高さを安全に取得
*/
static int	ft_get_height(char *filename)
{
	char	*line;
	int		fd;
	int		height;

	printf("DEBUG: Opening file to count lines\n");
	fd = safe_open(filename);
	
	printf("DEBUG: Counting lines in file\n");
	height = 0;
	line = get_next_line(fd);
	
	while (line)
	{
		height++;
		free(line);
		line = get_next_line(fd);
	}
	
	close(fd);
	printf("DEBUG: Found %d lines in file\n", height);
	
	if (height == 0)
		ft_return_error("Empty map file", 0);
	
	return (height);
}

/*
** ft_get_width - マップファイルの幅を安全に取得
*/
static int	ft_get_width(char *filename)
{
	char	*line;
	int		fd;
	int		width;
	char	**split;

	printf("DEBUG: Opening file to determine map width\n");
	fd = safe_open(filename);
	
	printf("DEBUG: Reading first line\n");
	line = get_next_line(fd);
	if (!line)
		ft_return_error("Empty file", 0);
	
	// 最初の行の最後の改行を削除
	if (ft_strlen(line) > 0 && line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	
	printf("DEBUG: Splitting line: '%s'\n", line);
	split = ft_split(line, ' ');
	if (!split)
		ft_return_error("Memory allocation error", 1);
	
	width = 0;
	while (split && split[width])
		width++;
	
	printf("DEBUG: Found width: %d\n", width);
	
	if (width == 0)
		ft_return_error("Invalid map format (zero width)", 0);
	
	free(line);
	ft_split_free(split);
	close(fd);
	return (width);
}

/*
** ft_fill_map - 行データをマップに入力
*/
static void	ft_fill_map(int *data_line, char *line, int width)
{
	char	**split;
	int		i;
	char	*ptr;

	if (!data_line || !line)
		return;
	
	if (ft_strlen(line) > 0 && line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	
	split = ft_split(line, ' ');
	if (!split)
		ft_return_error("Memory allocation error", 1);
	
	i = 0;
	while (split[i] && i < width)
	{
		data_line[i] = ft_atoi(split[i]);
		
		ptr = ft_strchr(split[i], ',');
		if (ptr)
			data_line[i + width] = ft_atoi_base(ptr + 1, 16);
		else
			data_line[i + width] = -1;
		i++;
	}
	
	// 残りのセルをゼロで埋める
	while (i < width)
	{
		data_line[i] = 0;
		data_line[i + width] = -1;
		i++;
	}
	
	ft_split_free(split);
}

/* 
** ft_set_min_max_z - マップ内のZ値の最小値と最大値を安全に設定
** @map: マップ構造体
*/
void	ft_set_min_max_z(t_map *map)
{
	int	x;
	int	y;
	int	z;
	int	has_valid_z;

	if (!map || !map->array)
	{
		printf("DEBUG: Error in ft_set_min_max_z - NULL map or array\n");
		return;
	}
	
	map->z_min = INT_MAX;
	map->z_max = INT_MIN;
	has_valid_z = 0;
	
	printf("DEBUG: Scanning Z values in map of size %dx%d\n", map->width, map->height);
	y = 0;
	while (y < map->height)
	{
		if (!map->array[y])
		{
			printf("DEBUG: NULL row at y=%d\n", y);
			y++;
			continue;
		}
		
		x = 0;
		while (x < map->width)
		{
			if (!map->array[y][x])
			{
				printf("DEBUG: NULL cell at [%d][%d]\n", y, x);
				x++;
				continue;
			}
			
			z = map->array[y][x][0];
			if (z < map->z_min)
				map->z_min = z;
			if (z > map->z_max)
				map->z_max = z;
			has_valid_z = 1;
			x++;
		}
		y++;
	}
	
	// 有効なZ値がない、または最小値と最大値が同じ場合の処理
	if (!has_valid_z || map->z_min == map->z_max)
	{
		printf("DEBUG: Setting default Z range (no valid Z values found or flat map)\n");
		map->z_min = 0;
		map->z_max = 1;
	}
	
	printf("DEBUG: Z range set to: min=%d, max=%d\n", map->z_min, map->z_max);
}

/*
** ft_simple_read_map - 安全なマップ読み込み関数
** @filename: マップファイルのパス
** @map: マップ構造体
*/
void	ft_simple_read_map(char *filename, t_map *map)
{
	FILE	*file;
	char	line[1024];
	int		width;
	int		height;
	int		i;
	int		j;
	char	**split;

	printf("DEBUG: Opening file for reading: %s\n", filename);
	file = fopen(filename, "r");
	if (!file)
	{
		printf("DEBUG: Failed to open file\n");
		ft_return_error("Error opening file", 1);
	}

	// 行数カウント
	height = 0;
	while (fgets(line, sizeof(line), file))
		height++;
	
	printf("DEBUG: Counted %d lines in file\n", height);
	if (height <= 0)
	{
		fclose(file);
		ft_return_error("Empty map file", 0);
	}
	map->height = height;
	
	// ファイルを先頭に戻す
	rewind(file);
	
	// 1行目を読んで幅を決定
	if (!fgets(line, sizeof(line), file))
	{
		fclose(file);
		ft_return_error("Failed to read first line", 1);
	}
	
	// 最後の改行を削除
	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	line[i] = '\0';
	
	// スペースで分割
	printf("DEBUG: Splitting first line for width determination\n");
	split = ft_split(line, ' ');
	if (!split)
	{
		fclose(file);
		ft_return_error("Memory allocation error", 1);
	}
	
	// 要素数をカウント
	width = 0;
	while (split[width])
		width++;
	
	printf("DEBUG: Determined width: %d\n", width);
	map->width = width;
	ft_split_free(split);
	
	// メモリ確保
	printf("DEBUG: Allocating 3D array for map data\n");
	map->array = (int ***)malloc(sizeof(int **) * height);
	if (!map->array)
	{
		fclose(file);
		ft_return_error("Memory allocation error", 1);
	}
	
	// すべての要素を初期化
	printf("DEBUG: Initializing array elements\n");
	for (i = 0; i < height; i++)
	{
		map->array[i] = (int **)malloc(sizeof(int *) * width);
		if (!map->array[i])
		{
			fclose(file);
			ft_return_error("Memory allocation error", 1);
		}
		
		for (j = 0; j < width; j++)
		{
			map->array[i][j] = (int *)malloc(sizeof(int) * 2);
			if (!map->array[i][j])
			{
				fclose(file);
				ft_return_error("Memory allocation error", 1);
			}
			
			// デフォルト値（念のため初期化）
			map->array[i][j][0] = 0;  // Z値
			map->array[i][j][1] = -1; // 色
		}
	}
	
	// ファイルを再度先頭に戻す
	rewind(file);
	
	// データ読み込み
	printf("DEBUG: Reading map data\n");
	i = 0;
	while (i < height && fgets(line, sizeof(line), file))
	{
		// 最後の改行を削除
		j = 0;
		while (line[j] && line[j] != '\n')
			j++;
		line[j] = '\0';
		
		printf("DEBUG: Processing line %d: %s\n", i, line);
		split = ft_split(line, ' ');
		if (!split)
		{
			fclose(file);
			ft_return_error("Memory allocation error", 1);
		}
		
		for (j = 0; j < width && split[j]; j++)
		{
			// Z値を設定
			map->array[i][j][0] = ft_atoi(split[j]);
			
			// 色情報を設定（もしあれば）
			char *color_ptr = ft_strchr(split[j], ',');
			if (color_ptr)
				map->array[i][j][1] = ft_atoi_base(color_ptr + 1, 16);
		}
		
		ft_split_free(split);
		i++;
	}
	
	fclose(file);
	
	// Z範囲を安全に設定
	ft_set_min_max_z(map);
}

/*
** ft_check_valid - メイン関数：マップを読み込んで配列に格納
*/
void	ft_check_valid(char *filename, t_map *map)
{
	int		fd;
	char	*line;
	int		i;
	int		j;

	if (!map)
		ft_return_error("NULL map pointer", 0);

	printf("DEBUG: Getting map height\n");
	map->height = ft_get_height(filename);
	
	printf("DEBUG: Getting map width\n");
	map->width = ft_get_width(filename);
	
	printf("DEBUG: Map dimensions: %dx%d\n", map->width, map->height);
	
	printf("DEBUG: Allocating memory for map array\n");
	map->array = (int ***)safe_malloc(sizeof(int **) * map->height);

	printf("DEBUG: Opening file for map data reading\n");
	fd = safe_open(filename);
	
	i = 0;
	printf("DEBUG: Reading map data line by line\n");
	while (i < map->height)
	{
		map->array[i] = (int **)safe_malloc(sizeof(int *) * map->width);
		
		j = 0;
		while (j < map->width)
		{
			map->array[i][j] = (int *)safe_malloc(sizeof(int) * 2);
			// 初期化（念のため）
			map->array[i][j][0] = 0;
			map->array[i][j][1] = -1;
			j++;
		}
		i++;
	}
	
	// ファイルを再度読み込んでデータを設定
	printf("DEBUG: Reading file data\n");
	close(fd);
	fd = safe_open(filename);
	
	i = 0;
	line = get_next_line(fd);
	while (line && i < map->height)
	{
		printf("DEBUG: Processing line %d\n", i);
		ft_fill_map((int *)map->array[i], line, map->width);
		free(line);
		i++;
		line = get_next_line(fd);
	}
	
	close(fd);
	printf("DEBUG: Setting Z range\n");
	ft_set_min_max_z(map);
	printf("DEBUG: Map loaded successfully\n");
}
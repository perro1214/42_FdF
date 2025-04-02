#include "fdf.h"

/* @brief Initializes MiniLibX connection, window, and image buffer */
void	init_mlx(t_fdf *fdf)
{
	fdf->mlx_ptr = mlx_init();
	if (!fdf->mlx_ptr)
		terminate("Error: mlx_init() failed");
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "FdF");
	if (!fdf->win_ptr)
	{
		terminate("Error: mlx_new_window() failed");
	}
	fdf->img.img_ptr = mlx_new_image(fdf->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (!fdf->img.img_ptr)
	{
		mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
		terminate("Error: mlx_new_image() failed");
	}
	fdf->img.addr = mlx_get_data_addr(fdf->img.img_ptr, &fdf->img.bpp,
			&fdf->img.line_len, &fdf->img.endian);
	if (!fdf->img.addr)
	{
		mlx_destroy_image(fdf->mlx_ptr, fdf->img.img_ptr);
		mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
		terminate("Error: mlx_get_data_addr() failed");
	}
}

/* @brief Calculate scale based on map size and window target */
static float	calculate_initial_scale(t_fdf *fdf, float target_ratio)
{
	float	scale_x;
	float	scale_y;
	float	scale;

	if (fdf->map_width <= 1 && fdf->map_height <= 1)
		return (20.0f);
	if (fdf->map_width <= 0)
		fdf->map_width = 1;
	if (fdf->map_height <= 0)
		fdf->map_height = 1;
	scale_x = (WIN_WIDTH * target_ratio) / fdf->map_width;
	scale_y = (WIN_HEIGHT * target_ratio) / fdf->map_height;
	if (scale_x < scale_y)
		scale = scale_x;
	else
		scale = scale_y;
	if (scale < 2.0f)
		scale = 2.0f;
	if (scale > 100.0f)
		scale = 100.0f;
	return (scale);
}

/* @brief マップを中央に表示するための初期オフセットを計算する */
static void	calculate_initial_offsets(t_fdf *fdf)
{
	float	proj_center_x;
	float	proj_top_y;

	proj_center_x = ((fdf->map_width / 2.0f) - (fdf->map_height / 2.0f))
		* cos(fdf->angle);
	proj_center_x *= fdf->scale;
	fdf->x_offset = (WIN_WIDTH / 2) - (int)proj_center_x;
	proj_top_y = ((0.0f - (fdf->map_height / 2.0f))) * sin(fdf->angle)
		- ((fdf->z_min + fdf->z_max) / 2.0f);
	proj_top_y *= fdf->scale;
	fdf->y_offset = (WIN_HEIGHT / 4) - (int)proj_top_y;
}

/* @brief Calculate initial scale and offsets to fit map */
void	calculate_defaults(t_fdf *fdf)
{
	float	target_ratio;

	target_ratio = 0.5f;
	if (fdf->map_width <= 0 || fdf->map_height <= 0)
	{
		fdf->scale = 10.0f;
		fdf->x_offset = WIN_WIDTH / 2;
		fdf->y_offset = WIN_HEIGHT / 2;
		ft_putendl_fd("Warn: calc_defaults invalid map dims.", 2);
		return ;
	}
	fdf->scale = calculate_initial_scale(fdf, target_ratio);
	calculate_initial_offsets(fdf);
}

/* @brief Finds min and max Z values (useful for color gradients) */
void	find_z_min_max(t_fdf *fdf)
{
	int	x;
	int	y;

	if (!fdf->z_grid || fdf->map_height <= 0 || fdf->map_width <= 0)
		return ;
	fdf->z_min = fdf->z_grid[0][0];
	fdf->z_max = fdf->z_grid[0][0];
	y = 0;
	while (y < fdf->map_height)
	{
		x = 0;
		while (x < fdf->map_width)
		{
			if (fdf->z_grid[y][x] < fdf->z_min)
				fdf->z_min = fdf->z_grid[y][x];
			if (fdf->z_grid[y][x] > fdf->z_max)
				fdf->z_max = fdf->z_grid[y][x];
			x++;
		}
		y++;
	}
}

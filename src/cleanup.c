#include "fdf.h"
#include <stdlib.h>

static void	cleanup_grids(t_fdf *fdf)
{
	int	i;

	if (!fdf->z_grid)
		return ;
	i = 0;
	while (i < fdf->map_height)
	{
		if (fdf->z_grid[i])
			free(fdf->z_grid[i]);
		if (fdf->color_grid && fdf->color_grid[i])
			free(fdf->color_grid[i]);
		i++;
	}
	free(fdf->z_grid);
	fdf->z_grid = NULL;
	if (fdf->color_grid)
		free(fdf->color_grid);
	fdf->color_grid = NULL;
	fdf->map_height = 0;
	fdf->map_width = 0;
}

static void	cleanup_mlx(t_fdf *fdf)
{
	if (!fdf->mlx_ptr)
		return ;
	if (fdf->img.img_ptr)
		mlx_destroy_image(fdf->mlx_ptr, fdf->img.img_ptr);
	if (fdf->win_ptr)
		mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
	fdf->mlx_ptr = NULL;
	fdf->img.img_ptr = NULL;
	fdf->win_ptr = NULL;
}

void	cleanup(t_fdf *fdf)
{
	if (!fdf)
		return ;
	cleanup_grids(fdf);
	cleanup_mlx(fdf);
}

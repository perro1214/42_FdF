#include "fdf.h"

void	terminate(char *error_message)
{
	if (error_message)
		perror(error_message);
	else
		ft_putendl_fd("Exiting.", STDOUT_FILENO);
	exit(EXIT_FAILURE);
}

void	init_fdf_struct(t_fdf *fdf)
{
	fdf->mlx_ptr = NULL;
	fdf->win_ptr = NULL;
	fdf->img.img_ptr = NULL;
	fdf->img.addr = NULL;
	fdf->map_width = 0;
	fdf->map_height = 0;
	fdf->z_grid = NULL;
	fdf->color_grid = NULL;
	fdf->z_min = 0;
	fdf->z_max = 0;
	fdf->scale = 20.0f;
	fdf->x_offset = WIN_WIDTH / 3;
	fdf->y_offset = WIN_HEIGHT / 4;
	fdf->angle = 0.5235f;
}

void	setup_hooks(t_fdf *fdf)
{
	mlx_hook(fdf->win_ptr, 2, 1L << 0, key_hook, fdf);
	mlx_hook(fdf->win_ptr, 17, 1L << 17, close_hook, fdf);
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	if (argc != 2)
	{
		ft_putendl_fd("Usage: ./fdf <map_file.fdf>", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	init_fdf_struct(&fdf);
	parse_map(argv[1], &fdf);
	if (fdf.map_height <= 0 || fdf.map_width <= 0)
		terminate("Error: Invalid or empty map after parsing");
	init_mlx(&fdf);
	calculate_defaults(&fdf);
	render(&fdf);
	setup_hooks(&fdf);
	mlx_loop(fdf.mlx_ptr);
	return (EXIT_SUCCESS);
}

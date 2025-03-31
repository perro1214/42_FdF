#include "fdf.h"

/* @brief Handles program termination with an error message */
void	terminate(char *error_message)
{
	if (error_message)
		perror(error_message); // Uses perror as allowed
	else
		ft_putendl_fd("Exiting.", STDOUT_FILENO);
	exit(EXIT_FAILURE); // Allowed exit function
}

/* @brief Frees allocated memory and destroys MLX components */
void cleanup(t_fdf *fdf)
{
    int i;

    if (!fdf)
        return ;

    // --- Free map data ---
    if (fdf->z_grid)
    {
        i = 0;
        // Check map_height before looping if it could be 0 from parsing errors
        while (fdf->map_height > 0 && i < fdf->map_height)
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
    }
     // Reset dimensions as well
    fdf->map_height = 0;
    fdf->map_width = 0;


    // --- MLX Cleanup (Check mlx_ptr first!) ---
    // Only destroy if mlx connection was successfully initialized
    if (fdf->mlx_ptr)
    {
        // Destroy image if it was created
        if (fdf->img.img_ptr) {
            mlx_destroy_image(fdf->mlx_ptr, fdf->img.img_ptr);
            fdf->img.img_ptr = NULL; // Set to NULL after destroying
        }
        // Destroy window if it was created
        if (fdf->win_ptr) {
            mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
            fdf->win_ptr = NULL; // Set to NULL after destroying
        }
        // Destroy display connection (Linux specific, needed if mlx_init succeeded)
        // Check MiniLibX documentation if mlx_destroy_display is required for your version
        // mlx_destroy_display(fdf->mlx_ptr); // Uncomment if needed
        // free(fdf->mlx_ptr); // Usually not needed for the pointer returned by mlx_init
        fdf->mlx_ptr = NULL; // Set to NULL
    }
}


/* @brief Main function */
int	main(int argc, char **argv)
{
	t_fdf	fdf; // Use stack allocation for the main struct

	if (argc != 2)
	{
		ft_putendl_fd("Usage: ./fdf <map_file.fdf>", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	init_fdf(&fdf); // Initialize default values
	parse_map(argv[1], &fdf); // Read and store map data
	if (fdf.map_height == 0 || fdf.map_width == 0) // Check if map parsing failed
		terminate("Error: Invalid or empty map");
	init_mlx(&fdf); // Initialize MiniLibX and window
	calculate_defaults(&fdf); // Calculate initial scale and offset
	render(&fdf); // Perform initial drawing
	// --- Register Hooks ---
	mlx_hook(fdf.win_ptr, 2, 1L << 0, key_hook, &fdf); // KeyPress
	mlx_hook(fdf.win_ptr, 17, 1L << 17, close_hook, &fdf); // DestroyNotify (Window close)
	// mlx_expose_hook(fdf.win_ptr, expose_hook, &fdf); // Optional: redraw on expose
	mlx_loop(fdf.mlx_ptr); // Start event loop
	cleanup(&fdf); // Should technically be unreachable if loop runs forever
	return (EXIT_SUCCESS);
}

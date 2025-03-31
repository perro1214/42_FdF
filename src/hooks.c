#include "fdf.h"

/* @brief Handles key press events */
int	key_hook(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_ESC)
	{
		// ★ cleanup を呼び出して終了するだけにする ★
		cleanup(fdf);
		exit(EXIT_SUCCESS);
	}
	// Add other key hooks here if needed
	return (0);
}

/* @brief Handles the window close button event */
int	close_hook(t_fdf *fdf)
{
	// ★ cleanup を呼び出して終了するだけにする ★
	cleanup(fdf);
	exit(EXIT_SUCCESS);
	// return (0); // exit() の後なので不要
}

/* @brief Handles window exposure events (redraw if necessary) */
/* Useful if window gets covered and then uncovered */
int expose_hook(t_fdf *fdf)
{
    render(fdf); // Just re-render the current state
    return (0);
}
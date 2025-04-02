#include "fdf.h"
#include <stdlib.h>

void	init_bresenham_params(t_bresenham *bres, t_point p0, t_point p1)
{
	bres->dx = abs((int)p1.x - (int)p0.x);
	bres->dy = -abs((int)p1.y - (int)p0.y);
	if (p0.x < p1.x)
		bres->sx = 1;
	else
		bres->sx = -1;
	if (p0.y < p1.y)
		bres->sy = 1;
	else
		bres->sy = -1;
	bres->err = bres->dx + bres->dy;
	bres->cur_x = (int)p0.x;
	bres->cur_y = (int)p0.y;
}

int	key_hook(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_ESC)
	{
		ft_putendl_fd("ESC key pressed. Exiting.", STDOUT_FILENO);
		cleanup(fdf);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

int	close_hook(t_fdf *fdf)
{
	ft_putendl_fd("Window close button clicked. Exiting.", STDOUT_FILENO);
	cleanup(fdf);
	exit(EXIT_SUCCESS);
}

int	expose_hook(t_fdf *fdf)
{
	render(fdf);
	return (0);
}


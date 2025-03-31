#include "fdf.h"

/* @brief Puts a pixel onto the image buffer respecting boundaries */
void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	// Check bounds before writing
	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
	{
		dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
		*(unsigned int *)dst = color; // Cast to unsigned int* for direct color write
	}
}

/* @brief Helper function for Bresenham's algorithm setup */
static void	init_bresenham(t_point p0, t_point p1, int *dx, int *dy, int *sx, int *sy)
{
	*dx = abs((int)p1.x - (int)p0.x);
	*dy = -abs((int)p1.y - (int)p0.y);
	*sx = (p0.x < p1.x) ? 1 : -1;
	*sy = (p0.y < p1.y) ? 1 : -1;
}

/* @brief Bresenham's line drawing algorithm */
void	draw_line(t_point p0, t_point p1, t_fdf *fdf)
{
	int dx;
	int dy;
	int sx;
	int sy;
	int err;
	int e2;
	int current_x;
	int current_y;

	// Optional: Interpolate color along the line (simple version: use p0's color)
	int color = (p0.color != -1) ? p0.color : get_default_color(p0.z, fdf);

	init_bresenham(p0, p1, &dx, &dy, &sx, &sy);
	err = dx + dy;
	current_x = (int)p0.x;
	current_y = (int)p0.y;
	while (1)
	{
		my_mlx_pixel_put(&fdf->img, current_x, current_y, color);
		if (current_x == (int)p1.x && current_y == (int)p1.y)
			break ;
		e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			current_x += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			current_y += sy;
		}
	}
}

/* @brief Renders the entire wireframe model */
void	render(t_fdf *fdf)
{
	int		x;
	int		y;
	t_point	current_3d;
	t_point	p0; // Projected current point
	t_point	p_right; // Projected point to the right
	t_point	p_down; // Projected point below

	// Clear image (optional, set to black or another background color)
	// memset(fdf->img.addr, 0, WIN_WIDTH * WIN_HEIGHT * (fdf->img.bpp / 8));

	y = 0;
	while (y < fdf->map_height)
	{
		x = 0;
		while (x < fdf->map_width)
		{
			current_3d = (t_point){(float)x, (float)y, (float)fdf->z_grid[y][x],
									 fdf->color_grid[y][x]}; // Use stored color
			p0 = project(current_3d, fdf); // Project current point

			// Draw line to the right neighbor
			if (x < fdf->map_width - 1)
			{
				t_point right_3d = {(float)(x + 1), (float)y, (float)fdf->z_grid[y][x + 1],
				                    fdf->color_grid[y][x+1]};
				p_right = project(right_3d, fdf);
				draw_line(p0, p_right, fdf);
			}
			// Draw line to the bottom neighbor
			if (y < fdf->map_height - 1)
			{
                 t_point down_3d = {(float)x, (float)(y + 1), (float)fdf->z_grid[y + 1][x],
                                    fdf->color_grid[y+1][x]};
				p_down = project(down_3d, fdf);
				draw_line(p0, p_down, fdf);
			}
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img.img_ptr, 0, 0);
}

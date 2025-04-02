#include "fdf.h"
#include <math.h>

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
	{
		dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

void	clear_image(t_img *img)
{
	if (img && img->addr)
	{
		ft_memset(img->addr, 0, WIN_WIDTH * WIN_HEIGHT * (img->bpp / 8));
	}
}

void	draw_line(t_point p0, t_point p1, t_fdf *fdf)
{
	t_bresenham	bres;
	int			color;

	init_bresenham_params(&bres, p0, p1);
	if (p0.color != -1)
		color = p0.color;
	else
		color = get_default_color(p0.z, fdf);
	while (1)
	{
		my_mlx_pixel_put(&fdf->img, bres.cur_x, bres.cur_y, color);
		if (bres.cur_x == (int)p1.x && bres.cur_y == (int)p1.y)
			break ;
		bres.err2 = 2 * bres.err;
		if (bres.err2 >= bres.dy)
		{
			bres.err += bres.dy;
			bres.cur_x += bres.sx;
		}
		if (bres.err2 <= bres.dx)
		{
			bres.err += bres.dx;
			bres.cur_y += bres.sy;
		}
	}
}

static void	render_point_connections(int x, int y, t_fdf *fdf)
{
	t_point	current_3d;
	t_point	p0;
	t_point	p_right;
	t_point	p_down;
	t_point	_3d;

	current_3d = (t_point){(float)x, (float)y, (float)fdf->z_grid[y][x],
		fdf->color_grid[y][x]};
	p0 = project(current_3d, fdf);
	if (x < fdf->map_width - 1)
	{
		_3d = (t_point){(float)(x + 1), (float)y, (float)fdf->z_grid[y][x + 1],
			fdf->color_grid[y][x + 1]};
		p_right = project(_3d, fdf);
		draw_line(p0, p_right, fdf);
	}
	if (y < fdf->map_height - 1)
	{
		_3d = (t_point){(float)x, (float)(y + 1), (float)fdf->z_grid[y + 1][x],
			fdf->color_grid[y + 1][x]};
		p_down = project(_3d, fdf);
		draw_line(p0, p_down, fdf);
	}
}

void	render(t_fdf *fdf)
{
	int	x;
	int	y;

	clear_image(&fdf->img);
	y = 0;
	while (y < fdf->map_height)
	{
		x = 0;
		while (x < fdf->map_width)
		{
			render_point_connections(x, y, fdf);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img.img_ptr, 0, 0);
}

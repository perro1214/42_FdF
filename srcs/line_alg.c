#include "fdf.h"

static void	ft_swap_points(t_point *s, t_point *e)
{
	t_point	tmp;

	tmp.x = s->x;
	tmp.y = s->y;
	tmp.z = s->z;
	tmp.color = s->color;
	s->x = e->x;
	s->y = e->y;
	s->z = e->z;
	s->color = e->color;
	e->x = tmp.x;
	e->y = tmp.y;
	e->z = tmp.z;
	e->color = tmp.color;
}

static int	ft_get_color(int start, int end, double percentage)
{
	int	r;
	int	g;
	int	b;

	r = (int)((1 - percentage) * ((start >> 16) & 0xFF)
			+ percentage * ((end >> 16) & 0xFF));
	g = (int)((1 - percentage) * ((start >> 8) & 0xFF)
			+ percentage * ((end >> 8) & 0xFF));
	b = (int)((1 - percentage) * (start & 0xFF)
			+ percentage * (end & 0xFF));
	return ((r << 16) | (g << 8) | b);
}

void	ft_draw_line(t_point s, t_point e, t_fdf *env)
{
	int		steps;
	int		i;
	double	y_inc;
	double	percentage;

	env->steep = ft_abs(e.y - s.y) > ft_abs(e.x - s.x);
	if (env->steep)
	{
		ft_swap(&s.x, &s.y);
		ft_swap(&e.x, &e.y);
	}
	if (s.x > e.x)
		ft_swap_points(&s, &e);
	steps = e.x - s.x;
	/* x_inc変数を削除（xはiによって一定間隔で増加するため不要） */
	y_inc = (double)(e.y - s.y) / (double)steps;
	i = 0;
	while (i <= steps)
	{
		percentage = (steps == 0) ? 1.0 : (double)i / (double)steps;
		if (env->steep)
			ft_put_pixel(env, s.y + (int)(i * y_inc), s.x + i,
				ft_get_color(s.color, e.color, percentage));
		else
			ft_put_pixel(env, s.x + i, s.y + (int)(i * y_inc),
				ft_get_color(s.color, e.color, percentage));
		i++;
	}
}
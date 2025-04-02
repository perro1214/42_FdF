#include "fdf.h"
#include <math.h>

t_point	project(t_point p, t_fdf *fdf)
{
	t_point	projected_p;
	float	x_tmp;
	float	y_tmp;
	float	rad_angle;

	rad_angle = fdf->angle;
	x_tmp = p.x - (fdf->map_width / 2.0f);
	y_tmp = p.y - (fdf->map_height / 2.0f);
	projected_p.x = (x_tmp - y_tmp) * cos(rad_angle);
	projected_p.y = (x_tmp + y_tmp) * sin(rad_angle) - p.z;
	projected_p.x *= fdf->scale;
	projected_p.y *= fdf->scale;
	projected_p.x += fdf->x_offset;
	projected_p.y += fdf->y_offset;
	projected_p.z = p.z;
	projected_p.color = p.color;
	return (projected_p);
}

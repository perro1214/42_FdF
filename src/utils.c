#include "fdf.h"

/* @brief Applies isometric projection to a 3D point */
t_point project(t_point p, t_fdf *fdf)
{
	t_point projected_p;
	float	x_tmp;
	float	y_tmp;
	float	rad_angle; // Angle for projection calculation

	// Use the stored angle (e.g., 0.5235 for 30 degrees)
	rad_angle = fdf->angle;

	// Center the point around origin before rotation/projection
	x_tmp = p.x - (fdf->map_width / 2.0f);
	y_tmp = p.y - (fdf->map_height / 2.0f);

	// Isometric projection formulas
	projected_p.x = (x_tmp - y_tmp) * cos(rad_angle);
	projected_p.y = (x_tmp + y_tmp) * sin(rad_angle) - p.z;

	// Apply scaling (zoom)
	projected_p.x *= fdf->scale;
	projected_p.y *= fdf->scale;

	// Apply translation (offset) to position in window
	projected_p.x += fdf->x_offset;
	projected_p.y += fdf->y_offset;

	// Keep original z and color for potential future use (like Z-buffering or coloring)
	projected_p.z = p.z;
	projected_p.color = p.color; // Pass color through

	return (projected_p);
}

/* @brief Calculates a default color based on altitude (simple gradient) */
int	get_default_color(int z, t_fdf *fdf)
{
	float	percentage;
	int		red;
	int		green;
	int		blue;

	if (fdf->z_max == fdf->z_min) // Avoid division by zero for flat maps
		return (DEFAULT_COLOR);
	// Calculate how high z is relative to min/max range (0.0 to 1.0)
	percentage = (float)(z - fdf->z_min) / (float)(fdf->z_max - fdf->z_min);

	// Simple gradient: White (low) to Red (high)
	red = (int)(255 * percentage);
	green = (int)(255 * (1.0f - percentage));
	blue = (int)(255 * (1.0f - percentage));

    // Clamp values (shouldn't be necessary if percentage is correct)
	red = (red < 0) ? 0 : (red > 255) ? 255 : red;
	green = (green < 0) ? 0 : (green > 255) ? 255 : green;
	blue = (blue < 0) ? 0 : (blue > 255) ? 255 : blue;


	return ((red << 16) | (green << 8) | blue);
}

/* @brief Helper to free arrays created by ft_split */
void free_split(char **split_arr)
{
	int i;

	if (!split_arr)
		return;
	i = 0;
	while (split_arr[i])
	{
		free(split_arr[i]);
		i++;
	}
	free(split_arr);
}

/* @brief Checks if a character is a valid hexadecimal digit */
int	ft_ishexdigit(char c)
{
	return (ft_isdigit(c) || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'));
}


/* @brief Converts a hexadecimal string (like 0xFFFFFF or FFFFFF) to int */
int	ft_atoi_hex(const char *str)
{
	int		result;
	int		i;
	char	c;

	result = 0;
	i = 0;
	// Skip "0x" or "0X" prefix if present
	if (str[i] == '0' && (str[i + 1] == 'x' || str[i + 1] == 'X'))
		i += 2;
	while (str[i] && ft_ishexdigit(str[i]))
	{
		c = str[i];
		result *= 16;
		if (ft_isdigit(c))
			result += c - '0';
		else if (c >= 'a' && c <= 'f')
			result += c - 'a' + 10;
		else if (c >= 'A' && c <= 'F')
			result += c - 'A' + 10;
		i++;
	}
	return (result);
}
#include "fdf.h"
#include <math.h>

static void	calculate_clamped_rgb(int *r_ptr, int *g_ptr, int *b_ptr)
{
	int	red;
	int	green;
	int	blue;

	red = *r_ptr;
	green = *g_ptr;
	blue = *b_ptr;
	if (red < 0)
		red = 0;
	else if (red > 255)
		red = 255;
	if (green < 0)
		green = 0;
	else if (green > 255)
		green = 255;
	if (blue < 0)
		blue = 0;
	else if (blue > 255)
		blue = 255;
	*r_ptr = red;
	*g_ptr = green;
	*b_ptr = blue;
}
/* @brief Calculates a default color based on altitude (simple gradient) */
int	get_default_color(int z, t_fdf *fdf)
{
	int		z_range;
	float	percentage;
	int		red;
	int		green;
	int		blue;

	percentage = 0.5f;
	z_range = fdf->z_max - fdf->z_min;
	if (z_range != 0)
		percentage = (float)(z - fdf->z_min) / (float)z_range;
	if (percentage < 0.5)
	{
		red = (int)(255 * (percentage * 2));
		green = red;
		blue = 255;
	}
	else
	{
		red = 255;
		green = (int)(255 * (1.0f - (percentage - 0.5f) * 2));
		blue = green;
	}
	calculate_clamped_rgb(&red, &green, &blue);
	return ((red << 16) | (green << 8) | blue);
}

/* @brief Helper to free arrays created by ft_split */
void	free_split(char **split_arr)
{
	int	i;

	if (!split_arr)
		return ;
	i = 0;
	while (split_arr[i])
	{
		free(split_arr[i]);
		i++;
	}
	free(split_arr);
}

/* @brief Checks if a character is a valid hexadecimal digit */
// Assuming ft_isdigit is available from libft.h (implicitly included via fdf.h)
int	ft_ishexdigit(char c)
{
	return (ft_isdigit(c) || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'));
}

/* @brief Converts a hexadecimal string (like 0xFFFFFF or FFFFFF) to int */
int	ft_atoi_hex(const char *str)
{
	int		result;
	int		i;
	char	c_lower;

	result = 0;
	i = 0;
	if (str && str[i] == '0' && (str[i + 1] == 'x' || str[i + 1] == 'X'))
		i += 2;
	while (str && str[i] && ft_ishexdigit(str[i]))
	{
		c_lower = ft_tolower(str[i]);
		result *= 16;
		if (ft_isdigit(c_lower))
			result += c_lower - '0';
		else
			result += c_lower - 'a' + 10;
		i++;
	}
	return (result);
}
// --- File Function Count: 5 ---

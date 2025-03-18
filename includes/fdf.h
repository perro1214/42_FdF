/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: perro1214 <perro1214@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-17 17:40:00 by perro1214         #+#    #+#             */
/*   Updated: 2025-03-17 17:40:00 by perro1214        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include "mlx.h"
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

# define WIDTH 1920
# define HEIGHT 1080

# define KEY_ESC 65307

/* マップ構造体 */
typedef struct s_map
{
	int	width;
	int	height;
	int	***array;
	int	z_min;
	int	z_max;
}	t_map;

/* 座標構造体 */
typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	int	color;
}	t_point;

/* 環境構造体 */
typedef struct s_fdf
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*data_addr;
	int		bpp;
	int		size_line;
	int		endian;
	t_map	*map;
}	t_fdf;

/* パース関連の関数 */
void	ft_simple_read_map(char *filename, t_map *map);
t_map	*ft_map_init(void);

/* 描画関連の関数 */
void	ft_draw(t_map *map, t_fdf *env);
void	ft_draw_line(t_point p1, t_point p2, t_fdf *env);
void	ft_put_pixel(t_fdf *env, int x, int y, int color);

/* 色関連の関数 */
int		ft_get_color_by_height(int z, int z_min, int z_max);

/* コントロール関連の関数 */
int		ft_close(void *param);
int		ft_key_press(int key, void *param);
void	ft_hook_controls(t_fdf *env);

/* ユーティリティ関数 */
void	ft_return_error(char *str, int exit_code);
void	ft_split_free(char **split);
int		ft_atoi_base(char *str, int base);
int		ft_max(int a, int b);
int		ft_min(int a, int b);

#endif
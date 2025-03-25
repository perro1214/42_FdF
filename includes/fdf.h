/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhayato@student.42.fr <hhayato>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:03:22 by perro1214         #+#    #+#             */
/*   Updated: 2025/03/25 21:07:33 by hhayato@stu      ###   ########.fr       */
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
void	ft_read_map(char *filename, t_map *map);
t_map	*ft_map_init(void);
void	update_row_min_max(t_map *map, int y);
void	set_min_max(t_map *map);

/* 描画関連の関数 */
void	ft_clear_img(t_fdf *env);
void	ft_draw(t_map *map, t_fdf *env);
void	draw_line(t_point p1, t_point p2, t_fdf *env);
void	put_pixel(t_fdf *env, int x, int y, int color);

/* 色関連の関数 */
int		get_color(int z, int z_min, int z_max);

/* コントロール関連の関数 */
int		ft_close(void *param);
int		key_press(int key, void *param);
int		handle_expose(void *param);
void	hook_controls(t_fdf *env);

/* メモリ管理関数 */
void	ft_free_map(t_map *map);
void	ft_free_env(t_fdf *env);

/* ユーティリティ関数 */
void	err_exit(char *str, int exit_code);
void	free_split(char **split);
int		ft_atoi_base(char *str, int base);
int		ft_max(int a, int b);
int		ft_min(int a, int b);

#endif
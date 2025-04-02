#ifndef FDF_H
# define FDF_H

# include <stdlib.h> // size_t, malloc, free, exit
# include <fcntl.h>  // open
# include <unistd.h> // read, write, close
# include <stdio.h>  // perror (allowed)
# include <string.h> // strerror (allowed)
# include <math.h>   // cos, sin, sqrt (allowed with -lm)
# include "../mlx/mlx.h" // MiniLibX header (adjust path if needed)
# include "../libft/libft.h" // Libft header
# include "../get_next_line/get_next_line.h" // GNL header

// --- Configuration ---
# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define DEFAULT_COLOR 0xFFFFFF // White

// --- Key Codes (Example for macOS - adjust if needed for Linux) ---
# define KEY_ESC 65307
// # define KEY_ESC 65307 // Linux X11

// --- Structures ---

// Structure for a 3D point with color
typedef struct s_point
{
	float	x;
	float	y;
	float	z;
	int		color;
}	t_point;

// Structure for MiniLibX image data
typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		bpp;        // bits per pixel
	int		line_len;   // line length in bytes
	int		endian;     // endianness
}	t_img;

// Main FdF data structure
typedef struct s_fdf
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
	int		map_width;
	int		map_height;
	int		**z_grid;   // Stores original z-values (altitude)
	int		**color_grid; // Stores original colors (if any)
	int		z_min;      // Min altitude for color gradient (optional)
	int		z_max;      // Max altitude for color gradient (optional)
	float	scale;      // Zoom factor
	int		x_offset;   // Horizontal translation
	int		y_offset;   // Vertical translation
	float	angle;      // Isometric projection angle factor (e.g., 0.5235f)
}	t_fdf;

typedef struct s_bresenham
{
	int	dx;       // xの差の絶対値
	int	dy;       // yの差の絶対値（負数として扱う）
	int	sx;       // x方向のステップ (+1 or -1)
	int	sy;       // y方向のステップ (+1 or -1)
	int	err;      // 誤差項
	int	err2;     // 誤差項 * 2 (ループ内計算用)
	int	cur_x;    // 現在描画中のx座標
	int	cur_y;    // 現在描画中のy座標
}	t_bresenham;

// --- Function Prototypes ---

// main.c
void	terminate(char *error_message);

// cleanup.c
void	cleanup(t_fdf *fdf);

// parse.c
void	parse_map(const char *filename, t_fdf *fdf);

// parse_utils.c
int	get_map_width(char *line);
int	count_lines(const char *filename);
void	allocate_grids(t_fdf *fdf);
int	fill_grid_row(int y, char *line, t_fdf *fdf);

// init.c
void	init_fdf(t_fdf *fdf);
void	init_mlx(t_fdf *fdf);
void	calculate_defaults(t_fdf *fdf);
void    find_z_min_max(t_fdf *fdf);

// draw.c
void	init_bresenham_params(t_bresenham *bres, t_point p0, t_point p1);
void	render(t_fdf *fdf);
void	draw_line(t_point p0, t_point p1, t_fdf *fdf);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);

// hooks.c
int		key_hook(int keycode, t_fdf *fdf);
int		close_hook(t_fdf *fdf);
int		expose_hook(t_fdf *fdf); // Handles window exposure/redraw

// utils.c (or projection.c, color.c etc.)
int		get_default_color(int z, t_fdf *fdf);
void	free_split(char **split_arr);
int		ft_ishexdigit(char c); // Helper for color parsing
int		ft_atoi_hex(const char *str); // Helper for color parsing

// utils2.c
t_point	project(t_point p, t_fdf *fdf);


#endif // FDF_H
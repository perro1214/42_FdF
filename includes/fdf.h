#ifndef FDF_H
# define FDF_H
# include "../get_next_line/get_next_line.h"
# include "../libft/libft.h"
# include "../minilibx/mlx.h"
# include <fcntl.h>
# include <errno.h>
# include <math.h>
# include <stdio.h>
# include <unistd.h>

# define WIDTH 1920
# define HEIGHT 1080

/* キーコード定義 */
# define ARROW_LEFT 123
# define ARROW_RIGHT 124
# define ARROW_DOWN 125
# define ARROW_UP 126
# define MINUS 27
# define PLUS 24
# define SPACE 49
# define KEY_R 15
# define MOUSE_CLICK_LEFT 1
# define MOUSE_CLICK_RIGHT 2
# define MOUSE_CLICK_MIDDLE 3
# define MOUSE_WHEEL_UP 4
# define MOUSE_WHEEL_DOWN 5
# define ESCAPE 53

/* 点の情報を格納する構造体 */
typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	int	color;
	int	reverse;
}				t_point;

/* マップデータを格納する構造体 */
typedef struct s_map
{
	int	height;
	int	width;
	int	***array;  /* [Y][X][0:Z値, 1:カラー] */
	int	z_max;     /* マップ内の最大高度 */
	int	z_min;     /* マップ内の最小高度 */
}				t_map;

/* カメラ設定を格納する構造体 */
typedef struct s_camera
{
	int		zoom;      /* 拡大率 */
	double	x_angle;   /* X軸周りの回転角度 */
	double	y_angle;   /* Y軸周りの回転角度 */
	double	z_angle;   /* Z軸周りの回転角度 */
	float	z_height;  /* 高さの強調度合い */
	int		x_offset;  /* X方向のオフセット */
	int		y_offset;  /* Y方向のオフセット */
	int		iso;       /* 投影モード（0:平行, 1:等角） */
}				t_camera;

/* マウス状態を格納する構造体 */
typedef struct s_mouse
{
	int		button;    /* 押されているボタン */
	int		x;         /* 現在のX座標 */
	int		y;         /* 現在のY座標 */
	int		prev_x;    /* 前回のX座標 */
	int		prev_y;    /* 前回のY座標 */
}				t_mouse;

/* メイン環境構造体 */
typedef struct s_fdf
{
	void		*mlx;         /* MiniLibX接続 */
	void		*win;         /* ウィンドウ */
	void		*img;         /* イメージ */
	char		*data_addr;   /* ピクセルデータ */
	int			bpp;         /* ピクセルあたりのビット数 */
	int			size_line;   /* 1行あたりのバイト数 */
	int			endian;      /* エンディアン */
	int			steep;       /* 線描画の傾き状態 */
	t_map		*map;        /* マップデータ */
	t_camera	*camera;     /* カメラ設定 */
	t_mouse		*mouse;      /* マウス状態 */
}				t_fdf;

/* マップ解析と検証 */
void	ft_check_valid(char *filename, t_map *map);
void	ft_split_free(char **split);
int		ft_atoi_base(char *str, int base);

/* 描画関連 */
void	ft_draw(t_map *map, t_fdf *env);
void	ft_put_pixel(t_fdf *env, int x, int y, int color);
void	ft_draw_line(t_point s, t_point e, t_fdf *env);
t_point	project(int x, int y, t_fdf *env);

/* ユーティリティ関数 */
int		ft_min(int a, int b);
int		get_default_color(int z, t_map *map);
void	ft_return_error(const char *err_msg, int system_function);
double	ft_reset_angles(double angle);
void	ft_swap(int *a, int *b);

/* 数学・アルゴリズム関連 */
float	ft_abs(float n);
int		ft_ipart(float n);
float	ft_fpart(float n);
float	ft_rfpart(float n);

/* コントロール関連 */
void	ft_hook_controls(t_fdf *env);
int		ft_key_press(int keycode, void *params);
int		ft_mouse_down(int button, int x, int y, void *params);
int		ft_mouse_up(int button, int x, int y, void *params);
int		ft_mouse_move(int x, int y, void *params);
int		ft_close_win(void *params);

#endif
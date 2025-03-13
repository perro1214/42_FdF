#include "fdf.h"

/*
** ft_init - 描画環境の初期化
** @path: 表示するマップファイルのパス
**
** この関数は、MiniLibXグラフィック環境を初期化し、ウィンドウとイメージバッファを
** 作成します。また、マウス追跡のための構造体も初期化します。
** 
** 戻り値: 初期化された環境構造体へのポインタ
*/
static t_fdf	*ft_init(const char *path)
{
	t_fdf	*env;
	char	*title;

	title = ft_strjoin("FdF - ", path);
	env = (t_fdf *)malloc(sizeof(t_fdf));
	if (!env)
		ft_return_error("malloc error", 1);
	env->mlx = mlx_init();
	if (!env->mlx)
		ft_return_error("error connecting to graphics server", 1);
	env->win = mlx_new_window(env->mlx, WIDTH, HEIGHT, title);
	if (!env->win)
		ft_return_error("error initializing window", 1);
	free(title);
	env->img = mlx_new_image(env->mlx, WIDTH, HEIGHT);
	if (!env->img)
		ft_return_error("error initializing image", 1);
	env->data_addr = mlx_get_data_addr(env->img, &env->bpp, &env->size_line,
			&env->endian);
	env->map = NULL;
	env->camera = NULL;
	env->mouse = (t_mouse *)malloc(sizeof(t_mouse));
	if (!env->mouse)
		ft_return_error("error initializing mouse", 1);
	return (env);
}

/*
** ft_map_init - マップ構造体の初期化
**
** マップデータを格納するための構造体を初期化します。
** 
** 戻り値: 初期化されたマップ構造体へのポインタ
*/
static t_map	*ft_map_init(void)
{
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		ft_return_error("error initializing map", 1);
	map->height = 0;
	map->width = 0;
	map->array = NULL;
	map->z_max = 0;
	map->z_min = 0;
	return (map);
}

/*
** ft_camera_init - カメラパラメータの初期化
** @env: FDF環境構造体
**
** カメラの初期設定を行います。ズーム値、回転角度、オフセット、投影モードなどを設定します。
** 適切なズーム値はマップサイズに基づいて計算されます。
**
** 戻り値: 初期化されたカメラ構造体へのポインタ
*/
static t_camera	*ft_camera_init(t_fdf *env)
{
	t_camera	*camera;

	camera = (t_camera *)malloc(sizeof(t_camera));
	if (!camera)
		ft_return_error("error initializing camera", 1);
	camera->zoom = ft_min(WIDTH / env->map->width / 2,
			HEIGHT / env->map->height / 2);
	camera->x_angle = -0.615472907;
	camera->y_angle = -0.523599;
	camera->z_angle = 0.615472907;
	camera->z_height = 1;
	camera->x_offset = 0;
	camera->y_offset = 0;
	camera->iso = 1;
	return (camera);
}

/*
** main - プログラムのエントリポイント
** @argc: コマンドライン引数の数
** @argv: コマンドライン引数の配列
**
** コマンドライン引数からマップファイルを読み込み、FDFプログラムを実行します。
** 環境初期化、マップ読み込み、カメラ設定、イベントフック、描画を行います。
**
** 戻り値: プログラムの終了コード
*/
int	main(int argc, char *argv[])
{
	t_fdf	*env;

	if (argc == 2)
	{
		env = ft_init(argv[1]);
		env->map = ft_map_init();
		ft_check_valid(argv[1], env->map);
		env->camera = ft_camera_init(env);
		ft_hook_controls(env);
		ft_draw(env->map, env);
		mlx_loop(env->mlx);
	}
	else
		ft_return_error("Usage: ./fdf <filename>", 0);
	return (0);
}
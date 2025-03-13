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
		
	/* マップサイズに基づいて適切なズーム値を計算 */
	camera->zoom = ft_min(WIDTH / env->map->width / 2,
			HEIGHT / env->map->height / 2);
			
	/* デフォルトの回転角度を設定（ラジアン単位） */
	camera->x_angle = -0.615472907;  /* 約-35度 */
	camera->y_angle = -0.523599;     /* 約-30度 */
	camera->z_angle = 0.615472907;   /* 約35度 */
	
	/* Z方向の高さ倍率 */
	camera->z_height = 1;
	
	/* 初期位置のオフセット（中心） */
	camera->x_offset = 0;
	camera->y_offset = 0;
	
	/* アイソメトリック投影モードを有効化 */
	camera->iso = 1;
	
	return (camera);
}
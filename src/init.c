#include "fdf.h"

/* @brief Initializes the main fdf structure with default/null values */
void	init_fdf(t_fdf *fdf)
{
	fdf->mlx_ptr = NULL;
	fdf->win_ptr = NULL;
	fdf->img.img_ptr = NULL;
	fdf->img.addr = NULL;
	fdf->map_width = 0;
	fdf->map_height = 0;
	fdf->z_grid = NULL;
	fdf->color_grid = NULL; // Initialize color grid pointer
	fdf->z_min = 0;         // Initialize min/max z
	fdf->z_max = 0;
	// Default view parameters (can be adjusted in calculate_defaults)
	fdf->scale = 20.0f;
	fdf->x_offset = WIN_WIDTH / 3; // Initial guess for centering
	fdf->y_offset = WIN_HEIGHT / 4; // Initial guess for centering
	fdf->angle = 0.5235f; // Approx 30 degrees in radians
}

/* @brief Initializes MiniLibX connection, window, and image buffer */
void	init_mlx(t_fdf *fdf)
{
	fdf->mlx_ptr = mlx_init();
	if (!fdf->mlx_ptr)
		terminate("Error: mlx_init() failed");
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "FdF");
	if (!fdf->win_ptr)
	{
		// cleanup(&fdf); // Partial cleanup if window fails
		terminate("Error: mlx_new_window() failed");
	}
	fdf->img.img_ptr = mlx_new_image(fdf->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (!fdf->img.img_ptr)
	{
		// cleanup(&fdf); // Partial cleanup
		terminate("Error: mlx_new_image() failed");
	}
	fdf->img.addr = mlx_get_data_addr(fdf->img.img_ptr, &fdf->img.bpp,
			&fdf->img.line_len, &fdf->img.endian);
	if (!fdf->img.addr)
	{
		// cleanup(&fdf);
		terminate("Error: mlx_get_data_addr() failed");
	}
}

/* @brief Calculate initial scale and offsets to fit map */
/* @brief Calculate initial scale and offsets using a fixed small scale */
void calculate_defaults(t_fdf *fdf)
{
    float scale_x;
    float scale_y;
    // ★ 目標とするウィンドウ内の占有率 (この値を調整して初期サイズを変更) ★
    float target_ratio = 0.25f; // 例: 0.25 = ウィンドウ幅/高さの 1/4 程度に収める

    // --- マップが読み込まれていない場合のエラーハンドリング (念のため) ---
    if (fdf->map_width <= 0 || fdf->map_height <= 0)
    {
        // デフォルトのスケールとオフセットを設定して予期せぬ動作を防ぐ
        fdf->scale = 10.0f;
        fdf->x_offset = WIN_WIDTH / 2;
        fdf->y_offset = WIN_HEIGHT / 2;
        // エラーメッセージを出すか、そのまま進むかは設計による
        // fprintf(stderr, "Warning: Invalid map dimensions in calculate_defaults.\n");
        return; // ここで処理を中断するのも手
    }

    // --- スケールの自動計算 ---
    // target_ratio に基づいてスケールを計算
    scale_x = (WIN_WIDTH * target_ratio) / fdf->map_width;
    scale_y = (WIN_HEIGHT * target_ratio) / fdf->map_height;

    // X方向とY方向で計算したスケールのうち、小さい方を採用 (全体が収まるように)
    fdf->scale = (scale_x < scale_y) ? scale_x : scale_y;

    // --- スケールの最小値・最大値制限 ---
    // スケールが小さくなりすぎないように最低値を保証 (例: 2.0)
    if (fdf->scale < 3.0f)
        fdf->scale = 3.0f;
    // スケールが大きくなりすぎないように最大値を制限 (任意)
    // if (fdf->scale > 30.0f)
    //     fdf->scale = 30.0f;

    // --- オフセットの計算 (中央配置) ---
    // (注意: この計算は projection 関数の中身に依存します。)

    // 投影後のモデルのおおよその高さを計算 (単純な推定)
    float approx_proj_height = (fdf->map_width + fdf->map_height) * 0.5f * sin(fdf->angle) * fdf->scale;
    // Zによる高さ変化も考慮に入れる (単純に最大/最小差の半分を加味)
    float z_factor = (fdf->z_max - fdf->z_min) * 0.5f * fdf->scale;
    approx_proj_height += z_factor; // Zの高さを加味

    // ウィンドウの中央に配置
    fdf->x_offset = (WIN_WIDTH / 2); // 横方向は中央
    fdf->y_offset = (WIN_HEIGHT / 2) + (approx_proj_height / 3); // 縦方向は少し上寄りに

    // --- より単純な中央配置 (見た目で調整) ---
    // fdf->x_offset = WIN_WIDTH / 2;
    // fdf->y_offset = WIN_HEIGHT / 3; // この値を調整して上下位置を決める

    // --- デバッグ用出力 (任意) ---
    // printf("DEBUG: Calculated scale=%.2f, x_offset=%d, y_offset=%d\n",
    //        fdf->scale, fdf->x_offset, fdf->y_offset);
}

/* @brief Finds min and max Z values (useful for color gradients) */
void	find_z_min_max(t_fdf *fdf)
{
	int	x;
	int	y;

	fdf->z_min = fdf->z_grid[0][0];
	fdf->z_max = fdf->z_grid[0][0];
	y = 0;
	while (y < fdf->map_height)
	{
		x = 0;
		while (x < fdf->map_width)
		{
			if (fdf->z_grid[y][x] < fdf->z_min)
				fdf->z_min = fdf->z_grid[y][x];
			if (fdf->z_grid[y][x] > fdf->z_max)
				fdf->z_max = fdf->z_grid[y][x];
			x++;
		}
		y++;
	}
}

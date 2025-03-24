#include "../includes/fdf.h"

/*
** ft_get_color_component - 2色間の単一成分の補間値を計算
** @start: 開始色の成分（R, G, または B）
** @end: 終了色の成分
** @percentage: 補間の割合（0.0 から 1.0）
**
** 戻り値: 補間された色成分
*/
static int	ft_get_color_component(int start, int end, double percentage)
{
	return (start + (int)((end - start) * percentage));
}

/*
** ft_get_gradient_color - ある割合に応じた2色間のグラデーション色を取得
** @start_color: 開始色（低い値）
** @end_color: 終了色（高い値）
** @percentage: 補間の割合（0.0 から 1.0）
**
** 戻り値: 補間された色
*/
static int	ft_get_gradient_color(int start_color, int end_color, double percentage)
{
	int	r;
	int	g;
	int	b;

	r = ft_get_color_component((start_color >> 16) & 0xFF, 
			(end_color >> 16) & 0xFF, percentage);
	g = ft_get_color_component((start_color >> 8) & 0xFF, 
			(end_color >> 8) & 0xFF, percentage);
	b = ft_get_color_component(start_color & 0xFF, 
			end_color & 0xFF, percentage);
	return ((r << 16) | (g << 8) | b);
}

/*
** ft_get_color_by_height - 高さに応じた色を決定
** @z: 現在の高さ値
** @z_min: マップの最小高さ
** @z_max: マップの最大高さ
**
** 戻り値: 高さに応じた色
*/
int	ft_get_color_by_height(int z, int z_min, int z_max)
{
	double	percentage;
	int		color;

	// 高さの範囲が0の場合（平坦なマップ）
	if (z_max == z_min)
		return (0x00FFFFFF); // 白色

	// 高さの割合を計算（0.0〜1.0）
	percentage = (double)(z - z_min) / (z_max - z_min);
	
	// マルチカラーグラデーション（低→高：青→緑→黄→赤）
	if (percentage < 0.2)
		color = ft_get_gradient_color(0x0000FF, 0x00FFFF, percentage * 5); // 青→水色
	else if (percentage < 0.4)
		color = ft_get_gradient_color(0x00FFFF, 0x00FF00, (percentage - 0.2) * 5); // 水色→緑
	else if (percentage < 0.6)
		color = ft_get_gradient_color(0x00FF00, 0xFFFF00, (percentage - 0.4) * 5); // 緑→黄
	else if (percentage < 0.8)
		color = ft_get_gradient_color(0xFFFF00, 0xFF7F00, (percentage - 0.6) * 5); // 黄→オレンジ
	else
		color = ft_get_gradient_color(0xFF7F00, 0xFF0000, (percentage - 0.8) * 5); // オレンジ→赤

	return (color);
}

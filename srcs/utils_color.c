
#include "fdf.h"

/*
** get_default_color - 高さ値に基づくデフォルトカラーを取得
** @z: 点の高さ（Z値）
** @map: マップ構造体
**
** 点の高さ（Z値）に基づいて色を決定します。
** Z値の最小値から最大値までの範囲を正規化し、
** 低い値から高い値までのグラデーションカラーを生成します。
**
** 戻り値: 計算された色（RGB値）
*/
int	get_default_color(int z, t_map *map)
{
	double	percentage;

	/* Z値が一定の場合（平らなマップ） */
	if (map->z_max == map->z_min)
		return (0xFFFFFF);  /* 白色を返す */
		
	/* Z値を0〜1の範囲に正規化 */
	percentage = (double)(z - map->z_min) / (map->z_max - map->z_min);
	
	/* 正規化した値に基づいて色を決定（青→シアン→緑→黄→赤のグラデーション） */
	if (percentage < 0.2)
		return (0x0000FF);  /* 青 (低い高度) */
	else if (percentage < 0.4)
		return (0x00FFFF);  /* シアン */
	else if (percentage < 0.6)
		return (0x00FF00);  /* 緑 */
	else if (percentage < 0.8)
		return (0xFFFF00);  /* 黄色 */
	else
		return (0xFF0000);  /* 赤 (高い高度) */
}
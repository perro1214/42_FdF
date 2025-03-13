#include "fdf.h"

/*
** ft_abs - 浮動小数点数の絶対値を計算
** @n: 対象の浮動小数点数
**
** 戻り値: nの絶対値
*/
float	ft_abs(float n)
{
	if (n < 0)
		return (-n);
	return (n);
}

/*
** ft_swap - 2つの整数値を交換
** @a: 1つ目の整数へのポインタ
** @b: 2つ目の整数へのポインタ
*/
void	ft_swap(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

/*
** ft_ipart - 浮動小数点数の整数部分を取得
** @n: 対象の浮動小数点数
**
** 戻り値: nの整数部分
*/
int	ft_ipart(float n)
{
	return ((int)n);
}

/*
** ft_fpart - 浮動小数点数の小数部分を取得
** @n: 対象の浮動小数点数
**
** 戻り値: nの小数部分 (0.0〜1.0未満)
*/
float	ft_fpart(float n)
{
	return (n - ft_ipart(n));
}

/*
** ft_rfpart - 浮動小数点数の逆小数部分を取得（1-小数部分）
** @n: 対象の浮動小数点数
**
** 戻り値: 1-nの小数部分 (0.0〜1.0未満)
*/
float	ft_rfpart(float n)
{
	return (1 - ft_fpart(n));
}
#include "fdf.h"

/*
** ft_atoi_base - 指定された基数で文字列を整数に変換
** @str: 変換する文字列
** @base: 変換の基数 (通常は16進数の場合16)
**
** 戻り値: 変換された整数値
*/
int	ft_atoi_base(char *str, int base)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	if (*str == '0' && (*(str + 1) == 'x' || *(str + 1) == 'X'))
		str += 2;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			result = result * base + (*str - '0');
		else if (*str >= 'A' && *str <= 'F')
			result = result * base + (*str - 'A' + 10);
		else if (*str >= 'a' && *str <= 'f')
			result = result * base + (*str - 'a' + 10);
		else
			break ;
		str++;
	}
	return (result * sign);
}

/*
** ft_split_free - ft_splitによって作成された文字列配列を解放
** @split: 解放する文字列配列
*/
void	ft_split_free(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}
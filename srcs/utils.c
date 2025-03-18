/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: perro1214 <perro1214@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-17 17:40:00 by perro1214         #+#    #+#             */
/*   Updated: 2025-03-17 17:40:00 by perro1214        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

/*
** ft_return_error - エラーメッセージを表示して終了
*/
void	ft_return_error(char *str, int exit_code)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(str, 2);
	exit(exit_code);
}

/*
** ft_split_free - splitで確保された文字列配列を解放
*/
void	ft_split_free(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

/*
** ft_atoi_base - 文字列を指定した基数の整数に変換
*/
int	ft_atoi_base(char *str, int base)
{
	int	result;
	int	sign;
	int	digit;

	result = 0;
	sign = 1;
	if (*str == '0' && (*(str + 1) == 'x' || *(str + 1) == 'X'))
		str += 2;
	else if (*str == '-')
	{
		sign = -1;
		str++;
	}
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			digit = *str - '0';
		else if (*str >= 'a' && *str <= 'f')
			digit = *str - 'a' + 10;
		else if (*str >= 'A' && *str <= 'F')
			digit = *str - 'A' + 10;
		else
			break ;
		if (digit >= base)
			break ;
		result = result * base + digit;
		str++;
	}
	return (sign * result);
}

/*
** ft_max - 2つの整数の最大値を返す
*/
int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

/*
** ft_min - 2つの整数の最小値を返す
*/
int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

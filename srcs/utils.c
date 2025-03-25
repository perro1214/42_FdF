/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhayato@student.42.fr <hhayato>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:40:00 by perro1214         #+#    #+#             */
/*   Updated: 2025/03/25 20:27:09 by hhayato@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

/*
** err_exit - エラーメッセージを表示して終了
*/
void	err_exit(char *str, int exit_code)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(str, 2);
	exit(exit_code);
}

/*
** free_split - splitで確保された文字列配列を解放
*/
void	free_split(char **split)
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

static int get_val(char c, int base)
{
    int digit;

    if (c >= '0' && c <= '9')
        digit = c - '0';
    else if (c >= 'a' && c <= 'f')
        digit = c - 'a' + 10;
    else if (c >= 'A' && c <= 'F')
        digit = c - 'A' + 10;
    else
        return (-1); // Invalid digit

    if (digit >= base)
        return (-1); // Digit out of range for the given base
    return (digit);
}

/*
** ft_atoi_base - 文字列を指定した基数の整数に変換
*/
int	ft_atoi_base(char *str, int base)
{
	int	result = 0;
	int	sign = 1;
    int digit;

	if (*str == '0' && (*(str + 1) == 'x' || *(str + 1) == 'X'))
		str += 2;
	else if (*str == '-')
	{
		sign = -1;
		str++;
	}
	while (*str)
	{
        digit = get_val(*str, base);
        if (digit == -1)
            break;
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

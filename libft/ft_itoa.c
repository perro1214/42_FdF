/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhayato <hhayato@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:00:55 by hhayato           #+#    #+#             */
/*   Updated: 2024/11/09 13:08:13 by hhayato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_size(int n)
{
	int	ans;

	ans = 0;
	while (n <= 0)
	{
		ans++;
		n = n * -1;
	}
	while (n != 0)
	{
		n /= 10;
		ans++;
	}
	return (ans);
}

static void	make_ans(int n, char *ans, int len)
{
	ans[len] = '\0';
	while (0 < len)
	{
		ans[len - 1] = n % 10 + '0';
		n /= 10;
		len--;
	}
}

static char	*max_zero(int n)
{
	char	*ans;

	if (n == -2147483648)
	{
		ans = ft_strdup("-2147483648");
		if (ans == NULL)
			return (NULL);
	}
	else
	{
		ans = ft_strdup("0");
		if (ans == NULL)
			return (NULL);
	}
	return (ans);
}

char	*ft_itoa(int n)
{
	char	*ans;
	int		len;

	if (n == -2147483648 || n == 0)
	{
		ans = max_zero(n);
	}
	else
	{
		len = count_size(n);
		ans = (char *)malloc(sizeof(char) * (len + 1));
		if (!ans)
			return (NULL);
		if (n < 0)
		{
			ans[0] = '-';
			n = -n;
			make_ans(n, &ans[1], len - 1);
		}
		else
			make_ans(n, ans, len);
	}
	return (ans);
}

// int main(void){
// 	char *i1 = ft_itoa(0);
// 	printf("%s\n",i1);
// 	// if (i1)
// 	// {
// 	// 	printf("%s","TEST_FAILED");
// 	// }else{
// 	// 	printf("%s","TEST_SUCCESS");
// 	// }
// }
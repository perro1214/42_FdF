/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhayato <hhayato@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:48:52 by hhayato           #+#    #+#             */
/*   Updated: 2024/10/30 17:43:33 by hhayato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *string)
{
	char	*c_s;
	int		ans;
	int		pm;

	ans = 0;
	pm = 1;
	c_s = (char *)string;
	while (*c_s == '\t' || *c_s == '\r' || *c_s == ' ' || *c_s == '\f'
		|| *c_s == '\v' || *c_s == '\n')
		++c_s;
	if (*c_s == '-' || *c_s == '+')
	{
		if (*c_s == '-')
			pm *= -1;
		c_s++;
	}
	while ('0' <= *c_s && *c_s <= '9')
	{
		ans *= 10;
		ans += *c_s - '0';
		c_s++;
	}
	return (ans * pm);
}

// int main(void){
//     int ans = atoi("--2147483648");
//     printf("org__%d\n",ans);
//     ans = ft_atoi("--2147483648");
//     printf("ft___%d\n",ans);
// }
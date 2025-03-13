/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhayato <hhayato@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:03:11 by hhayato           #+#    #+#             */
/*   Updated: 2024/10/30 16:06:39 by hhayato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ans;
	char	ch;

	ans = (char *)s;
	ch = (char)c;
	while (*ans != '\0')
		ans++;
	while (ans != s)
	{
		if (ch == *ans)
			return (ans);
		ans--;
	}
	if (*ans == ch)
		return (ans);
	else
		return (NULL);
}

// int	main(void)
// {
// 	char *a;
// 	a = ft_strrchr("zabcdef/fedcba", 'd');
// 	printf("%s", a);
// }
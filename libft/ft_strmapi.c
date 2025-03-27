/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhayato <hhayato@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:06:16 by hhayato           #+#    #+#             */
/*   Updated: 2024/11/03 17:52:00 by hhayato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*now;
	size_t	len;
	size_t	i;

	if (s == 0)
		return (ft_strdup(""));
	len = ft_strlen(s);
	now = (char *)malloc(sizeof(char) * (len + 1));
	if (!now)
		return (NULL);
	i = 0;
	while (i < len)
	{
		now[i] = (*f)(i, s[i]);
		i++;
	}
	now[i] = 0;
	return (now);
}

// char	test(unsigned int i, char s)
// {
// 	s = i+'a';
//     return (s);
// }
// int	main(void)
// {
// 	char	str[] = "zzzzzzzzzz";
// 	printf("%s\n",ft_strmapi(str, test));
// }
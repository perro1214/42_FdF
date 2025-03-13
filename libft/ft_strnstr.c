/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhayato <hhayato@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 19:07:22 by hhayato           #+#    #+#             */
/*   Updated: 2024/10/30 19:07:24 by hhayato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;

	if (*little == '\0')
		return ((char *)big);
	i = ft_strlen(little);
	if (len == 0)
		return (0);
	while (*big != '\0' && i <= len)
	{
		if (*big == *little && ft_strncmp(big, little, i) == 0)
			return ((char *)big);
		big++;
		len--;
	}
	return (NULL);
}

// #include <string.h>
// int main(void){
//     const char *largestring = "Foo Bar Baz";
//     const char *smallstring = "Bar";
//     char *ptr;
//     int n = strlen(largestring);

//     ptr = strnstr(largestring, smallstring,n);
//     printf("org_:%s\n",ptr);
//     ptr = ft_strnstr(largestring, smallstring,n);
//     printf("ft_:%s\n",ptr);
// }
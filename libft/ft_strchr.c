/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhayato <hhayato@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:36:40 by hhayato           #+#    #+#             */
/*   Updated: 2024/11/12 13:53:46 by hhayato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	ch;

	ch = (char)c;
	while (*s && *s != ch)
		s++;
	if (*s == ch)
		return ((char *)s);
	return (NULL);
}

// int main(void){
// 	char s[] = "tripouille";
// 	printf("%s\n",ft_strchr(s, 't' + 256));
// 	printf("%s\n",strchr(s, 't' + 256));
// 	if(ft_strchr(s, 't' + 256) == strchr(s, 't' + 256))
// 		printf("%s","Yes");
// }

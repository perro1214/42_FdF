/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhayato <hhayato@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:03:52 by hhayato           #+#    #+#             */
/*   Updated: 2024/11/03 17:44:52 by hhayato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*d;
	const char	*s;

	d = (char *)dst;
	s = (char *)src;
	if (!dst && !src)
		return (NULL);
	if (d[0] == '\0' && s[0] == '\0')
		return (dst);
	if (dst < src)
	{
		return (ft_memcpy(dst, src, len));
	}
	while (len--)
		d[len] = s[len];
	return (dst);
}

// int main(void){
//     char str[] = "abcdefghijklmn";
//     //char ans[15];
//     ft_memmove(&str[0],&str[3],7);
//     //ans[14]='\0';
//     int i=0;
//     while (str[i]!='\0')
//     {
//         write(1,&str[i],1);
//         i++;
//     }

//     return (0);
// }
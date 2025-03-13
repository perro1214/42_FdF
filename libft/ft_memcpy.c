/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhayato <hhayato@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:03:44 by hhayato           #+#    #+#             */
/*   Updated: 2024/11/03 17:44:43 by hhayato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t len)
{
	char		*d;
	const char	*s;
	size_t		i;

	if (!src && !dst)
		return (dst);
	d = dst;
	s = src;
	if (d[0] == '\0' && s[0] == '\0')
	{
		return (dst);
	}
	i = 0;
	while (i < len)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}

// int main(){
//     char str[] = "abcdefghijklmn";
//     char ans[16];
//     ft_memcpy(ans,str,16);
// 	ft_memcpy("            ", ((void*)0), 17);
// 	memcpy("            ", ((void*)0), 17);
//     return (0);
// }
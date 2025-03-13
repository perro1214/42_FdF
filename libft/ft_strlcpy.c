/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhayato <hhayato@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:06:03 by hhayato           #+#    #+#             */
/*   Updated: 2024/10/30 16:06:04 by hhayato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	if (size == 0)
		return (ft_strlen(src));
	i = 0;
	while (src[i] != '\0' && (i < size - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (ft_strlen(src));
}

// int main(void){
// 	char src[] = "coucou";
// 	char dest[10]; memset(dest, 'A', 10);
// 	int ans;
// 	ans = ft_strlcpy(dest, src, 1);
// 	printf("%d",ans);
// 	printf("%s",dest);
//     return (0);
// }
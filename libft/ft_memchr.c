/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhayato <hhayato@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:33:08 by hhayato           #+#    #+#             */
/*   Updated: 2024/11/12 13:46:34 by hhayato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *buf, int ch, size_t n)
{
	unsigned char	*c_buf;
	unsigned char	c_ch;

	c_ch = (unsigned char)ch;
	c_buf = (unsigned char *)buf;
	while ((size_t)0 < n)
	{
		if (*c_buf == c_ch)
			return ((void *)(c_buf));
		n--;
		c_buf++;
	}
	return (NULL);
}

// int	main(void)
// {
// 	char s[] = {0, 1, 2 ,3 ,4 ,5};
// 	char *a;
// 	a = ft_memchr(s,2 + 256,3);
// 	printf("%s", a);
// }
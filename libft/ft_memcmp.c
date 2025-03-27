/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhayato <hhayato@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:58:34 by hhayato           #+#    #+#             */
/*   Updated: 2024/10/30 16:58:35 by hhayato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *buf1, const void *buf2, size_t n)
{
	unsigned char	*c_buf1;
	unsigned char	*c_buf2;

	c_buf1 = (unsigned char *)buf1;
	c_buf2 = (unsigned char *)buf2;
	while (0 < n && *c_buf1 == *c_buf2)
	{
		c_buf1++;
		c_buf2++;
		n--;
	}
	if (0 < n)
		return (*c_buf1 - *c_buf2);
	else
		return (0);
}

// int main(void)
// {
//         char buf1[] = "\0abc\0de";      /* 途中に空文字のある文字列 */
//         char buf2[] = "\0abc\0de";
//         char buf3[] = "\0abcdef";

//         if (ft_memcmp(buf1, buf2, 7) == 0)
//                 printf("buf1 = buf2\n");
//         else
//                 printf("buf1 != buf2\n");

//         if (ft_memcmp(buf1, buf3, 7) == 0)
//                 printf("buf1 = buf3\n");
//         else
//                 printf("buf1 != buf3\n");

//         return (0);
// }
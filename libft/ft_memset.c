/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhayato <hhayato@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:04:00 by hhayato           #+#    #+#             */
/*   Updated: 2024/10/30 16:04:01 by hhayato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;
	char	*string;

	string = (char *)s;
	i = 0;
	while (i < n)
	{
		string[i] = c;
		i++;
	}
	return (s);
}

// int main(void){
//     char c[]="aaaaaaa";
//     int i = 0;
//     while(c[i] != '\0'){
//         write(1,&c[i],1);
//         i++;
//     }
//     write(1,"\n",1);
//     ft_memset(c,'q',4);
//     i = 0;
//     while(c[i] != '\0'){
//         write(1,&c[i],1);
//         i++;
//     }
// }
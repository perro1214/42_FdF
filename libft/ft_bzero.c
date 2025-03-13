/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhayato <hhayato@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:49:13 by hhayato           #+#    #+#             */
/*   Updated: 2024/10/30 15:49:14 by hhayato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *b, size_t len)
{
	size_t	i;
	char	*string;

	string = (char *)b;
	i = 0;
	while (i < len)
	{
		string[i] = 0;
		i++;
	}
}

// int main(void){
//     char c[]="aaaaaaa";
//     ft_bzero(c,0);
//     return (0);
// }
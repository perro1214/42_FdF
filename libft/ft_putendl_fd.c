/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhayato <hhayato@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:04:17 by hhayato           #+#    #+#             */
/*   Updated: 2024/10/30 16:04:18 by hhayato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *c, int fd)
{
	while (*c != '\0')
	{
		write(fd, c, 1);
		c++;
	}
	write(fd, "\n", 1);
}

// int main(void){
//     char *a;
//     a = "abcdef";
//     ft_putendl_fd(a,1);
// }
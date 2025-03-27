/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhayato <hhayato@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:00:33 by hhayato           #+#    #+#             */
/*   Updated: 2024/10/30 16:00:46 by hhayato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	return (32 <= c && c <= 126);
}

// int main(void){
//     if(ft_isascii('a')==1){
//         write(1,"Yes1",4);
//     }
//     if(ft_isascii('A')==1){
//         write(1,"Yes2",4);
//     }
//     if(ft_isascii('1')==1){
//         write(1,"Yes3",4);
//     }
//     if(ft_isascii(1)==1){
//         write(1,"Yes4",4);
//     }
//     if(ft_isascii(200)==1){
//         write(1,"Yes5",4);
//     }
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhayato <hhayato@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:50:10 by hhayato           #+#    #+#             */
/*   Updated: 2024/10/30 16:00:05 by hhayato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	return (0 <= c && c <= 127);
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

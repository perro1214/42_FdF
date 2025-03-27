/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhayato <hhayato@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:06:10 by hhayato           #+#    #+#             */
/*   Updated: 2024/10/30 18:30:30 by hhayato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	int	result;

	result = 0;
	while (str[result] != '\0')
	{
		result++;
	}
	return (result);
}

// int main(void){
//     char *c=NULL;
//     int ans;
//     ans = ft_strlen(c);
//     if(ans==4);
//         write(1,"Yes1",4);
// }
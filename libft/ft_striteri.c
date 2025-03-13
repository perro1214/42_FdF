/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhayato <hhayato@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:05:36 by hhayato           #+#    #+#             */
/*   Updated: 2024/10/30 18:39:25 by hhayato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int	i;

	i = 0;
	if (!s)
		return ;
	if (s[0] == '\0')
		return ;
	while (s[i] != '\0')
	{
		(*f)(i, &s[i]);
		i++;
	}
}

// void	test(unsigned int i, char *str)
// {
// 	*str += i;
// }

// int	main(void)
// {
// 	char *str = NULL;
// 	ft_striteri(str, test);
// 	printf("%s", str);
// }
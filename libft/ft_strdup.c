/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhayato <hhayato@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:05:17 by hhayato           #+#    #+#             */
/*   Updated: 2024/11/09 13:09:20 by hhayato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		n;
	char	*result;

	n = ft_strlen(s);
	result = (char *)malloc(n + 1);
	if (result == NULL)
		return (NULL);
	ft_memcpy(result, s, n + 1);
	return (result);
}

// int	main(void)
// {
// 	char *string = NULL;
// 	char *newstr;

// 	if ((newstr = ft_strdup(string)) != NULL)
// 	{
// 		printf("The new string is: %s\n", newstr);
// 		printf("%s\n", newstr);
// 		free(newstr);
// 	}
// 		char *str;
// 	char *tmp = "HAHAHA \0 tu me vois pas !";

// 	str = ft_strdup(tmp);
// 	if (strcmp(str, tmp)){
// 		free(str);
// 		return (0);
// 	}else{
// 		free(str);
// 	}
// 	printf("%s","TEST_SUCCESS");
// 	return (0);
// }
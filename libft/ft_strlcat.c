/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhayato <hhayato@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:05:54 by hhayato           #+#    #+#             */
/*   Updated: 2024/11/09 13:09:26 by hhayato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	over(size_t *i, size_t size, char *s1, const char *s2)
{
	while (*i < size && s2[*i] != '\0')
	{
		s1[*i] = s2[*i];
		(*i)++;
	}
}

size_t	ft_strlcat(char *s1, const char *s2, size_t size)
{
	size_t	i;
	size_t	s1_size;
	size_t	s2_size;

	i = 0;
	if (s1 == NULL && s2 == NULL)
		return (0);
	if (s1 == NULL)
	{
		over(&i, size, s1, s2);
		return (i);
	}
	s1_size = ft_strlen(s1);
	s2_size = ft_strlen(s2);
	if (size <= s1_size)
		return (size + s2_size);
	while (s2[i] && s1_size + i < size - 1)
	{
		s1[s1_size + i] = s2[i];
		i++;
	}
	s1[s1_size + i] = 0;
	return (s1_size + s2_size);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char str1[30] = "ABC";

// 	ft_strlcat(str1, "aaa", 4); /* 文字型配列に文字型配列を連結 */
// 	printf("%s\n", str1);

// 	ft_strlcat(str1, "aaa", 7); /* 文字型配列にポインタの指す文字列リテラルを連結 */
// 	printf("%s\n", str1);

// 	char str2[30] = "ABC";
// 	ft_strlcat(str2, "", 2); /* 文字型配列に文字列リテラルを連結 */
// 	printf("%s\n", str2);

// 	char str3[30] = "ABC";
// 	ft_strlcat(str3, "", 4); /* 文字型配列に文字列リテラルを連結 */
// 	printf("%s\n", str3);

// 	char str4[30] = "ABC";
// 	ft_strlcat(str4, "", 3); /* 文字型配列に文字列リテラルを連結 */
// 	printf("%s\n", str4);

// 	char dest[30]; memset(dest, 0, 30);
// 	char * src = (char *)"AAAAAAAAA";
// 	memset(dest, 0, 30);
// 	int ans;
// 	ans = ft_strlcat(dest, "123", 3);
// 	printf("%s\n",dest);
// 	printf("%d\n",ans);
// 	if(!strcmp(dest, "12"))
// 		printf("%s","true");

// 	return (0);
// }

// int main(void){
// 	char b[0xF] = "nyan !";

// 	ft_strlcat(((void*)0), b, 0);
// 	printf("%s","TEST_SUCCESS");
// }
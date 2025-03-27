/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhayato <hhayato@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:06:53 by hhayato           #+#    #+#             */
/*   Updated: 2024/10/30 16:06:53 by hhayato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	size;

	if (!s)
		return (NULL);
	if (ft_strlen(s) <= start)
		return (ft_strdup(""));
	size = ft_strlen(s + start);
	if (size < len)
		len = size;
	result = (char *)malloc((sizeof(char) * (len + 1)));
	if (!result)
		return (NULL);
	ft_strlcpy(result, s + start, len + 1);
	return (result);
}

// int main() {
//     char source[] = "12345ABCDE";
//     //char destination[6];  // 切り出す数の分だけの配列を用意

//     // 文字列から5文字分切り出す

//     // 切り出した文字列を表示
//     printf("切り出した数：%s\n",ft_substr(source, 0, 3) );

//     return (0);
// }
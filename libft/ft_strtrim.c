/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhayato <hhayato@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:06:45 by hhayato           #+#    #+#             */
/*   Updated: 2024/11/03 17:29:32 by hhayato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ans;
	size_t	start;
	size_t	end;

	if (s1 == NULL)
		return (NULL);
	start = 0;
	end = ft_strlen(s1) - 1;
	while (s1[start] && ft_strchr(set, s1[start]) != 0)
		start++;
	while (s1[end] && ft_strchr(set, s1[end]) != 0)
		end--;
	ans = ft_substr(s1, start, end - start + 1);
	return (ans);
}

// int main(void){
//     char	str[] = "aaaa/bbbb/cccc/dddd/eeee/?";
//     char *ans;
//     ans = ft_strtrim(str, "abcde?");
//     printf("ft1::%s\n",ans);
//     ans = ft_strtrim(str, "a/b?e");
//     printf("ft2::%s\n",ans);
//     ans = ft_strtrim(str, "abde?/");
//     printf("ft3::%s\n",ans);
// }

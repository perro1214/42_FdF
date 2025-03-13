/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhayato <hhayato@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 20:35:17 by hhayato           #+#    #+#             */
/*   Updated: 2024/12/04 16:40:29 by hhayato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (0);
	while (*s && *s != c)
		s++;
	if (*s == c)
		return ((char *)s);
	return (NULL);
}

size_t	ft_strlen(const char *str)
{
	size_t	result;

	result = 0;
	while (str[result] != '\0')
	{
		result++;
	}
	return (result);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	if (size == 0)
		return (ft_strlen(src));
	i = 0;
	while (src[i] != '\0' && (i < size - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (ft_strlen(src));
}

char	*ft_strdup(const char *s)
{
	int		n;
	char	*result;

	n = ft_strlen(s);
	result = (char *)malloc(sizeof(char));//, n + 1);
	if (result == NULL)
		return (NULL);
	ft_strlcpy(result, s, n + 1);
	return (result);
}


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
	result = (char *)malloc(sizeof(char));//, (len + 1));
	if (!result)
		return (NULL);
	ft_strlcpy(result, s + start, len + 1);
	return (result);
}

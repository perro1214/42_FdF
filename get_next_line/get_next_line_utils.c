/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhayato <hhayato@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 20:35:17 by hhayato           #+#    #+#             */
/*   Updated: 2025/01/07 13:50:40 by hhayato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

void	*ft_memcpy(void *dst, const void *src, size_t len)
{
	char		*d;
	const char	*s;
	size_t		i;

	if (!src && !dst)
		return (dst);
	d = (char *)dst;
	s = (const char *)src;
	if (d[0] == '\0' || s[0] == '\0')
	{
		return (dst);
	}
	i = 0;
	while (i < len)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
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

char	*ft_strdup(const char *s)
{
	int		n;
	char	*result;

	n = ft_strlen(s);
	result = (char *)ft_calloc(sizeof(char), n + 1);
	if (result == NULL)
		return (NULL);
	ft_memcpy(result, s, n + 1);
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
	result = (char *)ft_calloc(sizeof(char), (len + 1));
	if (!result)
		return (NULL);
	ft_strlcpy(result, s + start, len + 1);
	return (result);
}

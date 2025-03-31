/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhayato@student.42.fr <hhayato>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 20:35:17 by hhayato           #+#    #+#             */
/*   Updated: 2025/03/30 22:40:22 by hhayato@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*gnl_strchr(const char *str, int c)
{
	int		i;
	char	*new;

	if (!str || !c)
		return (NULL);
	i = 0;
	new = (char *)str;
	while (new[i])
	{
		if (new[i] == (char) c)
			return (&new[i]);
		i++;
	}
	return (0);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!s1)
	{
		s1 = malloc(sizeof(char));
		s1[0] = '\0';
	}
	str = malloc(sizeof(char) * ((gnl_strlen(s1) + gnl_strlen(s2)) + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	return (str);
}

char	*gnl_substr(char const *s, unsigned int start, size_t len)
{
	char			*substr;
	size_t			i;
	unsigned int	slen;

	if (!s)
		return (NULL);
	slen = gnl_strlen(s);
	if (((slen - start) > len) && (start < slen))
		substr = malloc((len * sizeof(char) + 1));
	else if (start > slen)
		substr = malloc(sizeof(char));
	else
		substr = malloc(((slen - start) * sizeof(char) + 1));
	if (!substr)
		return (NULL);
	i = 0;
	if ((start < slen))
	{
		while ((i < len) && s[start])
			substr[i++] = s[start++];
	}
	substr[i] = '\0';
	return (substr);
}

int	gnl_endl(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (str[i] == '\n')
		return (1);
	return (0);
}
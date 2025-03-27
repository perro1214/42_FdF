/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhayato <hhayato@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:04:42 by hhayato           #+#    #+#             */
/*   Updated: 2024/11/03 17:45:04 by hhayato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_allocate(char **tab, char const *s, char charset)
{
	char		**m_tab;
	char const	*now_p;

	now_p = s;
	m_tab = tab;
	while (*now_p)
	{
		while (*s == charset)
			++s;
		now_p = s;
		while (*now_p && *now_p != charset)
			++now_p;
		if (*now_p == charset || now_p > s)
		{
			*m_tab = ft_substr(s, 0, now_p - s);
			s = now_p;
			++m_tab;
		}
	}
	*m_tab = NULL;
}

int	ft_count_words(char const *str, char charset)
{
	int	word_count;

	word_count = 0;
	while (*str)
	{
		while (*str == charset)
			++str;
		if (*str)
			++word_count;
		while (*str && *str != charset)
			++str;
	}
	return (word_count);
}

char	**ft_split(char const *str, char charset)
{
	char	**new;
	int		size;

	if (!str)
		return (NULL);
	size = ft_count_words(str, charset);
	new = (char **)malloc(sizeof(char *) * (size + 1));
	if (!new)
		return (NULL);
	ft_allocate(new, str, charset);
	return (new);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	**ans;
// 	char	*str;
// 	char	charset;
// 	int		i;

// 	str = ",,,aaa,bbb,ccc,";
// 	// str = ",,,,,";
// 	charset = ',';
// 	ans = ft_split(str, charset);
// 	i = 0;
// 	printf("%d\n", len(str, charset));
// 	while (i < len(str, charset) + 1)
// 	{
// 		printf("%d::::%s\n", i, ans[i]);
// 		i++;
// 	}
// 	char * * tab;
// 	tab = ft_split("", ' ');
// 	printf("%s",tab[0]);
// }

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

/*
** ft_strchr - 文字列の中から指定した文字を探す
** @s: 検索対象の文字列
** @c: 検索する文字
**
** 戻り値: 見つかった場合はその位置のポインタ、見つからなければNULL
*/
char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

/*
** ft_strlen - 文字列の長さを取得
** @str: 測定する文字列
**
** 戻り値: 文字列の長さ（ヌル終端文字を除く）
*/
size_t	ft_strlen(const char *str)
{
	size_t	result;

	if (!str)
		return (0);
	result = 0;
	while (str[result])
		result++;
	return (result);
}

/*
** ft_strlcpy - 文字列をコピー（サイズ制限あり）
** @dst: コピー先バッファ
** @src: コピー元文字列
** @size: コピー先バッファのサイズ
**
** 戻り値: コピー元文字列の長さ
*/
size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	src_len;

	if (!dst || !src)
		return (0);
	src_len = ft_strlen(src);
	if (size == 0)
		return (src_len);
	i = 0;
	while (src[i] && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_len);
}

/*
** ft_strdup - 文字列の複製
** @s: 複製する文字列
**
** 戻り値: 複製された新しい文字列
*/
char	*ft_strdup(const char *s)
{
	char	*result;
	size_t	len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	ft_strlcpy(result, s, len + 1);
	return (result);
}

/*
** ft_substr - 文字列の一部を抽出
** @s: 元の文字列
** @start: 抽出開始位置
** @len: 抽出する最大長
**
** 戻り値: 抽出された新しい文字列
*/
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (s_len <= start)
		return (ft_strdup(""));
	if (s_len - start < len)
		len = s_len - start;
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	ft_strlcpy(result, s + start, len + 1);
	return (result);
}
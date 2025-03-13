/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhayato <hhayato@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:48:23 by hhayato           #+#    #+#             */
/*   Updated: 2024/12/04 18:08:46 by hhayato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

// void	*ft_calloc(size_t n, size_t size)
// {
// 	void	*result;
// 	char	*c_r;
// 	size_t	i;

// 	if (n == 0 || size == 0)
// 	{
// 		result = malloc(0);
// 		return (result);
// 	}
// 	if (((__SIZE_MAX__ / n) < size))
// 	{
// 		return (NULL);
// 	}
// 	result = malloc(n * size);
// 	if (!result)
// 		return (NULL);
// 	i = (size_t)0;
// 	c_r = result;
// 	while (i < size)
// 	{
// 		c_r[i++] = 0;
// 	}
// 	return (result);
// }

/*
** gnl_strjoin - 2つの文字列を結合し、最初の文字列を解放
** @s1: 最初の文字列（解放される）
** @s2: 2つ目の文字列
**
** 戻り値: 結合された新しい文字列へのポインタ
*/
char	*gnl_strjoin(char *s1, char const *s2)
{
	char	*result;
	size_t	i;
	size_t	j;

	if (!s1)
	{
		s1 = (char *)malloc(sizeof(char));
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	result = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!result)
		return (NULL);
	i = -1;
	while (s1[++i])
		result[i] = s1[i];
	j = 0;
	while (s2[j])
		result[i++] = s2[j++];
	result[i] = '\0';
	free(s1);
	return (result);
}

/*
** get_line - ファイルから改行が見つかるまで読み込む
** @fd: ファイルディスクリプタ
** @left_str: 前回の呼び出しで残った文字列
**
** 戻り値: 読み込んだすべての文字列
*/
static char	*get_line(int fd, char *left_str)
{
	char	*buffer;
	ssize_t	read_bytes;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	read_bytes = 1;
	while (read_bytes > 0 && (!left_str || !ft_strchr(left_str, '\n')))
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buffer);
			if (left_str)
				free(left_str);
			return (NULL);
		}
		buffer[read_bytes] = '\0';
		left_str = gnl_strjoin(left_str, buffer);
		if (!left_str)
		{
			free(buffer);
			return (NULL);
		}
	}
	free(buffer);
	return (left_str);
}

/*
** extract_line - バッファから現在の行を抽出
** @left_str: 処理するバッファ
**
** 戻り値: バッファから抽出された1行
*/
static char	*extract_line(char *left_str)
{
	char	*line;
	size_t	i;

	if (!left_str || !left_str[0])
		return (NULL);
	i = 0;
	while (left_str[i] && left_str[i] != '\n')
		i++;
	if (left_str[i] == '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (left_str[i] && left_str[i] != '\n')
	{
		line[i] = left_str[i];
		i++;
	}
	if (left_str[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

/*
** new_left_str - 次の読み込みのために残りの文字列を保存
** @left_str: 処理するバッファ
**
** 戻り値: 現在の行を除いた残りの文字列
*/
static char	*new_left_str(char *left_str)
{
	char	*new_str;
	size_t	i;
	size_t	j;

	if (!left_str)
		return (NULL);
	i = 0;
	while (left_str[i] && left_str[i] != '\n')
		i++;
	if (left_str[i] == '\0')
	{
		free(left_str);
		return (NULL);
	}
	i++;
	new_str = (char *)malloc(sizeof(char) * (ft_strlen(left_str) - i + 1));
	if (!new_str)
	{
		free(left_str);
		return (NULL);
	}
	j = 0;
	while (left_str[i])
		new_str[j++] = left_str[i++];
	new_str[j] = '\0';
	free(left_str);
	return (new_str);
}

/*
** get_next_line - ファイルから1行ずつ読み込む
** @fd: 読み込むファイルディスクリプタ
**
** 戻り値: 読み込んだ1行の文字列（\nを含む）
*/
char	*get_next_line(int fd)
{
	static char	*left_str;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	left_str = get_line(fd, left_str);
	if (!left_str)
		return (NULL);
	line = extract_line(left_str);
	left_str = new_left_str(left_str);
	return (line);
}

// #include <string.h>
// int main(void){
//     int fd = open("filename.txt", O_RDONLY);
//     if (fd == -1) {
//         printf("%s","open_erro");
//     }
//     char *result;
//     result = "";
//     while (result)
//     {
//         result = get_next_line(fd);
//         printf("%s",result);
//         free(result);
//     }
//     if (close(fd) == -1) {
//         printf("%s","close_erro");
//     }
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhayato <hhayato@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:48:23 by hhayato           #+#    #+#             */
/*   Updated: 2025/01/07 14:16:32 by hhayato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

void	*ft_calloc(size_t n, size_t size)
{
	void	*result;
	char	*c_r;
	size_t	i;

	if (n == 0 || size == 0)
	{
		result = malloc(0);
		return (result);
	}
	if (((__SIZE_MAX__ / n) < size))
	{
		return (NULL);
	}
	result = malloc(n * size);
	if (!result)
		return (NULL);
	i = (size_t)0;
	c_r = result;
	while (i < size)
	{
		c_r[i++] = 0;
	}
	return (result);
}

char	*ft_strjoin(char *s1, char const *s2)
{
	char	*result;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	result = (char *)ft_calloc(sizeof(char), ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		result[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		result[i + j] = s2[j];
		j++;
	}
	result[i + j] = '\0';
	free(s1);
	return (result);
}

char	*open_codes(int fd, char *backup, char *buffer)
{
	int	bytes_read;
	int	i;

	bytes_read = 1;
	i = 0;
	while (1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (0);
		else if (bytes_read == 0)
			break ;
		if (backup == NULL)
			backup = ft_strdup("");
		buffer[bytes_read] = '\0';
		backup = ft_strjoin(backup, buffer);
		if (!backup)
			return (NULL);
		i = 0;
		while (buffer[i] != '\0' && buffer[i] != '\n')
			i++;
		if (buffer[i] == '\n')
			break ;
	}
	return (backup);
}

static char	*cat_open(char *result)
{
	int		count;
	char	*backup;

	count = 0;
	while (result[count] != '\n' && result[count] != '\0')
		count++;
	if (result[count] == '\0' || result[1] == '\0')
		return (0);
	backup = ft_substr(result, count + 1, ft_strlen(result) - count);
	if (*backup == '\0')
	{
		free(backup);
		backup = NULL;
	}
	result[count + 1] = 0;
	return (backup);
}

char	*get_next_line(int fd)
{
	static char	*backup;
	char		*result;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)ft_calloc(sizeof(char), (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	result = "";
	result = open_codes(fd, backup, buffer);
	free(buffer);
	if (!result)
	{
		free(backup);
		return (NULL);
	}
	backup = cat_open(result);
	return (result);
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

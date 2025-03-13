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

char	*gnl_strjoin(char *s1, char const *s2)
{
	char	*result;
	int		i;
	int		j;

	if (!s1)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	result = (char *)calloc(sizeof(char), ft_strlen(s1) + ft_strlen(s2) + 1);
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

char	*get_line(int fd, char *line)
{
	char	*buffer;
	ssize_t	read_bytes;

	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	read_bytes = 1;
	while (!ft_strchr(line, '\n') && read_bytes > 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[read_bytes] = '\0';
		line = gnl_strjoin(line, buffer);
	}
	free(buffer);
	return (line);
}

char	*next_line(char *line)
{
	int		count;
	char	*ans;

	count = 0;
	while (line[count] != '\n' && line[count] != '\0')
		count++;
	ans = ft_substr(line,0,count);
	ans[count + 1] = 0;
	return (ans);
}


char	*get_next_line(int fd)
{
	static char	*line;
	char		*result;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	result = "";
	result = get_line(fd,line);
	printf("::::%s",result);
	if(!line)
		return (NULL);
	result = next_line(line);
	printf("::::%s",result);
	//line = new_line(line);
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

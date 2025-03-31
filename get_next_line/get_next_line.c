/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhayato@student.42.fr <hhayato>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:48:23 by hhayato           #+#    #+#             */
/*   Updated: 2025/03/30 22:41:03 by hhayato@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "get_next_line.h"

char	*gnl_get_line(char *buffer)
{
	int		i;
	char	*str;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	str = gnl_substr(buffer, 0, i + gnl_endl(buffer));
	if (!str)
	{
		free(str);
		return (NULL);
	}
	return (str);
}

char	*gnl_new_str(char *buffer)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	str = malloc(sizeof(char) * (gnl_strlen(buffer) - i + 1));
	if (!str)
	{
		free(str);
		return (NULL);
	}
	i++;
	j = 0;
	while (buffer[i])
		str[j++] = buffer[i++];
	str[j] = '\0';
	free(buffer);
	return (str);
}

char	*gnl_read_str(int fd, char *buffer)
{
	char	*s;
	int		bytes;

	s = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!s)
		return (NULL);
	bytes = 1;
	while (!gnl_strchr(buffer, '\n') && bytes != 0)
	{
		bytes = read(fd, s, BUFFER_SIZE);
		if (bytes < 0)
		{
			free(s);
			return (NULL);
		}
		s[bytes] = '\0';
		buffer = gnl_strjoin(buffer, s);
	}
	free(s);
	return (buffer);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buffer = gnl_read_str(fd, buffer);
	if (!buffer)
		return (NULL);
	line = gnl_get_line(buffer);
	buffer = gnl_new_str(buffer);
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

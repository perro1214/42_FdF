/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhayato@student.42.fr <hhayato>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:54:36 by hhayato           #+#    #+#             */
/*   Updated: 2025/03/30 22:54:08 by hhayato@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 8192
# endif

# if BUFFER_SIZE < 0
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 0
# endif

size_t	gnl_strlen(const char *s);
char	*gnl_strchr(const char *str, int c);
char	*gnl_strjoin(char *buffer, char *s);
char	*gnl_substr(char const *s, unsigned int start, size_t len);
int		gnl_endl(char *str);
char	*gnl_get_line(char *buffer);
char	*gnl_new_str(char *buffer);
char	*gnl_read_str(int fd, char *buffer);
char	*get_next_line(int fd);

#endif
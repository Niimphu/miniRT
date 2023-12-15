/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 18:39:40 by yiwong            #+#    #+#             */
/*   Updated: 2023/02/08 01:27:57 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

char	*get_next_line(int fd);
char	*gnl_read(int fd, char *line);
char	*gnl_retline(char *line);
char	*gnl_save(char *buff);

int		gnl_strlen(char *s, char c);
int		gnl_findnl(char *s);
char	*gnl_calloc(int nmemb, int size);
char	*gnl_join(char *buff, char *read_line);

#endif
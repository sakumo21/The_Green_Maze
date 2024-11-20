/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziel-hac <ziel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 15:37:41 by ziel-hac          #+#    #+#             */
/*   Updated: 2024/11/20 20:47:26 by ziel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stddef.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/types.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

size_t	ft_strleng(const char *s);
char	*ft_strdupg(const char *s);
char	*ft_strjoing(char const *s1, char const *s2);
char	*ft_substrg(char const *s, unsigned int start, size_t len);
char	*ft_strchrg(const char *s, int c);
char	*get_next_line(int fd);
void	ft_bzerog(void *s, size_t n);

# ifndef MAX_FD
#  define MAX_FD 1
# endif

#endif

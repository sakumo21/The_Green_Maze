/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziel-hac <ziel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 15:34:18 by ziel-hac          #+#    #+#             */
/*   Updated: 2024/11/20 20:47:11 by ziel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strleng(const char *s)
{
	size_t	i;

	i = 0;
	while (*s != '\0')
	{
		i++;
		s++;
	}
	return (i);
}

char	*ft_strdupg(const char *str)
{
	size_t	i;
	size_t	len;
	char	*s;

	len = ft_strleng(str) + 1;
	s = (char *)malloc(sizeof(char) * len);
	if (s == NULL)
		return (NULL);
	i = -1;
	while (++i < len)
		s[i] = str[i];
	return (s);
}

char	*ft_strjoing(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;
	size_t	size;

	if (!s1 || !s2)
		return (NULL);
	size = ft_strleng(s1) + ft_strleng(s2) + 1;
	str = (char *)malloc(sizeof(char) * size);
	if (!str)
		return (NULL);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	j = -1;
	while (s2[++j])
		str[i + j] = s2[j];
	str[i + j] = '\0';
	return (str);
}

char	*ft_substrg(char const *s, unsigned int start, size_t len)
{
	char			*str;
	unsigned int	a;
	unsigned int	lens;
	unsigned int	i;

	i = 0;
	if (!s)
		return (NULL);
	lens = 0;
	a = 0;
	lens = ft_strleng(s);
	if (start < lens)
		a = lens - start;
	if (a > len)
		a = len;
	str = malloc((a + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (i < a && start < lens)
	{
		str[i++] = s[start++];
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strchrg(const char *s, int c)
{
	if (s == NULL)
		return (NULL);
	while (*s != '\0')
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	if (*s == '\0' && c == '\0')
		return ((char *)s);
	return (NULL);
}

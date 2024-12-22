/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziel-hac <ziel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 17:49:03 by ziel-hac          #+#    #+#             */
/*   Updated: 2024/12/22 17:49:04 by ziel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_m(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

static void	split_word(char const *s, char c, char **str, int count)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (*s && i < count)
	{
		while (*s == c)
			s++;
		if (!ft_strchr(s, c))
			k = ft_strlen(s);
		else
			k = ft_strchr(s, c) - s;
		str[i] = ft_substr(s, 0, k);
		if (!str[i])
		{
			free_m(str);
			return ;
		}
		s += k;
		i++;
	}
}

static int	word_count(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			i++;
		else
		{
			count++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		count;

	if (!s)
		return (0);
	count = word_count(s, c);
	str = (char **)malloc((count + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	if (count == 0)
	{
		free(str);
		return (NULL);
	}
	split_word(s, c, str, count);
	if (!str[count - 1])
	{
		free(str);
		return (NULL);
	}
	str[count] = NULL;
	return (str);
}

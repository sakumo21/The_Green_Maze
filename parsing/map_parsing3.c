/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziel-hac <ziel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 12:11:40 by mlamrani          #+#    #+#             */
/*   Updated: 2024/12/22 22:30:24 by ziel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	handle_empty_map(char *str)
{
	if (!str[0])
	{
		free(str);
		printf("Error: Empty map.\n");
		return (1);
	}
	return (0);
}

int	handle_empty_lines(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n' && str[i + 1] == '\n')
		{
			free(str);
			printf("Error: Empty line in map.\n");
			return (1);
		}
		i++;
	}
	return (0);
}

char	*read_map_lines(char *line, int fd)
{
	char	*str;
	char	*temp;

	str = ft_strdup("");
	if (!str)
		return (NULL);
	while (line)
	{
		temp = ft_strjoin(str, line);
		free(str);
		free(line);
		if (!temp)
			return (NULL);
		str = temp;
		line = get_next_line(fd);
	}
	return (str);
}

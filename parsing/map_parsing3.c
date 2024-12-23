/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 12:11:40 by mlamrani          #+#    #+#             */
/*   Updated: 2024/12/23 11:52:46 by mlamrani         ###   ########.fr       */
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

int	parsing_map(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '1' && map[i][j] != '0' && map[i][j] != ' '
				&& map[i][j] != 'N' && map[i][j] != 'S' && map[i][j] != 'W'
				&& map[i][j] != 'E' && map[i][j] != 'D')
				return (printf("Error: Invalid map character\n"), 1);
			j++;
		}
		i++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziel-hac <ziel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 12:11:40 by mlamrani          #+#    #+#             */
/*   Updated: 2024/12/24 18:32:25 by ziel-hac         ###   ########.fr       */
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


char *process_line(char *line, char *str, int fd, int i)
{
	if (i > 0 && line[i] == '\0')
	{
		int j = 0;
		line = get_next_line(fd);
		if(!line)
				return (str);
		while (line)
		{
			while (line[j])
			{
				if (line[j] != ' ' && line[j] != '\n' && line[j] != '\t')
				{
					return(printf("Error : Empty line in the map.\n"), NULL);
				}
				j++;
			}
			free(line);
			line = get_next_line(fd);
			if(!line)
			{
				return (str);
			}
		}
	}
	return (str);
}


char	*read_map_lines(char *line, int fd)
{
	char	*str;
	char	*temp;
	int		i;
	str = ft_strdup("");
	if (!str)
		return (NULL);
	while (line)
	{
		i = 0;
		while (line[i] && (line[i] == '\n' || line[i] == ' ' || line[i] == '\t'))
			i++;
		if (!process_line(line, str, fd, i))
			return (get_next_line(-1), free(str), NULL);
		temp = ft_strjoin(str, line);
		free(str);
		free(line);
		if (!temp)
			return (NULL);
		str = temp;
		get_next_line(-1);
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
				&& map[i][j] != 'E' &&  map[i][j] != 'D' && map[i][j] != '\t')
				return (printf("Error: Invalid map character\n"), 1);
			j++;
		}
		i++;
	}
	return (0);
}

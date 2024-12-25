/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 12:11:40 by mlamrani          #+#    #+#             */
/*   Updated: 2024/12/25 09:56:13 by mlamrani         ###   ########.fr       */
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


int process_line(char *line, int fd, int i)
{
	if (i > 0 && line[i] == '\0')
	{
		int j = 0;
		free(line);
		line = get_next_line(fd);
		if(!line)
			return (-1);
		while (line)
		{
			while (line[j])
			{
				if (line[j] != ' ' && line[j] != '\n' && line[j] != '\t')
					return(printf("Error : Empty line in the map.\n"), free(line), 1);
				j++;
			}
			free(line);
			line = get_next_line(fd);
			if(!line)
				return (-1);
		}
	}
	return (0);
}


char	*read_map_lines(char *line, int fd)
{
	char	*str;
	char	*temp;
	int		i;
	int 	proc;
	str = ft_strdup("");
	if (!str)
		return (NULL);
	while (line)
	{
		i = 0;
		while (line[i] && (line[i] == '\n' || line[i] == ' ' || line[i] == '\t'))
			i++;
		proc = process_line(line, fd, i);
		if (proc== 1)
			return (get_next_line(-1), free(str), NULL);
		else if (proc == -1)
			return (str);
		else
		{
			temp = ft_strjoin(str, line);
			free(str);
			free(line);
			if (!temp)
				return (NULL);
			str = temp;
			line = get_next_line(fd);
			get_next_line(-1);
		}
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
				&& map[i][j] != 'E' && map[i][j] != '\t')
				return (printf("Error: Invalid map character\n"), 1);
			j++;
		}
		i++;
	}
	return (0);
}

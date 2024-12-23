/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 12:11:40 by mlamrani          #+#    #+#             */
/*   Updated: 2024/12/23 23:42:42 by mlamrani         ###   ########.fr       */
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
		if (str[i] == ' ' && str[i + 1] == '\n')
		{
			free(str);
			printf("Error:=> Empty line in map.\n");
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
	int		i;
	str = ft_strdup("");
	if (!str)
		return (NULL);
	while (line)
	{
		//process line
		i = 0;
		while (line[i])
		{
			//check empyty line
			if (line[i] != '\n' && line[i] != ' ')
			{
				break;
		
			}
			i++;
		}
			// else if(!(line[i] == ' ' && line[i + 1] == '\n'))
			// 	break;
		if (i > 0 && line[i] == '\0')
		{
				int j = 0;
				line = get_next_line(fd); //get next line
				if(!line)
						return (str);
				while (line)
				{
					while (line[j])
					{
						if (line[j] != ' ' && line[j] != '\n')
						{
							printf("Error : Empty line in the map.\n");
							return (NULL);	
						}
						j++;
					}
					line = get_next_line(fd);
					if(!line)
						return (str);
				}
		}
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:28:51 by mlamrani          #+#    #+#             */
/*   Updated: 2024/12/23 11:52:35 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	mini_map(char *line, t_map *map, int fd)
{
	char	*str;

	str = read_map_lines(line, fd);
	close(fd);
	if (!str)
		return (printf("Error: Memory allocation failed.\n"), 1);
	if (handle_empty_map(str))
		return (1);
	if (handle_empty_lines(str))
		return (1);
	map->map = ft_split(str, '\n');
	free(str);
	if (!map->map)
		return (printf("Error: Memory allocation failed.\n"), 1);
	return (0);
}

int	check_pos(t_map *map, int x, int y, char *invalid_neighbors)
{
	map->exit = "10DNEWS";
	if (map->map[y][x] == 'D')
	{
		if (x == 0 || !ft_strchr(map->exit, map->map[y][x - 1]) ||
			!map->map[y][x + 1] || !ft_strchr(map->exit, map->map[y][x + 1]) ||
			y == 0 || x >= (int)ft_strlen(map->map[y - 1])
				|| !ft_strchr(map->exit, map->map[y - 1][x]) ||
			!map->map[y + 1] || x >= (int)ft_strlen(map->map[y + 1])
				|| !ft_strchr(map->exit, map->map[y + 1][x]))
			return (printf("Error: Invalid map\n"), 1);
	}
	else if (map->map[y][x] == 'N' || map->map[y][x] == 'S' ||
				map->map[y][x] == 'W' || map->map[y][x] == 'E')
	{
		if (x == 0 || !ft_strchr(invalid_neighbors, map->map[y][x - 1]) ||
			!map->map[y][x + 1] || !ft_strchr(invalid_neighbors, map->map[y][x
					+ 1]) ||
			y == 0 || x >= (int)ft_strlen(map->map[y - 1])
				|| !ft_strchr(invalid_neighbors, map->map[y - 1][x]) ||
			!map->map[y + 1] || x >= (int)ft_strlen(map->map[y + 1])
				|| !ft_strchr(invalid_neighbors, map->map[y + 1][x]))
			return (printf("Error: Invalid map\n"), 1);
	}
	return (0);
}

int	check_map_enclosure(t_map *map, int x, int y, char *valid_neighbors)
{
	while (map->map[y])
	{
		x = 0;
		while (map->map[y][x])
		{
			if (map->map[y][x] == '0')
			{
				if (x == 0 || !ft_strchr(valid_neighbors, map->map[y][x - 1]) ||
					!map->map[y][x + 1] || !ft_strchr(valid_neighbors,
							map->map[y][x + 1]) ||
					y == 0 || x >= (int)ft_strlen(map->map[y - 1])
						|| !ft_strchr(valid_neighbors, map->map[y - 1][x]) ||
					!map->map[y + 1] || x >= (int)ft_strlen(map->map[y + 1])
						|| !ft_strchr(valid_neighbors, map->map[y + 1][x]))
					return (printf("Error: Invalid map\n"), 1);
			}
			if (check_pos(map, x, y, "10D"))
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}

void	set_start_point(t_data *img, int i, int j)
{
	img->ray.posx = j + 0.5;
	img->ray.posy = i + 0.5;
	img->map->player_x = j;
	img->map->player_y = i;
	img->map->player = img->map->map[i][j];
	img->map->map[i][j] = '0';
}

int	find_starting_point(char **map, t_data *img, int i, int found)
{
	int	j;

	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W'
				|| map[i][j] == 'E')
			{
				if (found)
					return (printf("Error: Multiple player found\n"), 1);
				set_start_point(img, i, j);
				found = 1;
			}
			else if (map[i][j] != '1' && map[i][j] != '0' && map[i][j] != ' '
					&& map[i][j] != 'D')
				return (printf("Error: Invalid character\n"), 1);
			j++;
		}
		i++;
	}
	if (!found)
		return (printf("Error: No starting point found (N, S, W, or E).\n"), 1);
	return (0);
}

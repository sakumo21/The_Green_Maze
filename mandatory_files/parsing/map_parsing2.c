/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziel-hac <ziel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 16:40:53 by mlamrani          #+#    #+#             */
/*   Updated: 2024/12/24 17:23:53 by ziel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	my_map(t_map *map, t_data *img)
{
	int	max_y;

	max_y = 0;
	if (parsing_map(map->map))
		return (1);
	while (map->map[max_y] != NULL)
		max_y++;
	if (check_map_enclosure(map, 0, 0, "10NEWS"))
		return (1);
	if (find_starting_point(map->map, img, 0, 0))
		return (1);
	return (0);
}

int	check_set_color(int *flag, char *msg, char *new, t_data *img)
{
	if (*flag)
	{
		printf("Error : %s already defined.\n", msg);
		exit(1);
	}
	*flag = 1;
	if (new)
	{
		if (check_range(new, img, new + 2))
			exit(1);
	}
	return (0);
}

int	check_and_set(char **path, int *flag, char *msg, t_flag *flagg)
{
	char	*tmp;

	if (*flag)
	{
		printf("Error : %s already defined.\n", msg);
		exit(1);
	}
	*flag = 1;
	tmp = ft_strtrim(path[1], "\n");
	free(path[1]);
	path[1] = tmp;
	if (check_line(path, flagg))
		return (1);
	return (0);
}

void	set_set(char *line, char **p, t_data *img)
{
	char	*tmp;

	if (line[0] == 'F')
	{
		tmp = ft_strjoin_three(p[0], ",", p[1]);
		img->floor = ft_strjoin_three(tmp, ",", p[2]);
		free(tmp);
	}
	else if (line[0] == 'C')
	{
		tmp = ft_strjoin_three(p[0], ",", p[1]);
		img->ceiling = ft_strjoin_three(tmp, ",", p[2]);
		free(tmp);
	}
}

int	check_range(char *line, t_data *img, char *new)
{
	char	**p;
	char	*trimmed;
	char	*tmp;
	int i = 0;
	while (new[i])
	{
		if (new[i] == ',' && new[i + 1] == ',')
			return (printf("Error : Incorrect.\n"), 1);
		i++;
	}
	p = ft_split(new, ',');
	if (!p || !p[0] || !p[1] || !p[2] || (!p[2] && !p[2][0]) || (p[2]
			&& p[2][0] == '\n'))
	{
		free_range(p, 0);
		return (printf("Error : Expected 3 RGB values [..., ..., ...].\n"), 1);
	}
	tmp = p[2];
	p[2] = ft_strtrim(p[2], "\n");
	free(tmp);
	if (p[2][0] != '\0')
	{
		trimmed = ft_strtrim(p[2], "\n");
		if (!trimmed)
			return (free_range(p, 0), 1);
		free(p[2]);
		p[2] = trimmed;
	}
	if (validate_values(p) || check_extra_values(p) || check_value_range(p))
		return (1);
	return (set_set(line, p, img), free_range(p, 0), 0);
}

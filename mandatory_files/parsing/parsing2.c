/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 13:59:03 by mlamrani          #+#    #+#             */
/*   Updated: 2025/01/16 17:10:05 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	set_texture(t_texture_data *data)
{
	char	*trimmed;
	int		i;

	trimmed = NULL;
	if (data->path[1])
	{
		trimmed = ft_strtrim(data->path[1], "\n");
		if (data->img->textures[data->index].path)
			free(data->img->textures[data->index].path);
		data->img->textures[data->index].path = ft_strdup(trimmed);
		free(trimmed);
	}
	i = check_and_set(data->path, data->flag_check, data->texture_name,
			data->flag);
	if (i)
		data->flag->exit = 2;
	return (i);
}

int	handle_texture(t_texture_data *data, int index, char *name,
		int *flag_check)
{
	data->index = index;
	data->texture_name = name;
	data->flag_check = flag_check;
	return (set_texture(data));
}

int	texturing(char **path, char *new, t_flag *flag, t_data *img)
{
	t_texture_data	data;
	int				texture_result;
	int				color_result;

	data.path = path;
	data.flag = flag;
	data.img = img;
	texture_result = handle_texture_direction(path, &data, flag);
	if (texture_result != -1)
		return (texture_result);
	color_result = handle_floor_or_ceiling(path, new, flag, img);
	if (color_result != -1)
		return (color_result);
	if (ft_isalpha(path[0][0]))
	{
		printf("Error\n%s is not a valid identifier.\n", path[0]);
		flag->exit = 2;
		return (1);
	}
	flag->is_map_started = 1;
	return (1);
}

void	init_flag(t_flag *flag, t_map *map, t_data *img)
{
	flag->n_check = 0;
	flag->s_check = 0;
	flag->w_check = 0;
	flag->e_check = 0;
	flag->f_check = 0;
	flag->c_check = 0;
	flag->exit = 0;
	flag->is_map_started = 0;
	map->map = NULL;
	map->player = 0;
	map->player_x = 0;
	map->player_y = 0;
	img->floor = NULL;
	img->ceiling = NULL;
}

int	parse_input(int ac, char **av, int i)
{
	if (ac < 2)
		return (printf("Error\nWhere is the file?\n"), 1);
	if (ac > 2)
		return (printf("Error\nToo many files.\n"), 1);
	if (ft_strlen(av[1]) == 4 && !ft_strncmp(av[1] + ft_strlen(av[1]) - 4,
			".cub", 4))
		return (printf("Error\nadd a name to your .cub file.\n"), 1);
	while (av[1][i] != '.')
		i++;
	if (av[1][i] == '.' && (av[1][i + 1] != 'c' || av[1][i + 2] != 'u'
			|| av[1][i + 3] != 'b'))
		return (printf("Error\nPut the right extension (.cub) !\n"), 1);
	else if (av[1][i] == '.' && av[1][i + 1] == 'c' && av[1][i + 2] == 'u'
		&& av[1][i + 3] == 'b' && av[1][i + 4] != '\0')
		return (printf("Error\nPut the right extension (.cub) !\n"), 1);
	return (0);
}

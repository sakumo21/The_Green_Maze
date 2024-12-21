/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziel-hac <ziel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 13:59:03 by mlamrani          #+#    #+#             */
/*   Updated: 2024/12/21 15:48:51 by ziel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static int	set_texture(t_texture_data *data)
{
	if (data->path[1])
		data->img->textures[data->index].path
			= ft_strdup(ft_strtrim(data->path[1], "\n"));
	return (check_and_set(data->path, data->flag_check, data->texture_name,
			data->flag));
}

static int	handle_texture(t_texture_data *data, int index, char *name,
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

	data.path = path;
	data.flag = flag;
	data.img = img;
	if (!ft_strncmp(path[0], "N", ft_strlen("N")) || !ft_strncmp(path[0], "NO",
			ft_strlen("NO")))
		return (handle_texture(&data, 0, "North texture", &flag->N_check));
	if (!ft_strncmp(path[0], "S", ft_strlen("S")) || !ft_strncmp(path[0], "SO",
			ft_strlen("SO")))
		return (handle_texture(&data, 1, "South texture", &flag->S_check));
	if (!ft_strncmp(path[0], "W", ft_strlen("W")) || !ft_strncmp(path[0], "WE",
			ft_strlen("WE")))
		return (handle_texture(&data, 2, "West texture", &flag->W_check));
	if (!ft_strncmp(path[0], "E", ft_strlen("E")) || !ft_strncmp(path[0], "EA",
			ft_strlen("EA")))
		return (handle_texture(&data, 3, "East texture", &flag->E_check));
	if (!ft_strncmp(path[0], "F", 1))
		return (check_set_color(&flag->F_check, "Floor color", new, img));
	if (!ft_strncmp(path[0], "C", 1))
		return (check_set_color(&flag->C_check, "Ceiling color", new, img));
	if (ft_isalpha(path[0][0]))
		return (printf("Error: %s is not a valid identifier.\n", path[0]),
			flag->exit = 2, 1);
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
    map->map = NULL;
    map->player = 0;
    map->player_x = 0;
    map->player_y = 0;
    img->floor = NULL;
    img->ceiling = NULL;
}

int	parse_input(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac != 2)
		return (printf("Where is the file?\n"), 1);
	if (ft_strlen(av[1]) == 4 && !ft_strncmp(av[1] + ft_strlen(av[1]) - 4,
			".cub", 4))
		return (printf("Error : add a name to your .cub file.\n"), 1);
	while (av[1][i] != '.')
		i++;
	if (av[1][i] == '.' && (av[1][i + 1] != 'c' || av[1][i + 2] != 'u'
			|| av[1][i + 3] != 'b'))
		return (printf("Error : Put the right extension (.cub) !\n"), 1);
	else if (av[1][i] == '.' && av[1][i + 1] == 'c' && av[1][i + 2] == 'u'
			&& av[1][i + 3] == 'b' && av[1][i + 4] != '\0')
		return (printf("Error : Put the right extension (.cub) !\n"), 1);
	return (0);
}

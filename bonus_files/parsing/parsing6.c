/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing6.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:48:47 by mlamrani          #+#    #+#             */
/*   Updated: 2025/01/27 10:48:50 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	first_parse(int ac, char **av, int *fd, t_data *img)
{
	if (parse_input(ac, av, 0))
	{
		free(img->map);
		exit(1);
	}
	*fd = open(av[1], O_RDONLY);
	if (*fd < 0)
	{
		printf("Error\nFile not found.\n");
		free(img->map);
		exit(1);
	}
	return (0);
}

int	check_too_many_args(char **path, t_flag *flag, const char *texture_name)
{
	if (path[1] && path[2] && path[2][0] != '\n')
	{
		printf("Error\nToo many arguments for %s.\n", texture_name);
		flag->exit = 2;
		return (1);
	}
	return (0);
}

int	is_texture_match(char *input, char *short_id, char *long_id)
{
	return (!ft_strncmp(input, short_id, ft_strlen(short_id))
		|| !ft_strncmp(input, long_id, ft_strlen(long_id)));
}

int	handle_texture_direction(char **path, t_texture_data *data, t_flag *flag)
{
	if (is_texture_match(path[0], "N", "NO"))
	{
		if (check_too_many_args(path, flag, "North texture"))
			return (1);
		return (handle_texture(data, 0, "North texture", &flag->n_check));
	}
	if (is_texture_match(path[0], "S", "SO"))
	{
		if (check_too_many_args(path, flag, "South texture"))
			return (1);
		return (handle_texture(data, 1, "South texture", &flag->s_check));
	}
	if (is_texture_match(path[0], "W", "WE"))
	{
		if (check_too_many_args(path, flag, "West texture"))
			return (1);
		return (handle_texture(data, 2, "West texture", &flag->w_check));
	}
	if (is_texture_match(path[0], "E", "EA"))
	{
		if (check_too_many_args(path, flag, "East texture"))
			return (1);
		return (handle_texture(data, 3, "East texture", &flag->e_check));
	}
	return (-1);
}

int	handle_floor_or_ceiling(char **path, char *new, t_flag *flag, t_data *img)
{
	int	result;

	if (!ft_strncmp(path[0], "F", 1))
	{
		result = check_set_color(&flag->f_check, "Floor color", new, img);
		if (result == 2)
			flag->exit = 2;
		if (result)
			return (1);
		else
			return (0);
	}
	if (!ft_strncmp(path[0], "C", 1))
	{
		result = check_set_color(&flag->c_check, "Ceiling color", new, img);
		if (result == 2)
			flag->exit = 2;
		if (result)
			return (1);
		else
			return (0);
	}
	return (-1);
}

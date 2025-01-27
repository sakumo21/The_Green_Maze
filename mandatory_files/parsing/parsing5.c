/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:47:22 by mlamrani          #+#    #+#             */
/*   Updated: 2025/01/27 10:47:25 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	free_path(char **path, char *new)
{
	int	i;

	if (path)
	{
		i = 0;
		while (path[i])
		{
			free(path[i]);
			i++;
		}
		free(path);
	}
	if (new)
	{
		free(new);
		new = NULL;
	}
}

int	check_texture(t_flag *flag)
{
	int	error;

	error = 0;
	print_error("North texture", &flag->n_check, &error);
	print_error("South texture", &flag->s_check, &error);
	print_error("West texture", &flag->w_check, &error);
	print_error("East texture", &flag->e_check, &error);
	print_error("Floor color", &flag->f_check, &error);
	print_error("Ceiling color", &flag->c_check, &error);
	if (error)
		return (1);
	return (0);
}

int	final_checks(t_flag *flag, char *line, t_data *img, int fd)
{
	if (flag->exit == 2 || check_texture(flag))
		return (free(line), free_textures_path(img), 1);
	if (mini_map(line, img->map, fd) || my_map(img->map, img))
		return (free_textures_path(img), 1);
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

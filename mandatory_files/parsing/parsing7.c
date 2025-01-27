/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing7.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:47:05 by mlamrani          #+#    #+#             */
/*   Updated: 2025/01/27 10:47:07 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

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

int	my_isspace(char c)
{
	return (c == ' ' || c == '\n' || c == '\t');
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 17:41:15 by mlamrani          #+#    #+#             */
/*   Updated: 2024/12/21 17:46:06 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	free_path(char **path, char *new)
{
	int	i;

	i = 0;
	free(new);
	while (path[i])
	{
		free(path[i]);
		i++;
	}
	free(path);
}

int	check_texture(t_flag *flag)
{
	int	error;

	error = 0;
	print_error("North texture", &flag->N_check, &error);
	print_error("South texture", &flag->S_check, &error);
	print_error("West texture", &flag->W_check, &error);
	print_error("East texture", &flag->E_check, &error);
	print_error("Floor color", &flag->F_check, &error);
	print_error("Ceiling color", &flag->C_check, &error);
	if (error)
		return (1);
	return (0);
}

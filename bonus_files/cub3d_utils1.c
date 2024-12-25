/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziel-hac <ziel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 18:02:00 by ziel-hac          #+#    #+#             */
/*   Updated: 2024/12/25 14:36:51 by ziel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_d(char **args)
{
	int	i;

	i = 0;
	if (!args || !*args)
		return ;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void	free_end(t_data *img)
{
	if (img->map->map)
		free_d(img->map->map);
	free(img->floor);
	free(img->ceiling);
	free(img->map);
}

void	free_textures_path(t_data *img)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (img->textures[i].path)
			free(img->textures[i].path);
		i++;
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziel-hac <ziel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 17:30:10 by ziel-hac          #+#    #+#             */
/*   Updated: 2024/12/20 17:33:33 by ziel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	move_down(t_data *img)
{
	int	newX;
	int	newY;
	
	newX = (int)(img->ray.posx - img->ray.dirX * MOVESPEED);
	newY = (int)(img->ray.posy - img->ray.dirY * MOVESPEED);
	if (img->map->map[(int)img->ray.posy][newX] == '0' || img->map->map[(int)img->ray.posy][newX] == 'D')
		img->ray.posx -= img->ray.dirX * MOVESPEED;
	if (img->map->map[newY][(int)img->ray.posx] == '0' || img->map->map[newY][(int)img->ray.posx] == 'D')
		img->ray.posy -= img->ray.dirY * MOVESPEED;
}

void	move_up(t_data *img)
{
	int	newX;
	int	newY;
	
	newX = (int)(img->ray.posx + img->ray.dirX * MOVESPEED);
	newY = (int)(img->ray.posy + img->ray.dirY * MOVESPEED);
	if (img->map->map[(int)img->ray.posy][newX] == '0' || img->map->map[(int)img->ray.posy][newX] == 'D')
		img->ray.posx += img->ray.dirX * MOVESPEED;
	if (img->map->map[newY][(int)img->ray.posx] == '0' || img->map->map[newY][(int)img->ray.posx] == 'D')
		img->ray.posy += img->ray.dirY * MOVESPEED;
}

void 	move_left(t_data *img)
{
	int	newX;
	int	newY;

	newX = (int)(img->ray.posx - img->ray.planeX * MOVESPEED);
	newY = (int)(img->ray.posy - img->ray.planeY * MOVESPEED);
	if (img->map->map[(int)img->ray.posy][newX] == '0' || img->map->map[(int)img->ray.posy][newX] == 'D')
		img->ray.posx -= img->ray.planeX * MOVESPEED;
	if (img->map->map[newY][(int)img->ray.posx] == '0' || img->map->map[newY][(int)img->ray.posx] == 'D')
		img->ray.posy -= img->ray.planeY * MOVESPEED;
}

void	move_right(t_data *img)
{
	int	newX;
	int	newY;

	newX = (int)(img->ray.posx + img->ray.planeX * MOVESPEED);
	newY = (int)(img->ray.posy + img->ray.planeY * MOVESPEED);
	if (img->map->map[(int)img->ray.posy][newX] == '0' || img->map->map[(int)img->ray.posy][newX] == 'D')
		img->ray.posx += img->ray.planeX * MOVESPEED;
	if (img->map->map[newY][(int)img->ray.posx] == '0' || img->map->map[newY][(int)img->ray.posx] == 'D')
		img->ray.posy += img->ray.planeY * MOVESPEED;	
}
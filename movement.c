/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziel-hac <ziel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 17:30:10 by ziel-hac          #+#    #+#             */
/*   Updated: 2024/12/22 14:22:01 by ziel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	move_down(t_data *img)
{
	int	newx;
	int	newy;

	newx = (int)(img->ray.posx - img->ray.dirx * MOVESPEED);
	newy = (int)(img->ray.posy - img->ray.diry * MOVESPEED);
	if (img->map->map[(int)img->ray.posy][newx] == '0'
		|| img->map->map[(int)img->ray.posy][newx] == 'D')
		img->ray.posx -= img->ray.dirx * MOVESPEED;
	if (img->map->map[newy][(int)img->ray.posx] == '0'
		|| img->map->map[newy][(int)img->ray.posx] == 'D')
		img->ray.posy -= img->ray.diry * MOVESPEED;
}

void	move_up(t_data *img)
{
	int	newx;
	int	newy;

	newx = (int)(img->ray.posx + img->ray.dirx * MOVESPEED);
	newy = (int)(img->ray.posy + img->ray.diry * MOVESPEED);
	if (img->map->map[(int)img->ray.posy][newx] == '0'
		|| img->map->map[(int)img->ray.posy][newx] == 'D')
		img->ray.posx += img->ray.dirx * MOVESPEED;
	if (img->map->map[newy][(int)img->ray.posx] == '0'
		|| img->map->map[newy][(int)img->ray.posx] == 'D')
		img->ray.posy += img->ray.diry * MOVESPEED;
}

void	move_left(t_data *img)
{
	int	newx;
	int	newy;

	newx = (int)(img->ray.posx - img->ray.planex * MOVESPEED);
	newy = (int)(img->ray.posy - img->ray.planey * MOVESPEED);
	if (img->map->map[(int)img->ray.posy][newx] == '0'
		|| img->map->map[(int)img->ray.posy][newx] == 'D')
		img->ray.posx -= img->ray.planex * MOVESPEED;
	if (img->map->map[newy][(int)img->ray.posx] == '0'
		|| img->map->map[newy][(int)img->ray.posx] == 'D')
		img->ray.posy -= img->ray.planey * MOVESPEED;
}

void	move_right(t_data *img)
{
	int	newx;
	int	newy;

	newx = (int)(img->ray.posx + img->ray.planex * MOVESPEED);
	newy = (int)(img->ray.posy + img->ray.planey * MOVESPEED);
	if (img->map->map[(int)img->ray.posy][newx] == '0'
		|| img->map->map[(int)img->ray.posy][newx] == 'D')
		img->ray.posx += img->ray.planex * MOVESPEED;
	if (img->map->map[newy][(int)img->ray.posx] == '0'
		|| img->map->map[newy][(int)img->ray.posx] == 'D')
		img->ray.posy += img->ray.planey * MOVESPEED;
}

int	handle_movement(t_data *img)
{
	if (img->keys.w)
		move_up(img);
	if (img->keys.s)
		move_down(img);
	if (img->keys.a)
		move_left(img);
	if (img->keys.d)
		move_right(img);
	if (img->keys.space)
	{
		if (img->weapon == 0)
			punch_frames(img);
		else if (img->weapon == 1)
			pistol_frames(img);
	}
	if (img->keys.left)
		rotate_view(img, -ROTSPEED);
	if (img->keys.right)
		rotate_view(img, ROTSPEED);
	if (img->weapon == 0)
		rendering_image(img, 0, "./puunch.xpm");
	else
		rendering_image(img, 0, "./pistool.xpm");
	return (0);
}

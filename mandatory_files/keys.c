/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:03:36 by marvin            #+#    #+#             */
/*   Updated: 2024/11/04 17:03:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	rotate_view(t_data *img, double rotSpeed)
{
	double	olddirx;
	double	oldplanex;

	olddirx = img->ray.dirx;
	img->ray.dirx = img->ray.dirx * cos(rotSpeed)
		- img->ray.diry * sin(rotSpeed);
	img->ray.diry = olddirx * sin(rotSpeed)
		+ img->ray.diry * cos(rotSpeed);
	oldplanex = img->ray.planex;
	img->ray.planex = img->ray.planex * cos(rotSpeed)
		- img->ray.planey * sin(rotSpeed);
	img->ray.planey = oldplanex * sin(rotSpeed)
		+ img->ray.planey * cos(rotSpeed);
}

static int	key_press_handler(int keysym, t_data *img)
{
	if (keysym == 65307)
		free_img(img);
	else if (keysym == 119)
		img->keys.w = 1;
	else if (keysym == 115)
		img->keys.s = 1;
	else if (keysym == 97)
		img->keys.a = 1;
	else if (keysym == 100)
		img->keys.d = 1;
	else if (keysym == 65361)
		img->keys.left = 1;
	else if (keysym == 65363)
		img->keys.right = 1;
	return (0);
}

static int	key_release_handler(int keysym, t_data *img)
{
	if (keysym == 119)
		img->keys.w = 0;
	else if (keysym == 115)
		img->keys.s = 0;
	else if (keysym == 97)
		img->keys.a = 0;
	else if (keysym == 100)
		img->keys.d = 0;
	else if (keysym == 65361)
		img->keys.left = 0;
	else if (keysym == 65363)
		img->keys.right = 0;
	return (0);
}

void	event_keys(t_data *img)
{
	mlx_loop_hook(img->mlx, handle_movement, img);
	mlx_hook(img->win, KeyPress, KeyPressMask, key_press_handler, img);
	mlx_hook(img->win, KeyRelease, KeyReleaseMask, key_release_handler, img);
	mlx_hook(img->win, DestroyNotify, StructureNotifyMask, free_img, img);
}

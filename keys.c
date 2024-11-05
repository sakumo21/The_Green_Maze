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

#include "cub3d.h"

static int	free_img(t_data *img)
{
	mlx_destroy_image(img->mlx, img->img);
	mlx_destroy_window(img->mlx, img->win);
	mlx_destroy_display(img->mlx);
	free(img->mlx);
	exit(0);
}

static int	key_handler(int keysym, t_data *img)
{
	double moveSpeed = 0.1 * 5.0; //the constant value is in squares/second
    double rotSpeed = 0.1 * 3.0;
	printf("%d:%c\n", keysym, keysym);
	if (keysym == 65307)
	{
		free_img(img);
		exit(0);
	}
	if (keysym == 122) //z
		img->ray.posx -= img->ray.dirX;
	if (keysym == 115) // s
		img->ray.posx += img->ray.dirX;
	if (keysym == 113) // q
		img->ray.posy -= img->ray.dirY;
	if (keysym == 100) // d
		img->ray.posy += img->ray.dirY;
	if (keysym == 65363) // ->
	{
      double oldDirX = img->ray.dirX;
      img->ray.dirX = img->ray.dirX * cos(-rotSpeed) - img->ray.dirY * sin(-rotSpeed);
      img->ray.dirY = oldDirX * sin(-rotSpeed) + img->ray.dirY * cos(-rotSpeed);
      double oldPlaneX = img->ray.planeX;
      img->ray.planeX = img->ray.planeX * cos(-rotSpeed) - img->ray.planeY * sin(-rotSpeed);
      img->ray.planeY = oldPlaneX * sin(-rotSpeed) + img->ray.planeY * cos(-rotSpeed);
	}
	if (keysym == 65361) // <-
	{
      double oldDirX = img->ray.dirX;
      img->ray.dirX = img->ray.dirX * cos(rotSpeed) - img->ray.dirY * sin(rotSpeed);
      img->ray.dirY = oldDirX * sin(rotSpeed) + img->ray.dirY * cos(rotSpeed);
      double oldPlaneX = img->ray.planeX;
      img->ray.planeX = img->ray.planeX * cos(rotSpeed) - img->ray.planeY * sin(rotSpeed);
      img->ray.planeY = oldPlaneX * sin(rotSpeed) + img->ray.planeY * cos(rotSpeed);
	}
	rendering_image(img, 0, 0X0000FF);
	return (0);
}

void	event_keys(t_data *img)
{
	mlx_hook(img->win, KeyRelease, KeyReleaseMask, key_handler, img);
	mlx_hook(img->win, DestroyNotify, StructureNotifyMask, free_img, img);
}

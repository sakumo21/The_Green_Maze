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
	int	newX;
	int	newY;
	double moveSpeed = 0.03 * 4.0;
    double rotSpeed = 0.02;
	if (keysym == 65307)
	{
		free_img(img);
		exit(0);
	}
	else if  (keysym == 119)//w
	{
		newX = (int)(img->ray.posx + img->ray.dirX * moveSpeed);
		newY = (int)(img->ray.posy + img->ray.dirY * moveSpeed);
      if(img->map->map[(int)img->ray.posy][newX] == '0' || img->map->map[(int)img->ray.posy][newX] == 'D') 
	  	img->ray.posx += img->ray.dirX * moveSpeed;
      if(img->map->map[newY][(int)img->ray.posx] == '0' || img->map->map[newY][(int)img->ray.posx] == 'D') 
	  	img->ray.posy += img->ray.dirY * moveSpeed;
	}
	else if (keysym == 115) // s
	{
		newX = (int)(img->ray.posx - img->ray.dirX * moveSpeed);
		newY = (int)(img->ray.posy - img->ray.dirY * moveSpeed);
    	if(img->map->map[(int)img->ray.posy][newX] == '0' || img->map->map[(int)img->ray.posy][newX] == 'D') img->ray.posx -= img->ray.dirX * moveSpeed;
    	if(img->map->map[newY][(int)img->ray.posx] == '0' || img->map->map[newY][(int)img->ray.posx] == 'D') img->ray.posy -= img->ray.dirY * moveSpeed;
	}
	else if (keysym == 97) // a
	{
		newX = (int)(img->ray.posx - img->ray.planeX * moveSpeed);
		newY = (int)(img->ray.posy - img->ray.planeY * moveSpeed);
    	if(img->map->map[(int)img->ray.posy][newX] == '0' || img->map->map[(int)img->ray.posy][newX] == 'D') img->ray.posx -= img->ray.planeX * moveSpeed;
    	if(img->map->map[newY][(int)img->ray.posx] == '0' || img->map->map[newY][(int)img->ray.posx] == 'D') img->ray.posy -= img->ray.planeY * moveSpeed;
	}
	else if (keysym == 100) // d
	{
		newX = (int)(img->ray.posx + img->ray.planeX * moveSpeed);
		newY = (int)(img->ray.posy + img->ray.planeY * moveSpeed);
    	if(img->map->map[(int)img->ray.posy][newX] == '0' || img->map->map[(int)img->ray.posy][newX] == 'D') img->ray.posx += img->ray.planeX * moveSpeed;
    	if(img->map->map[newY][(int)img->ray.posx] == '0' || img->map->map[newY][(int)img->ray.posx] == 'D') img->ray.posy += img->ray.planeY * moveSpeed;
	}
	else if (keysym == 65361) // ->
	{
      double oldDirX = img->ray.dirX;
      img->ray.dirX = img->ray.dirX * cos(-rotSpeed) - img->ray.dirY * sin(-rotSpeed);
      img->ray.dirY = oldDirX * sin(-rotSpeed) + img->ray.dirY * cos(-rotSpeed);
      double oldPlaneX = img->ray.planeX;
      img->ray.planeX = img->ray.planeX * cos(-rotSpeed) - img->ray.planeY * sin(-rotSpeed);
      img->ray.planeY = oldPlaneX * sin(-rotSpeed) + img->ray.planeY * cos(-rotSpeed);
	}
	else if (keysym == 65363) // <-
	{
      double oldDirX = img->ray.dirX;
      img->ray.dirX = img->ray.dirX * cos(rotSpeed) - img->ray.dirY * sin(rotSpeed);
      img->ray.dirY = oldDirX * sin(rotSpeed) + img->ray.dirY * cos(rotSpeed);
      double oldPlaneX = img->ray.planeX;
      img->ray.planeX = img->ray.planeX * cos(rotSpeed) - img->ray.planeY * sin(rotSpeed);
      img->ray.planeY = oldPlaneX * sin(rotSpeed) + img->ray.planeY * cos(rotSpeed);
	}
	rendering_image(img, 0);
	return (0);
}

void	event_keys(t_data *img)
{
	mlx_hook(img->win, KeyPress, KeyPressMask, key_handler, img);
	mlx_hook(img->win, KeyRelease, KeyReleaseMask, key_handler, img);
	mlx_hook(img->win, DestroyNotify, StructureNotifyMask, free_img, img);
}

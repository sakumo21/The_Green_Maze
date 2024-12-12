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

static void	rotate_view(t_data *img, double rotSpeed)
{
	double oldDirX = img->ray.dirX;
	img->ray.dirX = img->ray.dirX * cos(rotSpeed) - img->ray.dirY * sin(rotSpeed);
	img->ray.dirY = oldDirX * sin(rotSpeed) + img->ray.dirY * cos(rotSpeed);

	double oldPlaneX = img->ray.planeX;
	img->ray.planeX = img->ray.planeX * cos(rotSpeed) - img->ray.planeY * sin(rotSpeed);
	img->ray.planeY = oldPlaneX * sin(rotSpeed) + img->ray.planeY * cos(rotSpeed);
}


int	handle_movement(t_data *img)
{
	double moveSpeed = 0.12;  // Adjust speed as needed
	double rotSpeed = 0.06;
	int newX, newY;

	// Forward (W)
	if (img->keys.w)
	{
		newX = (int)(img->ray.posx + img->ray.dirX * moveSpeed);
		newY = (int)(img->ray.posy + img->ray.dirY * moveSpeed);
		if (img->map->map[(int)img->ray.posy][newX] == '0' || img->map->map[(int)img->ray.posy][newX] == 'D')
			img->ray.posx += img->ray.dirX * moveSpeed;
		if (img->map->map[newY][(int)img->ray.posx] == '0' || img->map->map[newY][(int)img->ray.posx] == 'D')
			img->ray.posy += img->ray.dirY * moveSpeed;
	}

	// Backward (S)
	if (img->keys.s)
	{
		newX = (int)(img->ray.posx - img->ray.dirX * moveSpeed);
		newY = (int)(img->ray.posy - img->ray.dirY * moveSpeed);
		if (img->map->map[(int)img->ray.posy][newX] == '0' || img->map->map[(int)img->ray.posy][newX] == 'D')
			img->ray.posx -= img->ray.dirX * moveSpeed;
		if (img->map->map[newY][(int)img->ray.posx] == '0' || img->map->map[newY][(int)img->ray.posx] == 'D')
			img->ray.posy -= img->ray.dirY * moveSpeed;
	}

	// Left (A)
	if (img->keys.a)
	{
		newX = (int)(img->ray.posx - img->ray.planeX * moveSpeed);
		newY = (int)(img->ray.posy - img->ray.planeY * moveSpeed);
		if (img->map->map[(int)img->ray.posy][newX] == '0' || img->map->map[(int)img->ray.posy][newX] == 'D')
			img->ray.posx -= img->ray.planeX * moveSpeed;
		if (img->map->map[newY][(int)img->ray.posx] == '0' || img->map->map[newY][(int)img->ray.posx] == 'D')
			img->ray.posy -= img->ray.planeY * moveSpeed;
	}

	// Right (D)
	if (img->keys.d)
	{
		newX = (int)(img->ray.posx + img->ray.planeX * moveSpeed);
		newY = (int)(img->ray.posy + img->ray.planeY * moveSpeed);
		if (img->map->map[(int)img->ray.posy][newX] == '0' || img->map->map[(int)img->ray.posy][newX] == 'D')
			img->ray.posx += img->ray.planeX * moveSpeed;
		if (img->map->map[newY][(int)img->ray.posx] == '0' || img->map->map[newY][(int)img->ray.posx] == 'D')
			img->ray.posy += img->ray.planeY * moveSpeed;
	}

	// Rotate Left (←)
	if (img->keys.left)
		rotate_view(img, -rotSpeed);

	// Rotate Right (→)
	if (img->keys.right)
		rotate_view(img, rotSpeed);
	rendering_image(img, 0);
	return(0);
}



static int key_press_handler(int keysym, t_data *img)
{
    if (keysym == 65307) // Escape key
    {
        free_img(img);
        exit(0);
    }
    else if (keysym == 119) // W
        img->keys.w = 1;
    else if (keysym == 115) // S
        img->keys.s = 1;
    else if (keysym == 97)  // A
        img->keys.a = 1;
    else if (keysym == 100) // D
        img->keys.d = 1;
    else if (keysym == 65361) // Left arrow
        img->keys.left = 1;
    else if (keysym == 65363) // Right arrow
        img->keys.right = 1;
    return (0);
}

static int key_release_handler(int keysym, t_data *img)
{
    if (keysym == 119) // W
        img->keys.w = 0;
    else if (keysym == 115) // S
        img->keys.s = 0;
    else if (keysym == 97)  // A
        img->keys.a = 0;
    else if (keysym == 100) // D
        img->keys.d = 0;
    else if (keysym == 65361) // Left arrow
        img->keys.left = 0;
    else if (keysym == 65363) // Right arrow
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

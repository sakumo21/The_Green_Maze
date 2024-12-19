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
	free_textures(img);
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
	double rotSpeed = 0.05;
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
	if (img->keys.space)
	{
		if (img->weapon == 0)
		{
			rendering_image(img, 0, "./puunch3.xpm");
			usleep(10000);
			rendering_image(img, 0, "./puunch3.xpm");
			usleep(40000);
			rendering_image(img, 0, "./puunch2.xpm");
			usleep(40000);
			rendering_image(img, 0, "./puunch.xpm");
		}
		else if (img->weapon == 1)
		{
		
			rendering_image(img, 0, "./pistool2.xpm");
			usleep(40000);
			rendering_image(img, 0, "./pistool3.xpm");
			usleep(40000);
			rendering_image(img, 0, "./pistool4.xpm");
			usleep(40000);
			rendering_image(img, 0, "./pistool5.xpm");
			usleep(40000);
			rendering_image(img, 0, "./pistool2.xpm");
			usleep(40000);
			rendering_image(img, 0, "./pistool.xpm");
			}
	}
	// Rotate Left (←)
	if (img->keys.left)
		rotate_view(img, -rotSpeed);
	// Rotate Right (→)
	if (img->keys.right)
		rotate_view(img, rotSpeed);
	if (img->weapon == 0)
		rendering_image(img, 0, "./puunch.xpm");
	else	
		rendering_image(img, 0, "./pistool.xpm");
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
	else if (keysym == 32) // space
		img->keys.space = 1;
	else if (keysym == 49) // 1
		img->weapon = 0;
	else if (keysym == 50) // 2
		img->weapon = 1;
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
	else if (keysym == 32) // space
		img->keys.space = 0;
	return (0);
}

int	mouse_handler(int x, int y, t_data *img)
{
	// (void)img;
	// printf(" x: %d, y: %d\n", x, y);
	// (void)mouse;
	(void)y;
	if (x > img->keys.old_x)
		rotate_view(img, 0.05);
	else if (x < img->keys.old_x)
		rotate_view(img, -0.05);
	img->keys.old_x = x;
	return (0);
}

void	event_keys(t_data *img)
{
	mlx_loop_hook(img->mlx, handle_movement, img);
	mlx_hook(img->win, KeyPress, KeyPressMask, key_press_handler, img);
	mlx_hook(img->win, KeyRelease, KeyReleaseMask, key_release_handler, img);
	mlx_hook(img->win, DestroyNotify, StructureNotifyMask, free_img, img);
	mlx_hook(img->win, MotionNotify, PointerMotionMask, mouse_handler, img);
}

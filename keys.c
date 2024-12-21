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
	double	olddirx;
	double	oldplanex;

	olddirx = img->ray.dirX;
	img->ray.dirX = img->ray.dirX * cos(rotSpeed)
		- img->ray.dirY * sin(rotSpeed);
	img->ray.dirY = olddirx * sin(rotSpeed)
		+ img->ray.dirY * cos(rotSpeed);
	oldplanex = img->ray.planeX;
	img->ray.planeX = img->ray.planeX * cos(rotSpeed)
		- img->ray.planeY * sin(rotSpeed);
	img->ray.planeY = oldplanex * sin(rotSpeed)
		+ img->ray.planeY * cos(rotSpeed);
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

static int	key_press_handler(int keysym, t_data *img)
{
	if (keysym == 65307)
	{
		free_img(img);
		exit(0);
	}
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
	else if (keysym == 32)
		img->keys.space = 1;
	else if (keysym == 49)
		img->weapon = 0;
	else if (keysym == 50)
		img->weapon = 1;
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
	else if (keysym == 32)
		img->keys.space = 0;
	return (0);
}

int	mouse_handler(int x, int y, t_data *img)
{
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziel-hac <ziel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 15:39:42 by ziel-hac          #+#    #+#             */
/*   Updated: 2024/12/24 17:58:37 by ziel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_textures(t_data *img)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (img->textures[i].img)
			mlx_destroy_image(img->mlx, img->textures[i].img);
		i++;
	}
}

void	free_resources(t_data *img)
{
	if (img->img)
		mlx_destroy_image(img->mlx, img->img);
	if (img->win)
		mlx_destroy_window(img->mlx, img->win);
	if (img->mlx)
		mlx_destroy_display(img->mlx);
	free(img->mlx);
	free(img->map);
	exit (0);
}

void	initialize_values(t_data *img, double a[4])
{
	img->ray.dirx = a[0];
	img->ray.diry = a[1];
	img->ray.planex = a[2];
	img->ray.planey = a[3];
}

void	init_cube(t_data *img)
{
	img->mlx = NULL;
	img->win = NULL;
	img->img = NULL;
	img->addr = NULL;
	img->mlx = mlx_init();
	if (!img->mlx)
		exit (0);
	img->win = mlx_new_window(img->mlx, WIDTH, HEIGHT, "cub3d");
	if (!img->win)
		free_resources(img);
	img->img = mlx_new_image(img->mlx, WIDTH, HEIGHT);
	if (!img->img)
		free_resources(img);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	if (!img->addr)
		free_resources(img);
	img->map->minimap_height = HEIGHT / 9;
	img->map->minimap_width = WIDTH / 9;
	img->map->tile_size = img->map->minimap_width / img->map->width;
	load_textures(img, 0);
}

int	free_img(t_data *img)
{
	int	i;
	
	i = 0;
	free_textures_path(img);
	free_end(img);
	while(i < 4)
	{
		if (img->textures[i].img)
			mlx_destroy_image(img->mlx, img->textures[i].img);
		i++;
	}
	mlx_destroy_image(img->mlx, img->sprite.img);
	mlx_destroy_image(img->mlx, img->img);
	mlx_destroy_window(img->mlx, img->win);
	mlx_destroy_display(img->mlx);
	free(img->mlx);
	exit(0);
}

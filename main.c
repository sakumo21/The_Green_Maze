/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziel-hac <ziel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:22:47 by mlamrani          #+#    #+#             */
/*   Updated: 2024/12/20 17:43:35 by ziel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	initialize_values(t_data *img, double a[4])
{
	img->ray.dirX = a[0];
	img->ray.dirY = a[1];
	img->ray.planeX = a[2];
	img->ray.planeY = a[3];
}

void	initialize_data(t_data *img)
{
	if (img->map->player == 'N')
		initialize_values(img, (double [4]){0, -1, 0.66, 0});
	else if (img->map->player == 'S')
		initialize_values(img, (double [4]){0, 1, -0.66, 0});
	else if (img->map->player == 'E')
		initialize_values(img, (double [4]){1, 0, 0, 0.66});
	else if (img->map->player == 'W')
		initialize_values(img, (double [4]){-1, 0, 0, -0.66});
	img->ray.color = 0X0000FF;
	img->weapon = 0;
	img->keys.space = 0;
	img->keys.w = 0;
	img->keys.s = 0;
	img->keys.a = 0;
	img->keys.d = 0;
	img->keys.old_x = 0;
	img->keys.left = 0;
	img->keys.right = 0;
	img->sprite.img = NULL;
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
	img->map->minimap_height = HEIGHT / 8;
	img->map->minimap_width = WIDTH / 8;
	img->map->tile_size = img->map->minimap_width / img->map->width;
	load_textures(img);
}

void	put_to_image(t_data *img, char *str)
{
	int	img_width;
	int	img_height;

	mlx_destroy_image(img->mlx, img->sprite.img);
	img->sprite.img = mlx_xpm_file_to_image(img->mlx, str,
			&img_width, &img_height);
	img->sprite.addr = mlx_get_data_addr(img->sprite.img,
			&img->sprite.bits_per_pixel, &img->sprite.line_length,
			&img->sprite.endian);
	my_mlx_pixel_put_sprite(img, img_height, img_width);
	mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);
}

void	rendering_wepon(t_data *img, char *str)
{
	int	img_width;
	int	img_height;

	if (img->sprite.img != NULL)
		mlx_destroy_image(img->mlx, img->sprite.img);
	img->sprite.img = mlx_xpm_file_to_image(img->mlx, str,
			&img_width, &img_height);
	img->sprite.addr = mlx_get_data_addr(img->sprite.img,
			&img->sprite.bits_per_pixel, &img->sprite.line_length,
			&img->sprite.endian);
	my_mlx_pixel_put_sprite(img, img_height, img_width);
}

void	rendering_image(t_data *img, int i, char *str)
{
	mlx_destroy_image(img->mlx, img->img);
	img->img = mlx_new_image(img->mlx, WIDTH, HEIGHT);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	while (WIDTH > i)
	{
		calculate_ray(img, i);
		img->ray.mapX = (int)img->ray.posx;
		img->ray.mapY = (int)img->ray.posy;
		calculate_sside(img);
		calculate_vector(img, 0);
		calculate_wall_height(img);
		coloring_the_image(img, i);
		i++;
	}
	rendering_wepon(img, str);
	draw_minimap(img);
	event_keys(img);
	mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);
}

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

int	main(int ac, char **av)
{
	t_data	img;

	img.map = malloc(sizeof(t_map));
	if (main_parsing(av, ac, img.map, &img))
		return (1);
	initialize_data(&img);
	img.map->height = get_map_width(img.map, 1);
	img.map->width = get_map_width(img.map, 0);
	init_cube(&img);
	rendering_image(&img, 0, "./puunch.xpm");
	mlx_loop(img.mlx);
	exit(0);
}

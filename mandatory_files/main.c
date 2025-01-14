/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziel-hac <ziel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:22:47 by mlamrani          #+#    #+#             */
/*   Updated: 2025/01/10 16:00:50 by ziel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
	img->ray.movespeed = MOVESPEED;
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

void	put_to_image(t_data *img, char *str)
{
	int	img_width;
	int	img_height;

	mlx_destroy_image(img->mlx, img->sprite.img);
	img->sprite.img = mlx_xpm_file_to_image(img->mlx, str, &img_width,
			&img_height);
	img->sprite.addr = mlx_get_data_addr(img->sprite.img,
			&img->sprite.bits_per_pixel,
			&img->sprite.line_length,
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
	img->sprite.img = mlx_xpm_file_to_image(img->mlx, str, &img_width,
			&img_height);
	img->sprite.addr = mlx_get_data_addr(img->sprite.img,
			&img->sprite.bits_per_pixel,
			&img->sprite.line_length,
			&img->sprite.endian);
	my_mlx_pixel_put_sprite(img, img_height, img_width);
}

void	rendering_image(t_data *img, int i)
{
	mlx_destroy_image(img->mlx, img->img);
	img->img = mlx_new_image(img->mlx, WIDTH, HEIGHT);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	while (WIDTH > i)
	{
		calculate_ray(img, i);
		img->ray.mapx = (int)img->ray.posx;
		img->ray.mapy = (int)img->ray.posy;
		calculate_sside(img);
		calculate_vector(img, 0);
		calculate_wall_height(img);
		coloring_the_image(img, i);
		i++;
	}
	event_keys(img);
	mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);
}

int	main(int ac, char **av)
{
	t_data	img;
	int		i;

	i = 0;
	img.map = malloc(sizeof(t_map));
	while (i < 4)
		img.textures[i++].path = NULL;
	if (main_parsing(av, ac, &img, NULL))
		return (free_end(&img), 1);
	initialize_data(&img);
	init_cube(&img);
	rendering_image(&img, 0);
	mlx_loop(img.mlx);
	exit(0);
}

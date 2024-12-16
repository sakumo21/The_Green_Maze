/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziel-hac <ziel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:22:47 by mlamrani          #+#    #+#             */
/*   Updated: 2024/12/15 21:48:20 by ziel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	initialize_data(t_data *img)
{
	if (img->map->player == 'N') // Facing North
    {
        img->ray.dirX = 0;
        img->ray.dirY = -1;
        img->ray.planeX = 0.66;
        img->ray.planeY = 0;
    }
    else if (img->map->player == 'S') // Facing South
    {
        img->ray.dirX = 0;
        img->ray.dirY = 1;
        img->ray.planeX = -0.66;
        img->ray.planeY = 0;
    }
    else if (img->map->player == 'E') // Facing East
    {
        img->ray.dirX = 1;
        img->ray.dirY = 0;
        img->ray.planeX = 0;
        img->ray.planeY = 0.66;
    }
    else if (img->map->player == 'W') // Facing West
    {
        img->ray.dirX = -1;
        img->ray.dirY = 0;
        img->ray.planeX = 0;
        img->ray.planeY = -0.66;
    }
	img->ray.color = 0X0000FF;
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
		exit (0);
	img->img = mlx_new_image(img->mlx, WIDTH, HEIGHT);
	if (!img->img)
		exit (0);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	if (!img->addr)
		exit (0);
	img->map->minimap_height = HEIGHT / 8;
	img->map->minimap_width = WIDTH / 8;
	img->map->tile_size = img->map->minimap_width / img->map->width;
}


void	put_to_image(t_data *img, char *str)
{
	int		img_width;
	int		img_height;
	mlx_destroy_image(img->mlx, img->sprite.img);
	img->sprite.img = mlx_xpm_file_to_image(img->mlx, str, &img_width, &img_height);
	img->sprite.addr = mlx_get_data_addr(img->sprite.img, &img->sprite.bits_per_pixel, &img->sprite.line_length, &img->sprite.endian);
	my_mlx_pixel_put_sprite(img,0, 350, img_height, img_width);
	mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);
}

void	rendering_wepon(t_data *img, char *str)
{
	int			img_width;
	int			img_height;

   	img->sprite.img = mlx_xpm_file_to_image(img->mlx, str, &img_width, &img_height);
	img->sprite.addr = mlx_get_data_addr(img->sprite.img, &img->sprite.bits_per_pixel, &img->sprite.line_length, &img->sprite.endian);
	my_mlx_pixel_put_sprite(img,0, 350, img_height, img_width);
	mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);
}

void	rendering_image(t_data *img, int i, char *str)
{
	int		mapX;
	int		mapY;

	img->img = mlx_new_image(img->mlx, WIDTH, HEIGHT);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	while (WIDTH > i)
	{
		calculate_ray(img, i);
		mapX = (int)img->ray.posx;
		mapY = (int)img->ray.posy;
		calculate_sside(img, mapX, mapY);
		calculate_vector(img, mapX, mapY, 0);
		calculate_wall_height(img, 0);
		if (img->ray.side == 1)
			img->ray.color = img->ray.color / 2;
		coloring_the_image(img, i, img->ray.color);
		i++;
	}
	event_keys(img);
	draw_minimap(img);
	mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);
	rendering_wepon(img, str);
}  

int main(int ac, char **av)
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

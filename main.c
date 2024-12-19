/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:22:47 by mlamrani          #+#    #+#             */
/*   Updated: 2024/12/19 14:43:22 by mlamrani         ###   ########.fr       */
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
    {
        free_resources(img);
        exit (0);
    }
    img->img = mlx_new_image(img->mlx, WIDTH, HEIGHT);
    if (!img->img)
    {
        free_resources(img);
        exit (0);
    }
    img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
            &img->line_length, &img->endian);
    if (!img->addr)
    {
        free_resources(img);
        exit (0);
    }
    img->map->minimap_height = HEIGHT / 8;
    img->map->minimap_width = WIDTH / 8;
    img->map->tile_size = img->map->minimap_width / img->map->width;
    load_textures(img);
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

    if (img->sprite.img != NULL)
    {
        mlx_destroy_image(img->mlx, img->sprite.img);
    }
   	img->sprite.img = mlx_xpm_file_to_image(img->mlx, str, &img_width, &img_height);
	img->sprite.addr = mlx_get_data_addr(img->sprite.img, &img->sprite.bits_per_pixel, &img->sprite.line_length, &img->sprite.endian);
	my_mlx_pixel_put_sprite(img,0, 350, img_height, img_width);
} 

void	rendering_image(t_data *img, int i, char *str)
{
    // (void) str;
	// free_textures(img);
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
		calculate_wall_height(img, 0);
		coloring_the_image(img, i, img->ray.color);
		i++;
	}
	rendering_wepon(img, str);
	draw_minimap(img);
	event_keys(img);
	mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);
}
void free_textures(t_data *img)
{
    for (int i = 0; i < 4; i++)
    {
        if (img->textures[i].img)
            mlx_destroy_image(img->mlx, img->textures[i].img);
    }
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

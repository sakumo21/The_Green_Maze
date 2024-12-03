/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:22:47 by mlamrani          #+#    #+#             */
/*   Updated: 2024/12/03 22:10:43 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void my_mlx_pixel_put(t_data *data, int x, int color)
{
    char *dst;
    int y = data->ray.drawstart;
    
    if (x < 0 || x >= WIDTH)
        return;
        
    while (y <= data->ray.drawend)
    {
        if (y >= 0 && y < HEIGHT)
        {
            dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
            *(unsigned int*)dst = color;
        }
        y++;
    }
}

void coloring_the_image(t_data *img, int i, int color)
{
	for(int y = 0; y < img->ray.drawstart; y++)
	{
		char *dst = img->addr + (y * img->line_length + i * (img->bits_per_pixel / 8));
		*(unsigned int*)dst = 0x808080;
	}
	my_mlx_pixel_put(img, i, color);
	for(int y = img->ray.drawend; y < HEIGHT; y++)
	{
		char *dst = img->addr + (y * img->line_length + i * (img->bits_per_pixel / 8));
		*(unsigned int*)dst = 0x303030;
	}
}

void	calculate_sside(t_data *img, int mapX, int mapY)
{
	if (img->ray.rayX< 0)
	{
		img->ray.stepX = -1;
		img->ray.SsideX = (img->ray.posx - mapX) * img->ray.DsideX;
	}
	else
	{
		img->ray.stepX = 1;
		img->ray.SsideX = (mapX + 1.0 - img->ray.posx) * img->ray.DsideX;
	}
	if (img->ray.rayY< 0)
	{
		img->ray.stepY = -1;
		img->ray.SsideY = (img->ray.posy - mapY) * img->ray.DsideY;
	}
	else
	{
		img->ray.stepY = 1;
		img->ray.SsideY = (mapY + 1.0 - img->ray.posy) * img->ray.DsideY;
	}
}

void	calculate_ray(t_data *img, int i)
{
	img->ray.cameraX =  2 * (i / (double)WIDTH) - 1;
	img->ray.rayX = img->ray.dirX + img->ray.planeX * img->ray.cameraX;
	img->ray.rayY = img->ray.dirY + img->ray.planeY * img->ray.cameraX;
	if (img->ray.rayX == 0)
		img->ray.DsideX = 1e30;
	else
		img->ray.DsideX = fabs(1.0 / img->ray.rayX); 
	if (img->ray.rayY == 0)
		img->ray.DsideY = 1e30;
	else
		img->ray.DsideY = fabs(1.0 / img->ray.rayY);
}

void	calculate_vector(t_data *img, int mapX, int mapY, int hit)//need to remove one line (the map array is not included)
{

	while (!hit)
	{
		if (img->ray.SsideX < img->ray.SsideY)
		{
			img->ray.SsideX += img->ray.DsideX;
			mapX += img->ray.stepX;
			img->ray.side = 0;
		}
		else
		{
			img->ray.SsideY += img->ray.DsideY;
			mapY += img->ray.stepY;
			img->ray.side = 1;
		}
		if (img->map->map[mapY][mapX] != '0')
		{
			hit = 1;
			img->ray.color = 0X00000FF;
			if (img->map->map[mapY][mapX] == 'D')
			{
				if (img->ray.side == 0)
				{
					if ((int)(HEIGHT / (img->ray.SsideX - img->ray.DsideX)) > 420)
						hit = 0;
				}
				else
					if ((int)(HEIGHT / (img->ray.SsideY - img->ray.DsideY)) > 420)
						hit = 0;
			}
			else
				img->ray.color = 0XFF0000;
		}
	}
	if(img->ray.side == 0)
		img->ray.perpwalldist = (img->ray.SsideX - img->ray.DsideX);
	else
		img->ray.perpwalldist = (img->ray.SsideY - img->ray.DsideY);
	if (img->ray.perpwalldist == 0) 
		img->ray.perpwalldist = 1e-6;
}

void	initialize_data(t_data *img)
{
	img->ray.dirX = -1;
	img->ray.dirY = 0;
	img->ray.planeX = 0;
	img->ray.planeY = 0.66;
	img->ray.color = 0X0000FF;
}

void	calculate_wall_height(t_data *img, int lineheight)
{
	lineheight = (int)(HEIGHT / img->ray.perpwalldist);
	img->ray.drawstart = -lineheight / 2 + HEIGHT / 2;
	if (img->ray.drawstart <  0)
		img->ray.drawstart = 0;
	img->ray.drawend = lineheight / 2 + HEIGHT / 2;
	if (img->ray.drawend >= HEIGHT)
		img->ray.drawend =  HEIGHT - 1;
	
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
}

void	rendering_image(t_data *img, int i)
{
	int		mapX;
	int		mapY;

	mlx_destroy_image(img->mlx, img->img);
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
	img->map->height = get_map_width(img->map, 1);
	img->map->width = get_map_width(img->map, 0);
	draw_minimap(img, img->map->map);
	event_keys(img);
	mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);
}

int main(int ac, char **av)
{
	t_data	img;

    img.map = malloc(sizeof(t_map));
    if (main_parsing(av, ac, img.map, &img))
		return (1);
	// printf("map : (%s)\n", img.map->map[2]);
	// printf("%f %f\n", img.ray.posx, img.ray.posy);
	// printf("%c\n", img.map->map[(int)img.ray.posy][(int)img.ray.posx]);
	initialize_data(&img);
	init_cube(&img);
	rendering_image(&img, 0);
	mlx_loop(img.mlx);
	exit(0);
}	
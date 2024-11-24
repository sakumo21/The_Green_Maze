/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 19:00:09 by marvin            #+#    #+#             */
/*   Updated: 2024/10/30 19:00:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	calculate_vector(t_data *img, int mapX, int mapY, int hit)
{
	int map[mapWidth][mapHeight]=
	{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1},
	{1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,2,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};
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
		if (map[mapX][mapY] != 0)
		{
			hit = 1;
			if (map[mapX][mapY] == 2)
			{
				if (mapX == (int)img->ray.posx)
					if (mapY == (int)img->ray.posy + 1 || mapY == (int)img->ray.posy - 1)
						hit = 0;
				else if (mapY == (int)img->ray.posy)
					if (mapX == (int)img->ray.posx + 1 || mapX == (int)img->ray.posx - 1)
						hit = 0;
			}
		}
	}
	if (map[mapX][mapY] == 2)
		img->ray.color = 0X00FF00;
	else 
		img->ray.color = 0X0000FF;
	if(img->ray.side == 0)
		img->ray.perpwalldist = (img->ray.SsideX - img->ray.DsideX);
	else
		img->ray.perpwalldist = (img->ray.SsideY - img->ray.DsideY);
	if (img->ray.perpwalldist == 0) 
		img->ray.perpwalldist = 1e-6;
}

void	initialize_data(t_data *img)
{
	img->ray.posx = 20.55;
	img->ray.posy = 2.44;
	img->ray.dirX = -1;
	img->ray.dirY = 0;
	img->ray.planeX = 0;
	img->ray.planeY = 0.66;
	img->ray.color = 0X0000FF;
	img->ray.door = 0;
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
	img->win = mlx_new_window(img->mlx, WIDTH, HEIGHT, "fract_ol");
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
	int		lineheight;
	int		side;

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
		calculate_wall_height(img, lineheight);
		if (side == 1)
			img->ray.color = img->ray.color / 2;
		coloring_the_image(img, i, img->ray.color);
		i++;
	}
	event_keys(img);
	mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);
	mlx_loop(img->mlx);
}

int main()
{
	t_data	img;
	int worldMap[mapWidth][mapHeight]=
	{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1},
	{1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,2,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};
	
	initialize_data(&img);
	init_cube(&img);
	rendering_image(&img, 0);
}	

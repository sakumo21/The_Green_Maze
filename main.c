/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:22:47 by mlamrani          #+#    #+#             */
/*   Updated: 2024/12/16 16:42:28 by mlamrani         ###   ########.fr       */
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

unsigned int rgb_to_hex(int r, int g, int b)
{
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
    {
        printf("Error: RGB values must be between 0 and 255.\n");
        return 0;
    }
    return ((r << 16) | (g << 8) | b);
}

unsigned int convert_ceiling_to_hex(char *ceiling)
{
    char **rgb;
    int r;
	int g;
	int b;
    unsigned int color;
    rgb = ft_split(ceiling, ',');
	if (!rgb)
		return (0);
	
    r = ft_atoi(rgb[0]);
    g = ft_atoi(rgb[1]);
    b = ft_atoi(rgb[2]);
    free_range(rgb, 0);
    color = rgb_to_hex(r, g, b);
    return (color);
}



int get_texture_index(t_data *img)
{
	if (img->map->map[(int)img->ray.posy][(int)img->ray.posx] == 'D')
		return (4);
    if (img->ray.side == 0)
	{
		if (img->ray.rayX < 0)
		else
			return (0);
			return (1);
	}
    else
    {
		if (img->ray.rayY < 0)
			return (2);
		else
			return (3);
	}
}


void draw_textured_wall(t_data *img, int x)
{
    int texX, texY; 
    img->map->texture_index = get_texture_index(img);
    double wallX, step, texPos; 
	int wallHeight;
	int startY;
	int endY;
	
    if (img->ray.side == 0)
        wallX = img->ray.posy + img->ray.perpwalldist * img->ray.rayY;
    else
        wallX = img->ray.posx + img->ray.perpwalldist * img->ray.rayX;
    wallX -= (int)wallX;
	if (wallX < 0)
    	wallX += 1.0;

    texX = (int)(wallX * img->textures[img->map->texture_index].width);
    if ((img->ray.side == 0 && img->ray.rayX > 0) || (img->ray.side == 1 && img->ray.rayY < 0))
        texX = img->textures[img->map->texture_index].width - texX - 1;
    wallHeight = (int)(HEIGHT / img->ray.perpwalldist);
    startY = -wallHeight / 2 + HEIGHT / 2; 
    if (startY < 0)
		startY = 0;
    endY = wallHeight / 2 + HEIGHT / 2;
    if (endY >= HEIGHT)
		endY = HEIGHT - 1;
    step = 1.0 * img->textures[img->map->texture_index].height / wallHeight;
    texPos = (startY - HEIGHT / 2 + wallHeight / 2) * step; // Initial texture position
	// printf("texture index : %d\n", texture_index);	
    for (int y = startY; y < endY; y++)
    {
        texY = (int)texPos & (img->textures[img->map->texture_index].height - 1); // Wrap texY if necessary
        texPos += step;
        unsigned int color = *(unsigned int *)(img->textures[img->map->texture_index].addr +
            (texY * img->textures[img->map->texture_index].line_length + texX * (img->textures[img->map->texture_index].bits_per_pixel / 8)));
        char *dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
        *(unsigned int *)dst = color;
    }
}



void coloring_the_image(t_data *img, int i, int color)
{
	(void)color;
	unsigned int cel;
	unsigned int flo;

	cel = convert_ceiling_to_hex(img->ceiling);
	flo = convert_ceiling_to_hex(img->floor);
	for(int y = 0; y < img->ray.drawstart; y++)
	{
		char *dst = img->addr + (y * img->line_length + i * (img->bits_per_pixel / 8));
		*(unsigned int*)dst = cel;
	}
	draw_textured_wall(img, i);
	// my_mlx_pixel_put(img, i, color);
	for(int y = img->ray.drawend; y < HEIGHT; y++)
	{
		char *dst = img->addr + (y * img->line_length + i * (img->bits_per_pixel / 8));
		*(unsigned int*)dst = flo;
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
			if (img->map->map[mapY][mapX] == 'D')
			{
				if (mapX == (int)img->ray.posx)
				{
					if (mapY == (int)img->ray.posy + 1 || mapY == (int)img->ray.posy - 1)
						hit = 0;
				}
				else if (mapY == (int)img->ray.posy)
					if (mapX == (int)img->ray.posx + 1 || mapX == (int)img->ray.posx - 1)
						hit = 0;
			}
			else
			{
				img->map->texture_index = get_texture_index(img);	
				img->ray.color = 0XFF0000;
			}
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
	img->keys.w = 0;
	img->keys.s = 0;
	img->keys.a = 0;
	img->keys.d = 0;
	img->keys.left = 0;
	img->keys.right = 0;
}

void	calculate_wall_height(t_data *img, int lineheight)
{
	lineheight = (int)(HEIGHT / img->ray.perpwalldist);
    img->ray.drawstart = -lineheight / 2 + HEIGHT / 2;
    if (img->ray.drawstart < 0)
        img->ray.drawstart = 0;
    img->ray.drawend = lineheight / 2 + HEIGHT / 2;
    if (img->ray.drawend >= HEIGHT)
        img->ray.drawend = HEIGHT - 1;
	
}


void load_textures(t_data *img)
{
	img->textures[4].path = "textures/gb1.xpm";
	img->textures[0].img = mlx_xpm_file_to_image(img->mlx, img->textures[0].path, &img->textures[0].width, &img->textures[0].height);
    img->textures[1].img = mlx_xpm_file_to_image(img->mlx, img->textures[1].path, &img->textures[1].width, &img->textures[1].height);
    img->textures[2].img = mlx_xpm_file_to_image(img->mlx, img->textures[2].path, &img->textures[2].width, &img->textures[2].height);
    img->textures[3].img = mlx_xpm_file_to_image(img->mlx, img->textures[3].path, &img->textures[3].width, &img->textures[3].height);
	img->textures[4].img = mlx_xpm_file_to_image(img->mlx, img->textures[4].path, &img->textures[4].width, &img->textures[4].height);
    for (int i = 0; i < 5; i++)
    {
        if (!img->textures[i].img)
        {
            printf("Error loading texture %d\n", i);
            exit(1);
        }
        img->textures[i].addr = mlx_get_data_addr(img->textures[i].img,
            &img->textures[i].bits_per_pixel, &img->textures[i].line_length, &img->textures[i].endian);
    }
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
	load_textures(img);
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
	event_keys(img);
	draw_minimap(img);
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
	// printf("map : (%s)\n", img.map->map[2]);
	// printf("%f %f\n", img.ray.posx, img.ray.posy);
	// printf("%c\n", img.map->map[(int)img.ray.posy][(int)img.ray.posx]);
	initialize_data(&img);
	img.map->height = get_map_width(img.map, 1);
	img.map->width = get_map_width(img.map, 0);
	init_cube(&img);
	rendering_image(&img, 0);
	mlx_loop(img.mlx);
	free_textures(&img);
	exit(0);
}	
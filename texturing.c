/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texturing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziel-hac <ziel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:17:37 by ziel-hac          #+#    #+#             */
/*   Updated: 2024/12/17 15:18:24 by ziel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void load_textures(t_data *img)
{
	int i;

	i = 0;
	img->textures[4].path = "textures/gb1.xpm";
	printf("texture (%s)\n", img->textures[0].path);
	img->textures[0].img = mlx_xpm_file_to_image(img->mlx, img->textures[0].path, &img->textures[0].width, &img->textures[0].height);
    img->textures[1].img = mlx_xpm_file_to_image(img->mlx, img->textures[1].path, &img->textures[1].width, &img->textures[1].height);
    img->textures[2].img = mlx_xpm_file_to_image(img->mlx, img->textures[2].path, &img->textures[2].width, &img->textures[2].height);
    img->textures[3].img = mlx_xpm_file_to_image(img->mlx, img->textures[3].path, &img->textures[3].width, &img->textures[3].height);
	img->textures[4].img = mlx_xpm_file_to_image(img->mlx, img->textures[4].path, &img->textures[4].width, &img->textures[4].height);
    while (i < 5)
    {
        if (!img->textures[i].img)
        {
            printf("Error loading texture %d\n", i);
            exit(1);
        }
        img->textures[i].addr = mlx_get_data_addr(img->textures[i].img,
            &img->textures[i].bits_per_pixel, &img->textures[i].line_length, &img->textures[i].endian);
		i++;
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

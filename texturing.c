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

int	free_img(t_data *img)
{
	free_textures(img);
	mlx_destroy_image(img->mlx, img->img);
	mlx_destroy_window(img->mlx, img->win);
	mlx_destroy_display(img->mlx);
	free(img->mlx);
	exit(0);
}

void	punch_frames(t_data *img)
{
	rendering_image(img, 0, "./puunch3.xpm");
	usleep(10000);
	rendering_image(img, 0, "./puunch3.xpm");
	usleep(40000);
	rendering_image(img, 0, "./puunch2.xpm");
	usleep(40000);
	rendering_image(img, 0, "./puunch.xpm");
}

void	pistol_frames(t_data *img)
{
	rendering_image(img, 0, "./pistool2.xpm");
	usleep(40000);
	rendering_image(img, 0, "./pistool3.xpm");
	usleep(40000);
	rendering_image(img, 0, "./pistool4.xpm");
	usleep(40000);
	rendering_image(img, 0, "./pistool5.xpm");
	usleep(40000);
	rendering_image(img, 0, "./pistool2.xpm");
	usleep(40000);
	rendering_image(img, 0, "./pistool.xpm");
}
void load_textures(t_data *img)
{
	int	i;

	i = 0;
	img->textures[4].path = "textures/alien.xpm";
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
	double wallX, step, texPos;
	
	img->map->texture_index = get_texture_index(img);
	if (img->ray.side == 0)
		wallX = img->ray.posy + img->ray.perpwalldist * img->ray.rayy;
	else
		wallX = img->ray.posx + img->ray.perpwalldist * img->ray.rayx;
	wallX -= (int)wallX;
	if (wallX < 0)
		wallX += 1.0;
	texX = (int)(wallX * img->textures[img->map->texture_index].width);
	if ((img->ray.side == 0 && img->ray.rayx > 0) || (img->ray.side == 1 && img->ray.rayy < 0))
		texX = img->textures[img->map->texture_index].width - texX - 1;
	step = 1.0 * img->textures[img->map->texture_index].height / img->ray.wallheight;
	texPos = (img->ray.drawstart - HEIGHT / 2 + img->ray.wallheight / 2) * step;
	for (int y = img->ray.drawstart; y < img->ray.drawend; y++)
	{
		texY = (int)texPos & (img->textures[img->map->texture_index].height - 1);
		texPos += step;
		unsigned int color = *(unsigned int *)(img->textures[img->map->texture_index].addr +
			(texY * img->textures[img->map->texture_index].line_length + texX * (img->textures[img->map->texture_index].bits_per_pixel / 8)));
		char *dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

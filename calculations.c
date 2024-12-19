/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziel-hac <ziel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 18:25:06 by ziel-hac          #+#    #+#             */
/*   Updated: 2024/12/17 15:19:22 by ziel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

void	calculate_sside(t_data *img)
{
	if (img->ray.rayX < 0)
	{
		img->ray.stepX = -1;
		img->ray.SsideX = (img->ray.posx - img->ray.mapX) * img->ray.DsideX;
	}
	else
	{
		img->ray.stepX = 1;
		img->ray.SsideX = (img->ray.mapX + 1.0 - img->ray.posx) * img->ray.DsideX;
	}
	if (img->ray.rayY < 0)
	{
		img->ray.stepY = -1;
		img->ray.SsideY = (img->ray.posy - img->ray.mapY) * img->ray.DsideY;
	}
	else
	{
		img->ray.stepY = 1;
		img->ray.SsideY = (img->ray.mapY + 1.0 - img->ray.posy) * img->ray.DsideY;
	}
}

void	calculate_vector(t_data *img, int hit)//need to remove one line (the map array is not included)
{

	while (!hit)
	{
		if (img->ray.SsideX < img->ray.SsideY)
		{
			img->ray.SsideX += img->ray.DsideX;
			img->ray.mapX += img->ray.stepX;
			img->ray.side = 0;
		}
		else
		{
			img->ray.SsideY += img->ray.DsideY;
			img->ray.mapY += img->ray.stepY;
			img->ray.side = 1;
		}
		if (img->map->map[img->ray.mapY][img->ray.mapX] != '0')
		{
			hit = 1;
			if (img->map->map[img->ray.mapY][img->ray.mapX] == 'D')
			{
				if (img->ray.mapX == (int)img->ray.posx)
				{
					if (img->ray.mapY == (int)img->ray.posy + 1 || img->ray.mapY == (int)img->ray.posy - 1)
						hit = 0;
				}
				else if (img->ray.mapY == (int)img->ray.posy)
					if (img->ray.mapX == (int)img->ray.posx + 1 || img->ray.mapX == (int)img->ray.posx - 1)
						hit = 0;
			}
			else
			{
				// img->map->texture_index = get_texture_index(img);	
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

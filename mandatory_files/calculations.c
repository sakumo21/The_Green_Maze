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
	img->ray.camerax = 2 * (i / (double)WIDTH) - 1;
	img->ray.rayx = img->ray.dirx + img->ray.planex * img->ray.camerax;
	img->ray.rayy = img->ray.diry + img->ray.planey * img->ray.camerax;
	if (img->ray.rayx == 0)
		img->ray.dsidex = 1e30;
	else
		img->ray.dsidex = fabs(1.0 / img->ray.rayx);
	if (img->ray.rayy == 0)
		img->ray.dsidey = 1e30;
	else
		img->ray.dsidey = fabs(1.0 / img->ray.rayy);
}

void	calculate_sside(t_data *img)
{
	if (img->ray.rayx < 0)
	{
		img->ray.stepx = -1;
		img->ray.ssidex = (img->ray.posx - img->ray.mapx) * img->ray.dsidex;
	}
	else
	{
		img->ray.stepx = 1;
		img->ray.ssidex = (img->ray.mapx + 1.0 - img->ray.posx)
			* img->ray.dsidex;
	}
	if (img->ray.rayy < 0)
	{
		img->ray.stepy = -1;
		img->ray.ssidey = (img->ray.posy - img->ray.mapy) * img->ray.dsidey;
	}
	else
	{
		img->ray.stepy = 1;
		img->ray.ssidey = (img->ray.mapy + 1.0 - img->ray.posy)
			* img->ray.dsidey;
	}
}

void	calculate_vector(t_data *img, int hit)
{
	while (!hit)
	{
		if (img->ray.ssidex < img->ray.ssidey)
		{
			img->ray.ssidex += img->ray.dsidex;
			img->ray.mapx += img->ray.stepx;
			img->ray.side = 0;
		}
		else
		{
			img->ray.ssidey += img->ray.dsidey;
			img->ray.mapy += img->ray.stepy;
			img->ray.side = 1;
		}
		if (img->map->map[img->ray.mapy][img->ray.mapx] != '0')
			hit = 1;
	}
	if (img->ray.side == 0)
		img->ray.perpwalldist = (img->ray.ssidex - img->ray.dsidex);
	else
		img->ray.perpwalldist = (img->ray.ssidey - img->ray.dsidey);
	if ((double)img->ray.perpwalldist < 0.000001)
		img->ray.perpwalldist = 0.00001;
}

void	calculate_wall_height(t_data *img)
{
	img->ray.wallheight = (int)(HEIGHT / img->ray.perpwalldist);
	img->ray.drawstart = -img->ray.wallheight / 2 + HEIGHT / 2;
	if (img->ray.drawstart < 0)
		img->ray.drawstart = 0;
	img->ray.drawend = img->ray.wallheight / 2 + HEIGHT / 2;
	if (img->ray.drawend >= HEIGHT)
		img->ray.drawend = HEIGHT - 1;
}

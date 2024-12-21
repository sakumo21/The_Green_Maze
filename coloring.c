/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coloring.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 18:29:29 by ziel-hac          #+#    #+#             */
/*   Updated: 2024/12/21 13:21:55 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int get_texture_index(t_data *img)
{
	if (img->map->map[img->ray.mapY][img->ray.mapX] == 'D')
		return (4);
    if (img->ray.side == 0)
	{
		if (img->ray.rayX < 0)
			return (0);
		else
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
	for(int y = img->ray.drawend; y < HEIGHT; y++)
	{
		char *dst = img->addr + (y * img->line_length + i * (img->bits_per_pixel / 8));
		*(unsigned int*)dst = flo;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziel-hac <ziel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 18:27:58 by ziel-hac          #+#    #+#             */
/*   Updated: 2024/12/20 16:12:03 by ziel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	my_mlx_pixel_put_image(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	my_mlx_pixel_put(t_data *data, int x, int color)
{
	char	*dst;
	int		y;

	y = data->ray.drawstart;
	if (x < 0 || x >= WIDTH)
		return ;
	while (y <= data->ray.drawend)
	{
		if (y >= 0 && y < HEIGHT)
		{
			dst = data->addr + (y * data->line_length + x
					* (data->bits_per_pixel / 8));
			*(unsigned int *)dst = color;
		}
		y++;
	}
}

void	my_mlx_pixel_put_sprite(t_data *data, int h, int w)
{
	int				i;
	int				y;
	int				src_pixel_index;
	unsigned int	src_color;

	i = 0;
	while (i < w)
	{
		y = 0;
		while (y < h)
		{
			src_pixel_index = (y * data->sprite.line_length)
				+ (i * (data->sprite.bits_per_pixel / 8));
			src_color = *(unsigned int *)(data->sprite.addr
					+ src_pixel_index);
			if (src_color == 0x000000 || src_color == 0xFF000000)
			{
				y++;
				continue ;
			}
			if (0 + i < 0 || 0 + i >= WIDTH || 0 + 350 < 0 || 0 + 350 >= HEIGHT) // imkn t7aydo
				continue ; // imkn it7aydo 
			my_mlx_pixel_put_image(data, 0 + i, 350 + y, src_color);
			y++;
		}
		i++;
	}
}

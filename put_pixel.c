/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 18:27:58 by ziel-hac          #+#    #+#             */
/*   Updated: 2024/12/21 14:17:36 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3D.h"

void	my_mlx_pixel_put_image(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

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

void my_mlx_pixel_put_sprite(t_data *data, int start_x, int start_y, int height, int width) 
{
    int	i; 
	int	y;
	int	dest_x;
	int	dest_y;

	i = 0;
    while (i < width) 
	{
		y = 0;
        while (y < height) 
		{
            int src_pixel_index = (y * data->sprite.line_length) + (i * (data->sprite.bits_per_pixel / 8));
            unsigned int src_color = *(unsigned int *)(data->sprite.addr + src_pixel_index);
			if (src_color == 0x000000 || src_color == 0xFF000000)
			{
				y++;
				continue;
			}
            dest_x = start_x + i;
            dest_y = start_y + y;
            if (dest_x < 0 || dest_x >= WIDTH || dest_y < 0 || dest_y >= HEIGHT)
                continue;
			my_mlx_pixel_put_image(data, dest_x, dest_y, src_color);
			y++;
        }
		i++;
    }

}

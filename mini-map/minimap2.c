/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 18:13:25 by mlamrani          #+#    #+#             */
/*   Updated: 2024/12/22 09:57:48 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	draw_player(t_data *img)
{
	t_circle	player_circle;
	t_line		player_line;

	player_circle.cx = img->ray.posx * img->map->tile_size + X_OFFSET;
	player_circle.cy = img->ray.posy * img->map->tile_size + Y_OFFSET;
	player_circle.radius = img->map->tile_size / 3;
	player_circle.color = 0x000000;
	player_line.x1 = player_circle.cx;
	player_line.y1 = player_circle.cy;
	player_line.x2 = player_circle.cx + img->ray.dirx * img->map->tile_size;
	player_line.y2 = player_circle.cy + img->ray.diry * img->map->tile_size;
	player_line.color = 0x000000;
	draw_circle(img, &player_circle);
	draw_line(img, &player_line, 0, 0);
}

void	draw_minimap(t_data *img, int i)
{
	int	j;
	int	x;
	int	y;
	int	row_length;

	i = 0;
	while (i < img->map->height)
	{
		row_length = ft_strlen(img->map->map[i]);
		j = 0;
		while (j < row_length)
		{
			x = j * img->map->tile_size + X_OFFSET;
			y = i * img->map->tile_size + Y_OFFSET;
			if (img->map->map[i][j] == '1')
				draw_rectangle(img, x, y, 0xFF0000);
			else if (img->map->map[i][j] == '0')
				draw_rectangle(img, x, y, 0x696969);
			else if (img->map->map[i][j] == 'D')
				draw_rectangle(img, x, y, 0x0000FF);
			j++;
		}
		i++;
	}
	draw_player(img);
}

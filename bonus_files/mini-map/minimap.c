/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziel-hac <ziel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 18:17:42 by mlamrani          #+#    #+#             */
/*   Updated: 2024/12/21 15:48:21 by ziel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	get_map_width(t_map *map, int i)
{
	int	max_width;
	int	height;
	int	row_width;

	max_width = 0;
	height = 0;
	while (map->map[height] != NULL)
	{
		height++;
		map->height = height;
		if (i == 1)
			return (height);
	}
	i = 0;
	while (i < height)
	{
		row_width = ft_strlen(map->map[i]);
		if (row_width > max_width)
			max_width = row_width;
		i++;
	}
	return (max_width);
}

void	my_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_rectangle(t_data *img, int x, int y, int color)
{
	int	i;
	int	j;

	i = x;
	while (i < x + img->map->tile_size)
	{
		j = y;
		while (j < y + img->map->tile_size)
		{
			my_put(img, i, j, color);
			j++;
		}
		i++;
	}
}

void	draw_circle(t_data *img, t_circle *circle)
{
	int	x;
	int	y;
	int	dx;
	int	dy;

	y = -circle->radius;
	while (y <= circle->radius)
	{
		x = -circle->radius;
		while (x <= circle->radius)
		{
			dx = circle->cx + x;
			dy = circle->cy + y;
			if ((x * x) + (y * y) <= (circle->radius * circle->radius))
				my_put(img, dx, dy, circle->color);
			x++;
		}
		y++;
	}
}

void	draw_line(t_data *img, t_line *line, int dx, int i)
{
	int		steps;
	int		dy;
	float	x_inc;
	float	y_inc;

	dx = line->x2 - line->x1;
	dy = line->y2 - line->y1;
	if (abs(dx) > abs(dy))
		steps = abs(dx);
	else
		steps = abs(dy);
	x_inc = dx / (float)steps;
	y_inc = dy / (float)steps;
	line->x = line->x1;
	line->y = line->y1;
	while (i <= steps)
	{
		my_put(img, line->x, line->y, line->color);
		line->x += x_inc;
		line->y += y_inc;
		i++;
	}
}

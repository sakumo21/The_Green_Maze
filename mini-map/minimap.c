/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 18:17:42 by mlamrani          #+#    #+#             */
/*   Updated: 2024/12/09 14:47:52 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int get_map_width(t_map *map, int i) {
    int max_width = 0;
    int height = 0;
    
    while (map->map[height] != NULL)
    {
        height++;
        map->height = height;
        if (i == 1)
            return height;
    }
    for (int i = 0; i < height; i++) {
        int row_width = ft_strlen(map->map[i]);
        if (row_width > max_width)
            max_width = row_width;
    }

    return max_width;
}

void my_put(t_data *data, int x, int y, int color)
{
    char *dst;

    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

void draw_rectangle(t_data *img, int x, int y, int width, int height, int color)
{
    int i, j;

    for (i = x; i < x + width; i++) {
        for (j = y; j < y + height; j++) {
            my_put(img, i, j, color);  
        }
    }
}


void draw_circle(t_data *img, int cx, int cy, int radius, int color)
{
    int x, y;
    int dx, dy;

    for (y = -radius; y <= radius; y++) {
        for (x = -radius; x <= radius; x++) {
            dx = cx + x;
            dy = cy + y;
            // Check if the point lies within the circle
            if ((x * x) + (y * y) <= (radius * radius)) {
               my_put(img, dx, dy, color);
            }
        }
    }
}

void draw_line(t_data *img, int x1, int y1, int x2, int y2, int color)
{
    int dx, dy, steps, i;
    float x_inc, y_inc, x, y;

    dx = x2 - x1;
    dy = y2 - y1;

    if (abs(dx) > abs(dy))
        steps = abs(dx);
    else
        steps = abs(dy);

    x_inc = dx / (float)steps;
    y_inc = dy / (float)steps;

    x = x1;
    y = y1;

    for (i = 0; i <= steps; i++)
    {
        my_put(img, x, y, color);
        x += x_inc;
        y += y_inc;
    }
}



void draw_player(t_data *img)
{
    int player_x;
    int player_y;
    int radius;
    int line_x;
    int line_y;
    int line_length;

    player_x = img->ray.posx * img->map->tile_size + x_offset;
    player_y = img->ray.posy * img->map->tile_size + y_offset;
    radius = img->map->tile_size / 3; // Smaller radius for the player circle
    line_length = img->map->tile_size; // Length of the direction line
    line_x = player_x + img->ray.dirX * line_length;
    line_y = player_y + img->ray.dirY * line_length;
    draw_circle(img, player_x, player_y, radius, 0x000000); // Red circle for the player
    draw_line(img, player_x, player_y, line_x, line_y, 0x000000); // Green line for direction
}


void draw_minimap(t_data *img)
{
    int i, j;
    int x, y;

    for (i = 0; i < img->map->height; i++) {
        for (j = 0; j < img->map->width; j++) {
            x = j * img->map->tile_size + x_offset;
            y = i * img->map->tile_size + y_offset;
            if (img->map->map[i][j] == '1')  // Wall
                draw_rectangle(img, x, y, img->map->tile_size, img->map->tile_size, 0xFF0000);  // Red for wall
            else if (img->map->map[i][j] == '0')  // Floor
                draw_rectangle(img, x, y, img->map->tile_size, img->map->tile_size, 0x696969);  // Grey for floor
            else if (img->map->map[i][j] == 'D')
                draw_rectangle(img, x, y, img->map->tile_size, img->map->tile_size, 0x0000FF);  // BLUE for Doors
        }
    }
    draw_player(img);
}









/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 18:17:42 by mlamrani          #+#    #+#             */
/*   Updated: 2024/12/05 16:34:57 by mlamrani         ###   ########.fr       */
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

    // Iterate over the area of the rectangle
    for (i = x; i < x + width; i++) {
        for (j = y; j < y + height; j++) {
            my_put(img, i, j, color);  
        }
    }
}
void draw_rectangle_border(t_data *img, int x, int y, int width, int height, int color)
{
    int i, j;

    // Draw a black border around the rectangle by coloring the edges
    for (i = x; i < x + width; i++) {
        my_put(img, i, y, color);  // Top border
        my_put(img, i, y + height - 1, color);  // Bottom border
    }

    for (j = y; j < y + height; j++) {
        my_put(img, x, j, color);  // Left border
        my_put(img, x + width - 1, j, color);  // Right border
    }
}


void draw_minimap(t_data *img)
{
    int i, j;
    int x, y;

    // Iterate over the map grid
    for (i = 0; i < img->map->height; i++) {
        for (j = 0; j < img->map->width; j++) {
            // Calculate the position of the current tile on the minimap
            x = j * img->map->tile_size;
            y = i * img->map->tile_size;

            // Check the map character and draw the appropriate tile
            if (img->map->map[i][j] == '1')  // Wall
                {draw_rectangle(img, x, y, img->map->tile_size, img->map->tile_size, 0xFF0000);  // Red for wall
                draw_rectangle_border(img, x, y, img->map->tile_size, img->map->tile_size, 0x000000);}
            else if (img->map->map[i][j] == '0')  // Floor
                {draw_rectangle(img, x, y, img->map->tile_size, img->map->tile_size, 0xFFFFFF);  // White for floor
                draw_rectangle_border(img, x, y, img->map->tile_size, img->map->tile_size, 0x000000);}
            else if (img->map->map[i][j] == 'D')
                {draw_rectangle(img, x, y, img->map->tile_size, img->map->tile_size, 0x0000FF);  // BLUE for Doors
                draw_rectangle_border(img, x, y, img->map->tile_size, img->map->tile_size, 0x000000);}        
        }
    }
}









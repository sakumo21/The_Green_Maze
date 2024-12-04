/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 18:17:42 by mlamrani          #+#    #+#             */
/*   Updated: 2024/12/04 19:07:13 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void my_put(t_data *data, int x, int y, int color)
{
    char *dst;

    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}


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

void draw_minimap(t_data *img)
{
    int cell_size = 13; // Increased size for visibility
    int x, y;
    int color;
    int offset_x = 30; // Horizontal offset for the minimap
    int offset_y = 30; // Vertical offset for the minimap

    // Render the map
    for (int i = 0; i < img->map->height; i++) {
        for (int j = 0; j < img->map->width; j++) {
            if (j < (int)strlen(img->map->map[i])) { // Ensure the row is not out of bounds
                if (img->map->map[i][j] == '1')
                    color = 0xFF0000; // Red for walls
                else if (img->map->map[i][j] == '0')
                    color = 0xFFFFFF; // White for empty space
                else if (img->map->map[i][j] == 'D')
                    color = 0x0000FF; // Blue for sprites
                else if (img->map->map[i][j] == img->map->player)
                    color = 0xFFFFFF; 
                else
                    continue;

                // Draw the corresponding pixels with offsets
                for (y = i * cell_size + offset_y; y < (i + 1) * cell_size + offset_y; y++) {
                    for (x = j * cell_size + offset_x; x < (j + 1) * cell_size + offset_x; x++) {
                        my_put(img, x, y, color);
                    }
                }
            }
        }
    }
}







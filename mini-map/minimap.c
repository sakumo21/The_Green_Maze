/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 18:17:42 by mlamrani          #+#    #+#             */
/*   Updated: 2024/12/07 16:57:15 by mlamrani         ###   ########.fr       */
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

// void draw_player(t_data *img)
// {
//     int player_x;
//     int player_y;
//     int radius;
//     int line_length;
//     int line_x;
//     int line_y;

//     player_x = img->ray.posx * img->map->tile_size;
//     player_y = img->ray.posy * img->map->tile_size;

//     radius = img->map->tile_size / 2; // Smaller radius for the player circle
//     draw_circle(img, player_x, player_y, radius, 0xFF0000); // Red circle for the player
// }


// Draw a line from (x0, y0) to (x1, y1)
void draw_line(t_data *img, int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx - dy;

    while (x0 != x1 || y0 != y1) {
        my_put(img, x0, y0, color); // Put pixel at current position
        int e2 = 2 * err;

        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

#include <math.h>

void draw_line(t_data *img, int x1, int y1, int x2, int y2, int color)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;
    int e2;

    while (1) {
        my_put(img, x1, y1, color); // Plot the pixel

        if (x1 == x2 && y1 == y2)
            break;

        e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

void draw_player(t_data *img)
{
    int player_x = img->ray.posx * img->map->tile_size;
    int player_y = img->ray.posy * img->map->tile_size;
    int radius = img->map->tile_size / 2; // Smaller radius for the player circle
    int line_length = img->map->tile_size; // Length of the direction line

    // Draw the player as a circle
    draw_circle(img, player_x, player_y, radius, 0xFF0000); // Red circle for the player

    // Calculate the endpoint of the line
    int line_x = player_x + cos(img->ray.dir) * line_length;
    int line_y = player_y + sin(img->ray.dir) * line_length;

    // Draw the line representing the player's direction
    draw_line(img, player_x, player_y, line_x, line_y, 0x00FF00); // Green line for direction
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
    draw_player(img);
}









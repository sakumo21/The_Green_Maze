/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:28:51 by mlamrani          #+#    #+#             */
/*   Updated: 2024/12/19 16:00:27 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../cub3D.h"

int mini_map(char *line, t_map *map, int fd, int i)
{
    char *str;
    str = NULL;
    while(1)
    {
        if (!str)
            str = ft_strdup("");
        if(!line)
            break;
        str = ft_strjoin(str, line);
        line = get_next_line(fd);
    }
    close(fd);
    if (!str || !str[0])
        return (printf("Error: Empty map.\n"), 1);
    while (str[i])
    {
        if (str[i] == '\n' && str[i + 1] == '\n')
            return(printf("Error: Empty line in map.\n"), 1);
        i++;
    }
    map->map = ft_split(str, '\n');
    return (0);
}

void flood_fill(t_map *map, int rows, int cols, int x, int y)
{
    if (x < 0 || x >= rows || y < 0 || y >= cols)
    {
        printf("Error: Map is open! Flood fill reached out-of-bounds at (%d, %d)\n", x, y);
        exit(1);
    }
    if (map->map[x][y] == '1' || map->map[x][y] == 'F')
        return;
    else if (map->map[x][y] == '0')  // If it's an open space
        map->map[x][y] = '+';
    else if (map->map[x][y] == 'D')  // If it's a door
        map->map[x][y] = '-';
    else if (map->map[x][y] == map->player)  // If it's the player
        map->map[x][y] = '+';
    map->map[x][y] = 'F';
    flood_fill(map, rows, cols, x + 1, y);
    flood_fill(map, rows, cols, x - 1, y);
    flood_fill(map, rows, cols, x, y + 1);
    flood_fill(map, rows, cols, x, y - 1);
}

void check_map_with_flood_fill(t_map *map, int start_x, int start_y)
{
    int max_y = 0;
    int max_x = 0;

    while (map->map[max_y])
        max_y++;
    max_x = ft_strlen(map->map[0]);
    flood_fill(map, max_y, max_x, start_y, start_x);
    for (int i = 0; i < max_y; i++)
    {
        for (int j = 0; j < (int)ft_strlen(map->map[i]); j++)
        {
            if (map->map[i][j] == '0' || map->map[i][j] == 'D')
            {
                printf("Error: Map contains unreachable tiles at (%d, %d).\n", i, j);
                exit(1);
            }
        }
    }
}

int my_map(t_map *map, t_data *img)
{
    int max_y;

    max_y = 0;
    if (parsing_map(map->map))
        return (1);
    while (map->map[max_y] != NULL)
        max_y++;
    if (check_map_enclosure(map->map, 0, 0))
        return (1);
    if (find_starting_point(map->map, img, 0))
        return (1);
    check_map_with_flood_fill(map, img->map->player_x, img->map->player_y);
    return (0);
}

int check_map_enclosure(char **map, int i, int j)
{
    int max_y = 0;

    // Find map height
    while (map[max_y])
        max_y++;

    // Check top and bottom rows
    while (map[0][i])
    {
        if (map[0][i] != '1' && map[0][i] != ' ')
            return (printf("Error: Map not enclosed at top row.\n"), 1);
        i++;
    }
    i = 0;
    while (map[max_y - 1][i])
    {
        if (map[max_y - 1][i] != '1' && map[max_y - 1][i] != ' ')
            return (printf("Error: Map not enclosed at bottom row.\n"), 1);
        i++;
    }

    // Check side boundaries, ignoring spaces until walls are hit
    for (i = 0; i < max_y; i++)
    {
        // Skip leading spaces
        j = 0;
        while (map[i][j] == ' ')
            j++;
        if (map[i][j] != '1') // First non-space must be a wall
            return (printf("Error: Map not enclosed on the left at row %d.\n", i), 1);

        // Check from the right side
        j = ft_strlen(map[i]) - 1;
        while (j >= 0 && map[i][j] == ' ')
            j--;
        if (map[i][j] != '1') // Last non-space must be a wall
            return (printf("Error: Map not enclosed on the right at row %d.\n", i), 1);
    }
    return 0;
}

int parsing_map(char **map)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] != '1' && map[i][j] != '0' && map[i][j] != ' ' && map[i][j] != 'N' && map[i][j] != 'S' && map[i][j] != 'W' && map[i][j] != 'E' && map[i][j] != 'D')
                return (printf("Error: Invalid map character at (%d, %d) = '%c'\n", i, j, map[i][j]), 1);
            j++;
        }
        i++;
    }
    return (0);
}

int find_starting_point(char **map, t_data *img, int i)
{
    int j;
    int found;

    found = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W' || map[i][j] == 'E')
            {
                if (found)
                    return (printf("Error: Multiple starting points found.\n"), 1);
                img->ray.posx = j + 0.5;
                img->ray.posy = i + 0.5;
                img->map->player_x = j;
                img->map->player_y = i;
                img->map->player = map[i][j];
                img->map->map[i][j] = '0';
                found = 1;
            }
            else if (map[i][j] != '1' && map[i][j] != '0' && map[i][j] != ' ' && map[i][j] != 'D')
                return (printf("Error: Invalid character '%c' at (%d, %d)\n", map[i][j], i, j), 1);
            j++;
        }
        i++;
    }
    if (!found)
        return (printf("Error: No starting point found (N, S, W, or E).\n"), 1);
    return (0);
}

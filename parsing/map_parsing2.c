#include "../cub3D.h"

int check_filled_map(char **map)
{
    int i = 0;
    int j;

    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] == '0')
            {
                printf("Error: Unfilled space at (%d, %d)\n", j, i);
                return (1);
            }
            j++;
        }
        i++;
    }
    return (0);
}

void flood_fill(t_map *map, int x, int y, int max_x, int max_y)
{
    // printf("%d %d\n", x, y);
    if (x < 0 || y < 0 || y >= max_y || x >= (int)ft_strlen(map->map[y]))
        return;
    if (map->map[y][x] != '0' && map->map[y][x] != 'D' && map->map[y][x] != 'E' && map->map[y][x] != 'N' && map->map[y][x] != 'S' && map->map[y][x] != 'W')
        return;
    if (map->map[y][x] == '0')
        map->map[y][x] = '.';
    else if (map->map[y][x] == 'D')
        map->map[y][x] = '+';
    else if (map->map[y][x] == 'N' || map->map[y][x] == 'S' || map->map[y][x] == 'W' || map->map[y][x] == 'E')
    {
        map->player = map->map[y][x];
        map->map[y][x] = '-';
    }
        
    // printf("Filling (%d, %d)\n", x, y);
    flood_fill(map, x + 1, y, max_x, max_y);  // Right
    flood_fill(map, x - 1, y, max_x, max_y);  // Left
    flood_fill(map, x, y + 1, max_x, max_y);  // Down
    flood_fill(map, x, y - 1, max_x, max_y);  // Up
}

void flood_fill2(t_map *map, int x, int y, int max_x, int max_y)
{
    // printf("%d %d\n", x, y);
    if (x < 0 || y < 0 || y >= max_y || x >= (int)ft_strlen(map->map[y]))
        return ;
    if (map->map[y][x] != '.' && map->map[y][x] != '+' && map->map[y][x] != '-')
        return ;
    if (map->map[y][x] == '.')
        map->map[y][x] = '0';
    else if (map->map[y][x] == '+')
        map->map[y][x] = 'D';
    else if (map->map[y][x] == '-')
        map->map[y][x] = '0';
    
    // printf("Filling (%d, %d)\n", x, y);
    flood_fill2(map, x + 1, y, max_x, max_y);  // Right
    flood_fill2(map, x - 1, y, max_x, max_y);  // Left
    flood_fill2(map, x, y + 1, max_x, max_y);  // Down
    flood_fill2(map, x, y - 1, max_x, max_y);  // Up
}

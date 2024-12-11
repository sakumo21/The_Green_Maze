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
    // flood_fill(map, img->ray.posx, img->ray.posy, max_x, max_y);
    // if (check_filled_map(map->map))
    //     return (printf("Error: The map is not properly enclosed.\n"), 1);
    // flood_fill2(map, img->ray.posx, img->ray.posy, max_x, max_y);
    return (0);
}

int check_map_enclosure(char **map, int i, int j)
{
    int max_y;

    max_y = 0;
    while (map[max_y]) //height
        max_y++;
    while (map[0][j])
    {
        if (map[0][j] != '1')
            return (printf("Error: Map not enclosed at top row.\n"), 1);
        j++;
    }
    j = 0;
    while (map[max_y - 1][j])
    {
        if (map[max_y - 1][j] != '1')
            return (printf("Error: Map not enclosed at bottom row.\n"), 1);
        j++;
    }
    while (i < max_y)
    {
        if (map[i][0] != '1' || map[i][ft_strlen(map[i]) - 1] != '1')
            return (printf("Error: Map not enclosed at row %d.\n", i), 1);
        i++;
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

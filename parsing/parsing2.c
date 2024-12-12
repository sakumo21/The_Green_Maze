#include "../cub3D.h"




int texturing(char **path, char *new, t_flag *flag, t_data *img)
{
    path[0] = ft_strtrim(path[0], "\n");
    if (!ft_strncmp(path[0], "N", ft_strlen("N")) || !ft_strncmp(path[0], "NO", ft_strlen("NO")))
        return (check_and_set(path, &flag->N_check, "North texture", flag));
    else if (!ft_strncmp(path[0], "S", ft_strlen("S")) || !ft_strncmp(path[0], "SO", ft_strlen("SO")))
        return (check_and_set(path, &flag->S_check, "South texture", flag));
    else if (!ft_strncmp(path[0], "W", ft_strlen("W")) || !ft_strncmp(path[0], "WE", ft_strlen("WE")))
        return (check_and_set(path, &flag->W_check, "West texture", flag));
    else if (!ft_strncmp(path[0], "E", ft_strlen("E")) || !ft_strncmp(path[0], "EA", ft_strlen("EA")))
        return (check_and_set(path, &flag->E_check, "East texture", flag));
    else if (!ft_strncmp(path[0], "F", 1))
        return (check_set_color(&flag->F_check, "Floor color", new, img));
    else if (!ft_strncmp(path[0], "C", 1))
        return (check_set_color(&flag->C_check, "Ceiling color", new, img));
    else if (ft_strncmp(path[0], "N", ft_strlen("N")) && ft_strncmp(path[0], "NO", ft_strlen("NO")) &&
                ft_strncmp(path[0], "S", ft_strlen("S")) && ft_strncmp(path[0], "SO", ft_strlen("SO")) &&
                ft_strncmp(path[0], "W", ft_strlen("W")) && ft_strncmp(path[0], "WE", ft_strlen("WE")) &&
                ft_strncmp(path[0], "E", ft_strlen("E")) && ft_strncmp(path[0], "EA", ft_strlen("EA")) &&
                ft_strncmp(path[0], "F", ft_strlen("F")) && ft_strncmp(path[0], "C", ft_strlen("C")) &&
                ft_isalpha(path[0][0]))
    {
        printf("Error : %s is not a valid identifier.\n", path[0]);
        flag->exit = 2;
        return (1);
    }
    else 
        return (1);
    return (0);
}

int check_set_color(int *flag, char *msg, char *new, t_data *img)
{
    if (*flag)
        return (printf("Error : %s already defined.\n", msg), 1);
    *flag = 1;
    if (new)
    {
        if (check_range(new, img))
            return (1);
    }
    return (0);
}

int check_and_set(char **path, int *flag, char *msg, t_flag *flagg)
{
    if (*flag)
        return (printf("Error : %s already defined.\n", msg), 1);
    *flag = 1;
    path[1] = ft_strtrim(path[1], "\n");
    if (check_line(path, flagg))
        return (1);
    return (0);
}

void init_flag(t_flag *flag, t_map *map, t_data *img)
{
    flag->N_check = 0;
    flag->S_check = 0;
    flag->W_check = 0;
    flag->E_check = 0;
    flag->F_check = 0;
    flag->C_check = 0;
    flag->exit = 0;
    map->map = NULL;
    map->player = 0;
    map->player_x = 0;
    map->player_y = 0;
    img->floor = NULL;
    img->ceiling = NULL;
}

int parse_input(int ac, char **av)
{
    int i = 0;
    if (ac != 2)
        return (printf("Where is the file?\n"), 1);
    if (ft_strlen(av[1]) == 4 && !ft_strncmp(av[1] + ft_strlen(av[1]) - 4, ".cub", 4))
        return (printf("Error : add a name to your .cub file.\n"), 1);
    while(av[1][i] != '.')
        i++;
    if (av[1][i] == '.' && (av[1][i + 1] != 'c' || av[1][i + 2] != 'u' || av[1][i + 3] != 'b'))
        return (printf("Error : Put the right extension (.cub) !\n"), 1);
    else if (av[1][i] == '.' && av[1][i + 1] == 'c' && av[1][i + 2] == 'u' && av[1][i + 3] == 'b' && av[1][i + 4] != '\0')
        return (printf("Error : Put the right extension (.cub) !\n"), 1);
    return (0);
}

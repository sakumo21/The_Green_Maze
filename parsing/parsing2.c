/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziel-hac <ziel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 13:59:03 by mlamrani          #+#    #+#             */
/*   Updated: 2024/12/21 15:48:51 by ziel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"



int texturing(char **path, char *new, t_flag *flag, t_data *img)
{
    path[0] = ft_strtrim(path[0], "\n");
    if (!ft_strncmp(path[0], "N", ft_strlen("N")) || !ft_strncmp(path[0], "NO", ft_strlen("NO")))
    {
        if (path[1])
            img->textures[0].path = ft_strdup(ft_strtrim(path[1], "\n"));
        return (check_and_set(path, &flag->n_check, "North texture", flag));
    }
    else if (!ft_strncmp(path[0], "S", ft_strlen("S")) || !ft_strncmp(path[0], "SO", ft_strlen("SO")))
    {
        if (path[1])
            img->textures[1].path = ft_strdup(ft_strtrim(path[1], "\n"));
        return (check_and_set(path, &flag->s_check, "South texture", flag));
    }
    else if (!ft_strncmp(path[0], "W", ft_strlen("W")) || !ft_strncmp(path[0], "WE", ft_strlen("WE")))
    {   
        if (path[1])
            img->textures[2].path = ft_strdup(ft_strtrim(path[1], "\n"));
        return (check_and_set(path, &flag->w_check, "West texture", flag));
    }
    else if (!ft_strncmp(path[0], "E", ft_strlen("E")) || !ft_strncmp(path[0], "EA", ft_strlen("EA")))
    {
        if (path[1])
            img->textures[3].path = ft_strdup(ft_strtrim(path[1], "\n"));
        return (check_and_set(path, &flag->e_check, "East texture", flag));
    }
    else if (!ft_strncmp(path[0], "F", 1))
        return (check_set_color(&flag->f_check, "Floor color", new, img));
    else if (!ft_strncmp(path[0], "C", 1))
        return (check_set_color(&flag->c_check, "Ceiling color", new, img));
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
        if (check_range(new, img, new + 2))
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
    flag->n_check = 0;
    flag->s_check = 0;
    flag->w_check = 0;
    flag->e_check = 0;
    flag->f_check = 0;
    flag->c_check = 0;
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

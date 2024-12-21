/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 14:04:58 by mlamrani          #+#    #+#             */
/*   Updated: 2024/12/21 14:05:01 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../cub3D.h"

int first_parse(int ac, char **av, int *fd)
{
    if (parse_input(ac, av))
        return (1);
    *fd = open(av[1], O_RDONLY);
    if (*fd < 0)
        return (printf("Error : File not found.\n"), 1);
    return (0);
}

int main_parsing(char **av, int ac, t_map *map, t_data *img)
{
    int fd;
    char *line;
    t_flag flag;
    
    if (first_parse(ac, av, &fd))
        return (1);
    init_flag(&flag, map, img);
    while ((line = get_next_line(fd))) 
    {
        if (line[0] == '\n')
        {
            free(line);
            continue;
        }
        if (parse_line(line, &flag, 0, img))
            break;
        free(line);
    } 
    if (flag.exit == 2 || check_texture(&flag))
        return (1);
    if (mini_map(line, map, fd, 0) || my_map(map, img))
        return (1);
    close(fd);
    return (0);
}

int check_texture(t_flag *flag)
{
    int error = 0;

    print_error("North texture", &flag->N_check, &error);
    print_error("South texture", &flag->S_check, &error);
    print_error("West texture", &flag->W_check, &error);
    print_error("East texture", &flag->E_check, &error);
    print_error("Floor color", &flag->F_check, &error);
    print_error("Ceiling color", &flag->C_check, &error);
    if (error)
        return (1);
    return (0);
}

int parse_line(char *line, t_flag *flag, int i, t_data *img)
{
    char **path;
    char *new;
    char *temp;
    char *t;
    char *trimmed;
    
    new = NULL;
    temp = NULL;
    t = NULL;
    path = ft_split(line, ' ');
    if (!path)
        return (1);
    while (path[i])
    {
        trimmed = ft_strtrim(path[i], " ");
        if (!trimmed)
            return (free_path(path, new), 1);
        free(path[i]);
        path[i] = trimmed;
        if (new == NULL)
        {
            t = ft_strdup(trimmed);
            if (!t)
                return (free_path(path, new), 1);
            new = ft_strjoin(t, " ");
            free(t);
            if (!new)
                return (free_path(path, new), 1);
        }
        else
        {
            temp = ft_strjoin(new, trimmed);
            free(new);
            new = temp;
            if (!new)
                return (free_path(path, new), 1);
        }
        i++;
    }
    if (texturing(path, new, flag, img))
        return (free_path(path, new), 1);
    return (free_path(path, new), 0);
}

void free_path(char **path, char *new)
{
    int i;

    i = 0;
    free(new);
    while (path[i])
    {
        free(path[i]);
        i++;
    }
    free(path);
}

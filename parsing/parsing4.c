#include "../cub3D.h"

int check_path_exists(char *path)
{
    int fd;
    fd = open(path, O_RDONLY);
    if (fd < 0)
        return (printf("Error: File not found %s.\n", path), 1);
    else
        close(fd);
    return (0);
}
void free_range(char **p, int i)
{
    while (p[i])
    {
        free(p[i]);
        i++;
    }
    free(p);
}

int parse_path(char **av)
{
    int i;
    char *path;
    
    i = 0;
    path = av[1] + 2;
    if (ft_strlen(path) == 4 && !ft_strncmp(path + ft_strlen(path) - 4, ".xpm", 4))
        return (printf("Error : add a name to your .xpm file.\n"), 1);
    while(path[i] != '.')
        i++;
    if (path[i] == '.' && (path[i + 1] != 'x' || path[i + 2] != 'p' || path[i + 3] != 'm'))
        return (printf("Error : Put the right extension (.xpm) !\n"), 1);
    else if (path[i] == '.' && path[i + 1] == 'x' && path[i + 2] == 'p' && path[i + 3] == 'm' && path[i + 4] != '\0')
        return (printf("Error : Put the right extension (.xpm) !\n"), 1);
    return (0);
}

int check_line(char **line, t_flag *flagg)
{
    (void)flagg;
    if (line[1] && line[1][0] != '\0' && line[1][0] != '\n')
    {
        if (parse_path(line) || check_path_exists(line[1]))
        {
            flagg->exit = 1;
            return (1);
        }
    } 
    else
    {
        // flagg->exit = 1;
        return (printf("Error: No path specified for %s\n", line[0]), 1);
    }
    return (0);
}

void print_error(char *message, int *flag, int *error)
{
    if (*flag == 0)
    {
        printf("Error: %s not defined.\n", message);
        *error = 1;
    }
}

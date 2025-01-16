/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing6.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 23:47:05 by marvin            #+#    #+#             */
/*   Updated: 2025/01/15 23:47:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	my_isspace(char c)
{
	return (c == ' ' || c == '\n' || c == '\t');
}

int	is_empty_line(char *line)
{
	while (*line)
	{
		if (!my_isspace(*line))
			return (0);
		line++;
	}
	return (1);
}

int	first_parse(int ac, char **av, int *fd, t_data *img)
{
	if (parse_input(ac, av, 0))
	{
		free(img->map);
		exit(1);
	}
	*fd = open(av[1], O_RDONLY);
	if (*fd < 0)
	{
		printf("Error : File not found.\n");
		free(img->map);
		exit(1);
	}
	return (0);
}

int check_too_many_args(char **path, t_flag *flag, const char *texture_name)
{
    if (path[1] && path[2] && path[2][0] != '\n')
    {
        printf("Error: Too many arguments for %s.\n", texture_name);
        flag->exit = 2;
        return 1;
    }
    return 0;
}

int handle_texture_direction(char **path, t_texture_data *data, t_flag *flag)
{
    if (!ft_strncmp(path[0], "N", ft_strlen("N")) || !ft_strncmp(path[0], "NO", ft_strlen("NO")))
    {
        if (check_too_many_args(path, flag, "North texture"))
            return 1;
        return handle_texture(data, 0, "North texture", &flag->n_check);
    }
    if (!ft_strncmp(path[0], "S", ft_strlen("S")) || !ft_strncmp(path[0], "SO", ft_strlen("SO")))
    {
        if (check_too_many_args(path, flag, "South texture"))
            return 1;
        return handle_texture(data, 1, "South texture", &flag->s_check);
    }
    if (!ft_strncmp(path[0], "W", ft_strlen("W")) || !ft_strncmp(path[0], "WE", ft_strlen("WE")))
    {
        if (check_too_many_args(path, flag, "West texture"))
            return 1;
        return handle_texture(data, 2, "West texture", &flag->w_check);
    }
    if (!ft_strncmp(path[0], "E", ft_strlen("E")) || !ft_strncmp(path[0], "EA", ft_strlen("EA")))
    {
        if (check_too_many_args(path, flag, "East texture"))
            return 1;
        return handle_texture(data, 3, "East texture", &flag->e_check);
    }
    return -1;
}

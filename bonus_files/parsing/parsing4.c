/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 17:35:16 by mlamrani          #+#    #+#             */
/*   Updated: 2025/01/16 16:59:01 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	check_path_exists(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		printf("Error\nFile not found %s.\n", path);
		return (1);
	}
	else
		close(fd);
	return (0);
}

void	free_range(char **p, int i)
{
	while (p[i])
	{
		free(p[i]);
		i++;
	}
	free(p);
}

int	parse_path(char **av)
{
	int		i;
	char	*path;

	i = 0;
	path = av[1];
	while (path[i])
		i++;
	if (i < 5 || ft_strncmp(path + i - 4, ".xpm", 4))
	{
		printf("Error\nPut the right extension (.xpm) !\n");
		return (1);
	}
	if (path[i - 1] == 'm' && path[i - 2] == 'p' && path[i - 3] == 'x' && path[i
			- 4] == '.' && path[i - 5] == '/')
	{
		printf("Error\nAdd a name to your .xpm file.\n");
		return (1);
	}
	return (0);
}

int	check_line(char **line, t_flag *flagg)
{
	if (line[1] && line[1][0] != '\0' && line[1][0] != '\n')
	{
		if (parse_path(line) || check_path_exists(line[1]))
		{
			flagg->exit = 2;
			return (1);
		}
	}
	else
	{
		flagg->exit = 2;
		return (printf("Error\nNo path specified for %s\n", line[0]), 1);
	}
	return (0);
}

void	print_error(char *message, int *flag, int *error)
{
	if (*flag == 0)
	{
		printf("Error\n%s not defined.\n", message);
		*error = 1;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 14:04:58 by mlamrani          #+#    #+#             */
/*   Updated: 2024/12/22 12:31:50 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	first_parse(int ac, char **av, int *fd)
{
	if (parse_input(ac, av))
		return (1);
	*fd = open(av[1], O_RDONLY);
	if (*fd < 0)
		return (printf("Error : File not found.\n"), 1);
	return (0);
}

int	main_parsing(char **av, int ac, t_data *img, char *line)
{
	int		fd;
	t_flag	flag;

	if (first_parse(ac, av, &fd))
		return (1);
	init_flag(&flag, img->map, img);
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] == '\n')
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (parse_line(line, &flag, 0, img))
			break ;
		free(line);
		line = get_next_line(fd);
	}
	if (flag.exit == 2 || check_texture(&flag))
		return (1);
	if (mini_map(line, img->map, fd) || my_map(img->map, img))
		return (1);
	return (close(fd), 0);
}

static char	*initialize_new(char *trimmed, char **path, char *new)
{
	char	*t;

	t = ft_strdup(trimmed);
	if (!t)
		return (free_path(path, new), NULL);
	new = ft_strjoin(t, " ");
	free(t);
	if (!new)
		return (free_path(path, new), NULL);
	return (new);
}

static char	*append_to_new(char *new, char *trimmed, char **path)
{
	char	*temp;

	temp = ft_strjoin(new, trimmed);
	free(new);
	if (!temp)
		return (free_path(path, new), NULL);
	return (temp);
}

int	parse_line(char *line, t_flag *flag, int i, t_data *img)
{
	char	**path;
	char	*new;
	char	*trimmed;

	new = NULL;
	path = ft_split(line, ' ');
	while (path[i])
	{
		trimmed = ft_strtrim(path[i], " ");
		if (!trimmed)
			return (free_path(path, new), 1);
		free(path[i]);
		path[i] = trimmed;
		if (new == NULL)
			new = initialize_new(trimmed, path, new);
		else
			new = append_to_new(new, trimmed, path);
		if (!new)
			return (1);
		i++;
	}
	path[0] = ft_strtrim(path[0], "\n");
	if (texturing(path, new, flag, img))
		return (free_path(path, new), 1);
	return (free_path(path, new), 0);
}

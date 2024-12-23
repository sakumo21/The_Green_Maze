/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 14:04:58 by mlamrani          #+#    #+#             */
/*   Updated: 2024/12/23 19:00:40 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	first_parse(int ac, char **av, int *fd)
{
	if (parse_input(ac, av, 0))
		return (1);
	*fd = open(av[1], O_RDONLY);
	if (*fd < 0)
	{
		printf("Error : File not found.\n");
		exit(1);
	}
	return (0);
}


void par_line(char *line)
{
	int i;

	i = 0;
	while (line[i] == ' ')
	{
		
		i++;
	}
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
		par_line(line);
		if (parse_line(line, &flag, 0, img))
			break ;
		free(line);
		line = get_next_line(fd);
	}
	if (flag.exit == 2 || check_texture(&flag))
		return (free(line), free_textures_path(img), 1);
	if (mini_map(line, img->map, fd) || my_map(img->map, img))
		return (free_textures_path(img), 1);
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
	if (!temp)
		return (free_path(path, new), NULL);
	free(new);
	return (temp);
}

int	parse_line(char *line, t_flag *flag, int i, t_data *img)
{
	char	*trimmed;
	char	*new;

	new = NULL;
	img->path = ft_split(line, ' ');
	while (img->path[i])
	{
		trimmed = ft_strtrim(img->path[i], " ");
		if (!trimmed)
			return (free_path(img->path, new), 1);
		free(img->path[i]);
		img->path[i++] = trimmed;
		if (new == NULL)
			new = initialize_new(trimmed, img->path, new);
		else
			new = append_to_new(new, trimmed, img->path);
	}
	trimmed = ft_strtrim(img->path[0], "\n");
	free(img->path[0]);
	img->path[0] = trimmed;
	if (texturing(img->path, new, flag, img))
		return (free_path(img->path, new), 1);
	return (free_path(img->path, new), 0);
}

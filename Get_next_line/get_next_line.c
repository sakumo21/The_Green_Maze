/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 17:11:10 by ziel-hac          #+#    #+#             */
/*   Updated: 2024/12/22 09:32:50 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_line(char **lines, int nl_position)
{
	char	*tmp;
	char	*rets;

	if (nl_position <= 0)
	{
		if (**lines == '\0')
		{
			free(*lines);
			*lines = NULL;
			return (NULL);
		}
		rets = ft_strdupg(*lines);
		free(*lines);
		*lines = NULL;
		return (rets);
	}
	tmp = ft_substrg(*lines, nl_position, BUFFER_SIZE);
	rets = *lines;
	rets[nl_position] = 0;
	*lines = tmp;
	return (rets);
}

char	*read_line(char *buffer, char **lines, int fd)
{
	char		*new_line_check;
	ssize_t		read_bytes;
	char		*tmp2;

	tmp2 = NULL;
	new_line_check = ft_strchrg(*lines, '\n');
	while (new_line_check == NULL)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
			return (free(*lines), *lines = NULL, NULL);
		if (read_bytes <= 0)
			return (get_line(lines, read_bytes));
		buffer[read_bytes] = 0;
		tmp2 = ft_strjoing(*lines, buffer);
		free(*lines);
		*lines = NULL;
		*lines = tmp2;
		new_line_check = ft_strchrg(*lines, '\n');
	}
	return (get_line(lines, (new_line_check - *lines) + 1));
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*lines;
	char		*rets;

	if (fd < -1 || BUFFER_SIZE <= 0)
		return (NULL);
	if (fd == -1)
	{
		free(lines);
		lines = NULL;
		return (NULL);
	}
	if (!lines)
		lines = ft_strdupg("");
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (0);
	rets = read_line(buffer, &lines, fd);
	free(buffer);
	buffer = NULL;
	return (rets);
}

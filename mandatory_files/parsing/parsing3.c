/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 17:32:59 by mlamrani          #+#    #+#             */
/*   Updated: 2024/12/25 14:05:30 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	only_num(char *s)
{
	int	i;
	int	num;

	i = 0;
	if (s[i] == '+' || s[i] == '-')
	{
		return (printf("Error: No sign allowed!\n"), 1);
	}
	num = ft_atoi(&s[i]);
	if (num == -1)
	{
		return (printf("Error : (%s), Only digits!\n", s), 1);
	}
	return (0);
}

int	validate_values(char **p)
{
	int	i;

	i = 0;
	while (i <= 2)
	{
		if (only_num(p[i]))
			return (free_range(p, 0), 1);
		i++;
	}
	return (0);
}

int	check_value_range(char **p)
{
	if ((ft_atoi(p[0]) < 0 || ft_atoi(p[0]) > 255)
		|| (ft_atoi(p[1]) < 0 || ft_atoi(p[1]) > 255)
		|| (ft_atoi(p[2]) < 0 || ft_atoi(p[2]) > 255))
	{
		free_range(p, 0);
		printf("Error : RGB range is between 0 and 255\n");
		return (1);
	}
	return (0);
}

int	check_extra_values(char **p)
{
	if (p[3] || p[2][0] == '\n' || p[2][0] == '\0')
	{
		free_range(p, 0);
		printf("Error : Expected 3 RGB values [..., ..., ...].\n");
		return (1);
	}
	return (0);
}

char	*ft_strjoin_three(char *s1, char *s2, char *s3)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(s1, s2);
	if (!tmp)
		return (NULL);
	result = ft_strjoin(tmp, s3);
	free(tmp);
	return (result);
}

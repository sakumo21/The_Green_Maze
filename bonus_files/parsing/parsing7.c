/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing7.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 11:01:48 by mlamrani          #+#    #+#             */
/*   Updated: 2025/01/16 11:02:06 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	my_map(t_map *map, t_data *img)
{
	int	max_y;

	max_y = 0;
	if (parsing_map(map->map))
		return (1);
	while (map->map[max_y] != NULL)
		max_y++;
	if (check_map_enclosure(map, 0, 0, "10DNEWS"))
		return (1);
	if (find_starting_point(map->map, img, 0, 0))
		return (1);
	return (0);
}

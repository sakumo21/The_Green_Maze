/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing7.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 01:18:03 by marvin            #+#    #+#             */
/*   Updated: 2025/01/16 01:18:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int handle_floor_or_ceiling(char **path, char *new, t_flag *flag, t_data *img)
{
    if (!ft_strncmp(path[0], "F", 1))
    {
        int result = check_set_color(&flag->f_check, "Floor color", new, img);
        if (result == 2)
            flag->exit = 2;
        return result ? 1 : 0;
    }
    if (!ft_strncmp(path[0], "C", 1))
    {
        int result = check_set_color(&flag->c_check, "Ceiling color", new, img);
        if (result == 2)
            flag->exit = 2;
        return result ? 1 : 0;
    }
    return -1;
}

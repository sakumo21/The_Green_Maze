/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texturing2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 16:08:25 by mlamrani          #+#    #+#             */
/*   Updated: 2025/01/27 09:35:53 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	draw_wall_slice(t_data *img, int x, t_texture_info *tex_info)
{
	int				y;
	int				tex_y;
	unsigned int	color;

	y = img->ray.drawstart;
	while (y < img->ray.drawend)
	{
		tex_y = (int)tex_info->tex_pos & (tex_info->texture_height - 1);
		tex_info->tex_pos += tex_info->step;
		color = *(unsigned int *)(tex_info->texture_addr + (tex_y
					* tex_info->texture_length + tex_info->tex_x
					* (tex_info->texture_bpp / 8)));
		draw_pixel(img, x, y, color);
		y++;
	}
}

static t_texture_info	get_texture_info(t_data *img, double wallX, double step,
		double tex_pos)
{
	t_texture_info	t_info;

	t_info.tex_x = (int)(wallX * img->textures[img->map->texture_index].width);
	if ((img->ray.side == 0 && img->ray.rayx < 0) || (img->ray.side == 1
			&& img->ray.rayy > 0))
		t_info.tex_x = img->textures[img->map->texture_index].width
			- t_info.tex_x - 1;
	t_info.step = step;
	t_info.tex_pos = tex_pos;
	t_info.texture_height = img->textures[img->map->texture_index].height;
	t_info.texture_width = img->textures[img->map->texture_index].width;
	t_info.texture_addr = img->textures[img->map->texture_index].addr;
	t_info.texture_length = img->textures[img->map->texture_index].line_length;
	t_info.texture_bpp = img->textures[img->map->texture_index].bits_per_pixel;
	return (t_info);
}

void	draw_textured_wall(t_data *img, int x)
{
	t_texture_info	tex_info;
	double			wall_x;
	double			step;
	double			tex_pos;

	img->map->texture_index = get_texture_index(img);
	if (img->ray.side == 0)
		wall_x = img->ray.posy + img->ray.perpwalldist * img->ray.rayy;
	else
		wall_x = img->ray.posx + img->ray.perpwalldist * img->ray.rayx;
	wall_x -= (int)wall_x;
	if (wall_x < 0)
		wall_x += 1.0;
	step = 1.0 * img->textures[img->map->texture_index].height
		/ img->ray.wallheight;
	tex_pos = (img->ray.drawstart - HEIGHT / 2 + img->ray.wallheight / 2)
		* step;
	tex_info = get_texture_info(img, wall_x, step, tex_pos);
	draw_wall_slice(img, x, &tex_info);
}

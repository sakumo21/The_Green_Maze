/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texturing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:17:37 by ziel-hac          #+#    #+#             */
/*   Updated: 2024/12/21 16:11:34 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	punch_frames(t_data *img)
{
	rendering_image(img, 0, "./puunch3.xpm");
	usleep(10000);
	rendering_image(img, 0, "./puunch3.xpm");
	usleep(40000);
	rendering_image(img, 0, "./puunch2.xpm");
	usleep(40000);
	rendering_image(img, 0, "./puunch.xpm");
}

void	pistol_frames(t_data *img)
{
	rendering_image(img, 0, "./pistool2.xpm");
	usleep(40000);
	rendering_image(img, 0, "./pistool3.xpm");
	usleep(40000);
	rendering_image(img, 0, "./pistool4.xpm");
	usleep(40000);
	rendering_image(img, 0, "./pistool5.xpm");
	usleep(40000);
	rendering_image(img, 0, "./pistool2.xpm");
	usleep(40000);
	rendering_image(img, 0, "./pistool.xpm");
}

void	check_text(t_data *img, int i)
{
	while (i < 5)
	{
		if (!img->textures[i].img)
		{
			printf("Error : Loading texture %d\n", i);
			exit(1);
		}
		img->textures[i].addr = mlx_get_data_addr(img->textures[i].img,
				&img->textures[i].bits_per_pixel, &img->textures[i].line_length,
				&img->textures[i].endian);
		i++;
	}
}

void	load_textures(t_data *img, int i)
{	
	img->textures[4].path = "textures/alien.xpm";
	img->textures[0].img = mlx_xpm_file_to_image(img->mlx,
			img->textures[0].path, &img->textures[0].width,
			&img->textures[0].height);
	img->textures[1].img = mlx_xpm_file_to_image(img->mlx,
			img->textures[1].path, &img->textures[1].width,
			&img->textures[1].height);
	img->textures[2].img = mlx_xpm_file_to_image(img->mlx,
			img->textures[2].path, &img->textures[2].width,
			&img->textures[2].height);
	img->textures[3].img = mlx_xpm_file_to_image(img->mlx,
			img->textures[3].path, &img->textures[3].width,
			&img->textures[3].height);
	img->textures[4].img = mlx_xpm_file_to_image(img->mlx,
			img->textures[4].path, &img->textures[4].width,
			&img->textures[4].height);
	check_text(img, i);
}

void	draw_pixel(t_data *img, int x, int y, unsigned int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 19:38:41 by marvin            #+#    #+#             */
/*   Updated: 2024/10/30 19:38:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <math.h>
#include "./minilibx_linux/mlx.h"
#include <X11/X.h>
#include <stdlib.h>
#include <stdio.h>

#define WIDTH 800
#define HEIGHT 800
#define mapWidth 24
#define mapHeight 24
#define EPSILON 1e-6

typedef struct s_ray
{
	int		drawend;
	int		drawstart;
	double 	cameraX;
	double	rayX;
	double	rayY;
	double	DsideX;
	double	DsideY;
	double	SsideX;
	double	SsideY;
	int		stepX;
	int		stepY;
	double	posx;
	double	posy;
  	double	dirX;
	double	dirY;
  	double	planeX;
	double	planeY;
	int		side;
	double perpwalldist;
}				t_ray;

typedef struct	s_data 
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	t_ray	ray;
}				t_data;

void	rendering_image(t_data *img, int i, int color);
void	event_keys(t_data *img);

#endif
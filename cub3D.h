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

#include "./minilibx-linux/mlx.h"
#include <math.h>
#include <X11/X.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include "Libft/libft.h"
#include "Get_next_line/get_next_line.h"

#define MINIMAP_SCALE 0.2  // Scale factor for minimap
#define MINIMAP_SIZE 150  // Size of the minimap in pixels
#define MINIMAP_PLAYER_SIZE 5  // Size of the player marker

#define WIDTH 1920
#define HEIGHT 1080
#define mapWidth 24
#define mapHeight 24
#define EPSILON 1e-6


typedef struct s_texture
{
    int N_check;
    int S_check;
    int W_check;
    int E_check;
    int F_check;
    int C_check;
	int exit;
}               t_texture;

typedef struct s_map
{
    char **map;
	int height;
	int width;
	char player;
	int player_x;
	int player_y;
}               t_map;


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
	int		color;
	double	perpwalldist;
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
	t_map	*map;
}				t_data;

void	rendering_image(t_data *img, int i);
void	event_keys(t_data *img);
int main_parsing(char **av, int ac, t_map *map, t_data *img);
int check_texture(t_texture *flag);
void print_error(char *message, int *flag, int *error);
int parse_line(char *line, t_texture *flag, int i);
void free_path(char **path, char *new);
int texturing(char **path, char *new, t_texture *flag);
int check_set_color(int *flag, char *msg, char *new);
int check_and_set(char **path, int *flag, char *msg);
void init_flag(t_texture *flag, t_map *map);
int parse_input(int ac, char **av);
int check_range(char *line);
int check_path_exists(char *path);
void free_range(char **p, int i);
int check_line(char **line);
int mini_map(char *line, t_map *map, int fd, int i);
int my_map(t_map *map, t_data *img);
int check_map_enclosure(char **map, int i, int j);
void flood_fill(t_map *map, int x, int y, int max_x, int max_y);
int check_filled_map(char **map);
int find_starting_point(char **map, t_data *img, int i);
void flood_fill2(t_map *map, int x, int y, int max_x, int max_y);
int parsing_map(char **map);


//minimap
void draw_minimap(t_data *img);
void my_put(t_data *data, int x, int y, int color);
int get_map_width(t_map *map, int i);

#endif
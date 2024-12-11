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
#include <sys/time.h>




#define WIDTH 2560
#define HEIGHT 1440
#define mapWidth 24
#define mapHeight 24
#define EPSILON 1e-6
#define x_offset 10
#define y_offset 10


typedef struct s_texture
{
    void    *img;           // Image pointer for the texture
    char    *addr;          // Pixel data of the texture
    int     width;          // Texture width
    int     height;         // Texture height
    int     bits_per_pixel; // Bits per pixel
    int     line_length;    // Line size in bytes
    int     endian;         // Endian format
}               t_texture;

typedef struct s_flag
{
    int N_check;
    int S_check;
    int W_check;
    int E_check;
    int F_check;
    int C_check;
	int exit;
}               t_flag;

typedef struct s_map
{
    char **map;
	int height;
	int width;
	char player;
	int player_x;
	int player_y;
	int minimap_width;
	int minimap_height;
	int tile_size;
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
	int move_forward;    // W key flag
    int move_backward;   // S key flag
    int move_left;       // A key flag
    int move_right;      // D key flag
    int rotate_left;     // Left arrow key flag
    int rotate_right;    // Right arrow key flag
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
	char *floor;
	char *ceiling;
	t_ray	ray;
	t_map	*map;
	t_texture textures[4];
}				t_data;



void	rendering_image(t_data *img, int i);
void	event_keys(t_data *img);
int main_parsing(char **av, int ac, t_map *map, t_data *img);
int check_texture(t_flag *flag);
void print_error(char *message, int *flag, int *error);
int parse_line(char *line, t_flag *flag, int i, t_data *img);
void free_path(char **path, char *new);
int texturing(char **path, char *new, t_flag *flag, t_data *img);
int check_set_color(int *flag, char *msg, char *new, t_data *img);
int check_and_set(char **path, int *flag, char *msg, t_flag *flagg);
void init_flag(t_flag *flag, t_map *map, t_data *img);
int parse_input(int ac, char **av);
int check_range(char *line, t_data *img);
int check_path_exists(char *path);
void free_range(char **p, int i);
int check_line(char **line, t_flag *flagg);
int mini_map(char *line, t_map *map, int fd, int i);
int my_map(t_map *map, t_data *img);
int check_map_enclosure(char **map, int i, int j);
void flood_fill(t_map *map, int x, int y, int max_x, int max_y);
int check_filled_map(char **map);
int find_starting_point(char **map, t_data *img, int i);
void flood_fill2(t_map *map, int x, int y, int max_x, int max_y);
int parsing_map(char **map);
void	initialize_data(t_data *img);


//minimap
void draw_minimap(t_data *img);
void my_put(t_data *data, int x, int y, int color);
int get_map_width(t_map *map, int i);

#endif
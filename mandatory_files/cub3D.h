/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamrani <mlamrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 13:39:36 by mlamrani          #+#    #+#             */
/*   Updated: 2024/12/25 11:43:27 by mlamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx.h"
# include "../Get_next_line/get_next_line.h"
# include "../Libft/libft.h"
# include <X11/X.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

# define WALL '1'
# define EMPTY '0'
# define SPACE ' '


# define WIDTH 800
# define HEIGHT 800

# define MAPWIDTH 24
# define MAPHEIGHT 24
# define EPSILON 1e-6
# define X_OFFSET 10
# define Y_OFFSET 10
# define MOVESPEED 0.02
# define ROTSPEED 0.05

typedef struct s_keys
{
	int			w;
	int			s;
	int			a;
	int			d;
	int			left;
	int			right;
	int			space;
	int			old_x;
}				t_keys;

typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	char	*path;
}				t_texture;

typedef struct s_texture_info
{
	int			tex_x;
	double		tex_pos;
	double		step;
	int			texture_height;
	int			texture_width;
	char		*texture_addr;
	int			texture_length;
	int			texture_bpp;
}				t_texture_info;

typedef struct s_flag
{
	int			n_check;
	int			s_check;
	int			w_check;
	int			e_check;
	int			f_check;
	int			c_check;
	int			exit;
	int 		is_map_started;
}				t_flag;

typedef struct s_map
{
	char		**map;
	int			height;
	int			width;
	char		player;
	int			player_x;
	int			player_y;
	int			minimap_width;
	int			minimap_height;
	int			tile_size;
	int			texture_index;
	char		*exit;
}				t_map;

typedef struct s_circle
{
	int			cx;
	int			cy;
	int			radius;
	int			color;
}				t_circle;

typedef struct s_line
{
	int			x1;
	int			y1;
	int			x2;
	int			y2;
	int			color;
	float		x;
	float		y;
}				t_line;

typedef struct s_ray
{
	int			drawend;
	int			drawstart;
	int			wallheight;
	double		movespeed;
	double		camerax;
	double		rayx;
	double		rayy;
	double		dsidex;
	double		dsidey;
	double		ssidex;
	double		ssidey;
	int			stepx;
	int			stepy;
	int			mapx;
	int			mapy;
	double		posx;
	double		posy;
	double		dirx;
	double		diry;
	double		planex;
	double		planey;
	int			side;
	int			color;
	double		perpwalldist;
	int			move_forward;
	int			move_backward;
	int			move_left;
	int			move_right;
	int			rotate_left;
	int			rotate_right;
}				t_ray;

typedef struct s_sprite
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_sprite;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			weapon;
	char		*floor;
	char		*ceiling;
	int			player_x;
	int			player_y;
	char		**path;
	char 		*new;
	t_ray		ray;
	t_map		*map;
	t_texture	textures[4];
	t_keys		keys;
	t_sprite	sprite;
}				t_data;

typedef struct s_texture_data
{
	char		**path;
	t_flag		*flag;
	t_data		*img;
	int			index;
	char		*texture_name;
	int			*flag_check;
}				t_texture_data;

int				free_img(t_data *img);
int				parsing_map(char **map);
int				validate_values(char **p);
int				check_value_range(char **p);
int				check_texture(t_flag *flag);
int				handle_empty_map(char *str);
int				check_texture(t_flag *flag);
int				handle_movement(t_data *img);
int				check_extra_values(char **p);
int				check_filled_map(char **map);
int				check_path_exists(char *path);
int				handle_empty_lines(char *str);
int				get_texture_index(t_data *img);
int				parse_input(int ac, char **av, int i);
int				my_map(t_map *map, t_data *img);
int				check_line(char **line, t_flag *flagg);
int				mini_map(char *line, t_map *map, int fd);
int				check_range(char *line, t_data *img, char *new);
int				main_parsing(char **av, int ac, t_data *img, char *line);
int				parse_line(char *line, t_flag *flag, int i, t_data *img);
int				texturing(char **path, char *new, t_flag *flag, t_data *img);
int				check_set_color(int *flag, char *msg, char *new, t_data *img);
int				find_starting_point(char **map, t_data *img, int i, int found);
int				check_and_set(char **path, int *flag, char *msg, t_flag *flagg);
int				check_map_enclosure(t_map *map, int x, int y, char	*valid_neighbors);
void			free_d(char **args);
void			free_end(t_data *img);
void			init_cube(t_data *img);
void			punch_frames(t_data *img);
void			free_textures(t_data *img);
void			pistol_frames(t_data *img);
void			free_resources(t_data *img);
void			free_textures_path(t_data *img);
void			load_textures(t_data *img, int i);
void			draw_textured_wall(t_data *img, int x);
void			move_up(t_data *img, double movespeed);
void			move_down(t_data *img, double movespeed);
void			move_left(t_data *img, double movespeed);
void			move_right(t_data *img, double movespeed);
void			rotate_view(t_data *img, double rotSpeed);
void			initialize_values(t_data *img, double a[4]);
void			rendering_image(t_data *img, int i);
void			print_error(char *message, int *flag, int *error);
void			event_keys(t_data *img);
void			free_path(char **path, char *new);
void			init_flag(t_flag *flag, t_map *map, t_data *img);
void			free_range(char **p, int i);
void			put_to_image(t_data *img, char *str);
void			calculate_ray(t_data *img, int i);
void			calculate_sside(t_data *img);
void			calculate_vector(t_data *img, int hit);
void			calculate_wall_height(t_data *img);
void			coloring_the_image(t_data *img, int i);
void			my_mlx_pixel_put_image(t_data *data, int x, int y, int color);
void			my_mlx_pixel_put(t_data *data, int x, int color);
void			my_mlx_pixel_put_sprite(t_data *data, int height, int width);
char			*read_map_lines(char *line, int fd);
char			*ft_strjoin_three(char *s1, char *s2, char *s3);
unsigned int	rgb_to_hex(int r, int g, int b);
unsigned int	convert_ceiling_to_hex(char *ceiling);
int				is_empty_line(char *line);
void			draw_pixel(t_data *img, int x, int y, unsigned int color);

#endif
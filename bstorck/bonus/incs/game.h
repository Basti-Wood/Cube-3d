/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstorck <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 15:22:15 by bstorck           #+#    #+#             */
/*   Updated: 2025/12/04 00:13:21 by bstorck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# define PI 3.14159265359

# include "../libs/mlx/mlx.h"
# include "../libs/libft/libft.h"
# include "../libs/libft/get_next_line.h"
# include <stdio.h>
# include <stdbool.h>
# include <math.h>
# include <sys/time.h>
# include <fcntl.h>

typedef enum e_colors
{
	HERO_CLR = 0X00FFFF,
	//HERO_CLR = 0x00FF7F,
	WALKER_CLR = 0xC8C800,
	TILE_CLR = 0x007777,
	//TILE_CLR = 0x007FAA,
	WHITE = 0xFFFFFF,
	BEAM_CLR = 0xC8C800
}	t_colors;

typedef enum e_dimensions
{
	WIN_WIDTH = 1280,
	WIN_HEIGHT = 800,
	NUM_TEXTURES = 6,
	NUM_COLOR_SYMBOLS = 95,
	TEXEL_SIZE = 16,
	TILE_SIZE = 32,
	BLOCK_SIZE = 16,
	MAX_NODE_SIZE = WIN_HEIGHT * 33/100,
	NUM_CARDINAL_DIRECTIONS = 4
}	t_dimensions;

typedef enum e_key_codes
{
	WIN_X_BTN = 17,
	KEY_ESC = 65307,
	// KEY_TAB = 65289,
	KEY_SHIFT_L = 65505,
	KEY_SHIFT_R = 65506,
	// KEY_Q = 113,
	KEY_W = 119,
	KEY_E = 101,
	// KEY_R = 114,
	// KEY_T = 116,
	KEY_A = 97,
	KEY_S = 115,
	KEY_D = 100,
	KEY_F = 102,
	// KEY_G = 103,
	// KEY_X = 120,
	// KEY_C = 99,
	// KEY_V = 118,
	// KEY_B = 98,
	// KEY_Y = 121,
	// KEY_U = 117,
	// KEY_I = 105,
	// KEY_O = 111,
	// KEY_P = 112,
	// KEY_H = 104,
	KEY_J = 106,
	// KEY_K = 107,
	KEY_L = 108,
	// KEY_N = 110,
	// KEY_M = 109,
	// KEY_COMMA = 44,
	// KEY_POINT = 46,
	// KEY_UP = 65362,
	KEY_LEFT = 65361,
	// KEY_DOWN = 65364,
	KEY_RIGHT = 65363,
	KEY_SPACE = 32,
	// MOUSE_WHEEL_UP = 4,
	// MOUSE_WHEEL_DOWN = 5
}	t_key_codes;

typedef struct s_square
{
	int			x;
	int			y;
}	t_square;

typedef struct s_vector
{
	double		x;
	double		y;
}	t_vector;

typedef struct s_line
{
	double	start;
	double	end;
	double	height;
}	t_line;

typedef struct s_floor
{
	t_vector	ray_dir_start;
	t_vector	ray_dir_end;
	int			p;
	double		z_pos;
	double		dist_row;
	t_vector	step;
	t_vector	pos;
	t_square	tex;
}	t_floor;

typedef struct s_texture
{
	int	width;
	int	height;
	int	color_count;
	int	color_table[NUM_COLOR_SYMBOLS];
	int	*pixel_map;
}	t_texture;

typedef struct s_ray
{
	t_vector	dir;
	t_square	map;
	t_square	step;
	t_vector	side_dist;
	t_vector	delta_dist;
	double		perp_dist;
	double_t	inv_perp_dist;
	bool		side;
}	t_ray;

typedef struct s_hero
{
	bool		mini;
	t_vector	pos;
	t_vector	dir;
	t_vector	plane;
	t_vector	probe;
	double		scan_x;
	double		fov;
	t_ray		ray;
	bool		move_forward;
	bool		move_backward;
	bool		move_port;
	bool		move_starboard;
	double		move_speed;

	bool		turn_sinistral;
	bool		turn_dextral;
	double		turn_speed;

	int			axes_of_travel;
	int			collision_radius;
}	t_hero;

typedef struct s_walker
{
	t_square	pos;
	t_square	dir;
	t_square	start;
	t_square	first;
	t_square	last;
	t_square	dir_set[NUM_CARDINAL_DIRECTIONS];
	int			prev;
}	t_walker;

typedef struct s_map
{
	int			*grid;
	int			width;
	int			height;
	int			tile_size;
	t_square	node_size;
	// int			max_node_size;
}	t_map;

typedef struct s_img
{
	void		*ptr;
	char		*data;
	int			bpp;
	int			size_line;
	int			endian;
	int			width;
	int			height;
	double		aspect_ratio;
}	t_img;

typedef struct s_game
{
	bool		skip_intro;
	void		*mlx;
	void		*win;
	t_img		img;
	double		half_screen;
	t_map		map;
	t_texture	texture[NUM_TEXTURES];
	int			present_num;
	t_walker	walker;
	t_hero		hero;
	t_hero		mini_hero;
	t_floor		floor;
}	t_game;

t_texture	parse_xpm_file(const char *filename, t_game *game);
int			get_fd(const char *filename);
void		free_tokens(void **token);
int			parse_color_table_line(char *line, t_texture *texture);
int			parse_hex_color(const char *line);
int			init_xpm_pixel_map(t_texture *texture);
int			parse_pixel_map_line(char *line, int y, t_texture *tx);
char		*skip_lines(int xpm_fd);
void		init_presenter_window(t_game *g);
int			presenter_loop(t_game *game);
int			init_map(t_game *game);
void		init_walker_window(t_game *g);
t_walker	init_walker(t_game *game);
int			get_walker_start(t_game *game);
int			move_walker(t_game *game);
t_hero		init_hero(bool mini, t_game *g);
int			walker_loop(t_game *game);
void		draw_map(bool intro, t_game *game);
t_square	get_offset(bool intro, t_game *game);
void		draw_walker(int x, int y, t_game *game);
void		draw_filled_square(t_square s, int size, int color, t_game *game);
void		ft_usleep(int usec);
void		init_game_window(t_game *g);
void		set_node_size(t_game *game);
int			key_press(int keycode, t_game *game);
int			key_release(int keycode, t_game *game);
int			hero_sonar(t_hero *hero, t_map *map);
int			game_loop(t_game *game);
void		hero_action(t_hero *hero, t_map *map);
bool		collision(int x, int y, t_map *map);
void		draw_floor_and_ceiling(t_game *game);
void		draw_hero(bool intro, t_vector pos, int size, t_game *game);
void		draw_radar(t_game *game);
void		init_ray(int i, t_hero *hero);
void		dda(t_game *game);
void		draw_walls(t_game *game);
void		draw_line_loop(int i, double d, t_line line, t_game *game);
void		put_pixel(int x, int y, int color, t_game *game);
void		clear_image(t_game *game);
void		free_game_resources(t_game *game);
void		free_texture(t_texture *texture);
int			close_game(t_game *game);
#endif

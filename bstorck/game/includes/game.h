/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstorck <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 15:22:15 by bstorck           #+#    #+#             */
/*   Updated: 2025/11/21 15:22:29 by bstorck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

// # define BLOCK 64
# define PI 3.14159265359

# include "./mlx/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
// # include <cstdint>
# include <limits.h>
# include <math.h>
# include <sys/time.h>

// # define	STATIC_MAP

typedef enum e_dimensions
{
	SCRN_WIDTH = 1920,
	SCRN_HEIGHT = 960,
	FRM_WIDTH = SCRN_WIDTH / 2,
	BLOCK_SIZE = 32
}	t_dimensions;

typedef enum e_key_codes
{
	WIN_X_BTN = 17,
	KEY_ESC = 65307,
	// KEY_Q = 113,
	KEY_W = 119,
	KEY_E = 101,
	// KEY_R = 114,
	KEY_T = 116,
	KEY_A = 97,
	KEY_S = 115,
	KEY_D = 100,
	KEY_F = 102,
	KEY_G = 103,
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

typedef struct s_ray
{
	t_vector	dir;
	t_square	map;
	t_square	step;

	t_vector	side_dist;
	t_vector	delta_dist;

	double		perp_dist_wall;
	bool		side;
}	t_ray;

// typedef struct s_wind_rose
// {
// 	t_square	wind_rose[4];
// }	t_wind_rose;

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

	// t_wind_rose	*c;
	bool		move_forward;
	bool		move_backward;
	bool		move_port;
	bool		move_starboard;
	// double		probe_speed;
	double		move_speed;

	bool		turn_sinistral;
	bool		turn_dextral;
	double		turn_speed;

	int			axes_of_travel;
	int			collision_radius;
}	t_hero;

// typedef struct s_settings
// {
// 	int			speed_factor;
// }	t_settings;

// typedef struct s_window
// {
// 	void		*mlx;
// 	void		*win;
// 	void		*img;
// 	char		*data;
// 	int			bpp;
// 	int			size_line;
// 	int			endian;
// }	t_window;

typedef struct s_walker
{
	t_square	pos;
	t_square	dir;
	t_square	start;
	t_square	first;
	t_square	last;
	t_square	wind_rose[4];
	// t_wind_rose	*c;
	// t_square	prev;
	int			prev;
}	t_walker;

typedef struct s_game
{
	int			level_of_speed;

	bool		skip_intro;
	// bool		intro_concluded;
	void		*mlx;
	void		*win;
	void		*img;
	char		*data;
	int			bpp;
	int			size_line;
	int			endian;

	int			**map;
	int			map_width;
	int			map_height;
	// int			block_size;
	// t_wind_rose	c;
	// t_ray		ray;
	// t_settings	settings;
	t_walker	walker;
	t_hero		hero;
	t_hero		mini_hero;

	// t_window	w;
	// double		time;
	// double		prev_time;
}	t_game;

// int			ft_strcmp(char const *s1, char const *s2);
void		init_game(t_game *g);
void		init_intro_window(t_game *g);
void		init_game_window(t_game *g);
int			intro_loop(t_game *game);
t_walker	init_walker(t_game *game);
int			get_start(t_game *game);
int			get_direction(t_game *game);
// void		check_wall_integrity(t_game *game);

int			**init_map(int map_width, int map_height);
t_hero		init_hero(bool mini, t_game *game);
// t_hero	init_mini_hero(t_hero *hero);
// t_ray	init_ray(t_hero *hero);
int			key_press(int keycode, t_game *game);
int			key_release(int keycode, t_game *game);
void		move_hero(int **map, t_hero *hero);
void		go_forward(t_hero *h, int **map);
void		go_backward(t_hero *h, int **map);
void		go_port(t_hero *h, int **map);
void		go_starboard(t_hero *h, int **map);
void		turn_hero(double dir_x, double plane_x, t_hero *h);
int			sonar(t_hero *hero, int **map);
int			game_loop(t_game *game);
// time_t		get_current_time(void);
void		ft_usleep(int usec);
bool		collision(int x, int y, int **map);
void		put_pixel(int x, int y, int color, t_game *game);
void		draw_blip(int x, int y, t_game *game);
void		draw_empty_square(t_square s, int size, int color, t_game *game);
void		draw_filled_square(t_square s, int size, int color, t_game *game);
void		draw_floor_and_ceiling(t_game *game);
void		draw_map(t_game *game);
void		draw_hero(double x, double y, int size, t_game *game);
void		draw_radar(t_game *game);
void		draw_walls(t_game *game);
void		cast_ray(t_hero *hero);
void		dda(t_game *game);

void		go_slower(t_game *game);
void		go_faster(t_game *game);

void		clear_image(t_game *game);
int			close_game(t_game *game);
#endif

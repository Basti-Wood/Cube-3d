#ifndef GAME_H
# define GAME_H

// # define BLOCK 64
# define PI 3.14159265359

#include "./mlx/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// #include <cstdint>
#include <limits.h>
#include <math.h>
#include <sys/time.h>

#define	STATIC_MAP


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

typedef struct s_ray
{
	bool		side;
	t_vector	dir;
	t_square	map;
	t_square	step;

	t_vector	side_dist;
	t_vector	delta_dist;

	double		perp_dist_wall;
}	t_ray;;

typedef struct s_player
{
	bool		mini;

	t_vector	pos;
	t_vector	dir;
	t_vector	plane;
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
} 	t_player;

typedef struct s_walker
{
	t_square	pos;
	t_square	start;
	t_square	wind_rose[4];
	t_square	first;
	t_square	last;
	// t_square	prev;
	int			prev;
}	t_walker;

typedef struct s_game
{
	bool		skip_intro;

	void		*mlx;
	void		*win;
	void		*img;

	char		*data;
	int			bpp;
	int			size_line;
	int			endian;

	int			**map;
	int			map_height;
	int			map_width;
	// int			block_size;

	// t_ray		ray;
	t_player	player;
	t_player	mini_player;

	// double		time;
	// double		prev_time;
}	t_game;

int			ft_strcmp(char const *s1, char const *s2);

int			**init_map(int map_width, int map_height);
t_player	init_player(bool mini);
// t_player	init_mini_player(t_player *player);
// t_ray	init_ray(t_player *player);
int			i_walk_the_line(t_game *game);
int			key_press(int keycode, t_game *game);
int			key_release(int keycode, t_game *game);
void		move_player(int **map, t_player *player);

// time_t		get_current_time(void);
void		ft_usleep(int usec);
bool		collision(int x, int y, int **map);
void		put_pixel(int x, int y, int color, t_game *game);
void		draw_blip(int x, int y, t_game *game);
void		draw_empty_square(t_square square, int size, int color, t_game *game);
void		draw_filled_square(t_square square, int size, int color, t_game *game);
void		draw_floor_and_ceiling(t_game *game);
void		draw_map(t_game *game);
// void		draw_player(t_game *game);
void		draw_hero(double x, double y, int size, t_game *game);
void		draw_radar(t_game *game);
void		draw_walls(t_game *game);
void		cast_ray(t_player *player);
void		dda(t_game *game);

void		clear_image(t_game *game);
void		throw_error(int num_error, t_game *game);
int			close_game(t_game *game);
#endif

// double		distance(double x, double y);
// double		fixed_dist(double x1, double y1, double x2, double y2, t_game *game);

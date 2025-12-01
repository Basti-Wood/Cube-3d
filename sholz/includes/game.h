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

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <unistd.h>
// # include <cstdint>
# include <limits.h>
# include <math.h>
# include <sys/time.h>
# include <fcntl.h>

// # define	STATIC_MAP

typedef enum e_dimensions
{
	// INTRO_WIDTH = 960,//1920,
	// INTRO_HEIGHT = 960,
	WIN_WIDTH = 1728,//1536,//1920,
	WIN_HEIGHT = 1080,//960,
	// FRM_WIDTH = SCRN_WIDTH / 2,
	// TEX_WIDTH = 64,
	// TEX_HEIGHT = 64,
	TEXEL_SIZE = 16,
	TILE_SIZE = 32,
	BLOCK_SIZE = 16
}	t_dimensions;

typedef enum e_key_codes
{
	WIN_X_BTN = 17,
	KEY_ESC = 65307,
	KEY_TAB = 65289,
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
	KEY_I = 105,
	// KEY_O = 111,
	// KEY_P = 112,
	// KEY_H = 104,
	KEY_J = 106,
	KEY_K = 107,
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

typedef struct s_line
{
	int		start;
	int		end;
	int		height;
}	t_line;

typedef struct s_texture
{
    int			width;
    int			height;
    int			color_count;
    // int			color_map[95];// 128(ASCII) - 1(DEL) - 32(NUL - US)
    int			color_table[95];
    // int			**image_data;
	int			**pixel_map;
}	t_texture;

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
	double		collision_radius;
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

/* ========================= PARSING STRUCTURES FROM SHOLZ ========================= */

typedef struct s_map
{
	int			**grid;
	int			width;
	int			height;
	t_square	player;
	char		player_dir;
}				t_map;

typedef struct s_config
{
	char		*north_tex;
	char		*south_tex;
	char		*east_tex;
	char		*west_tex;
	int			floor_color;
	int			ceiling_color;
	int			floor_r;
	int			floor_g;
	int			floor_b;
	int			ceiling_r;
	int			ceiling_g;
	int			ceiling_b;
}				t_config;

typedef struct s_keys
{
	int			w;
	int			a;
	int			s;
	int			d;
	int			left;
	int			right;
}				t_keys;

/* ========================= IMAGE STRUCTURE ========================= */

/* Image wrapper - used by window code */
typedef struct s_img
{
	void		*img_ptr;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			height;
}				t_img;

/* ========================= MAIN GAME STRUCTURE ========================= */

typedef struct s_game
{
	// int		level_of_speed;
	bool		skip_intro;
	bool		display_map;
	// bool		intro_concluded;
	void		*mlx;
	void		*win;
	t_img		img;
	//int			**map;
	//int			map_width;
	//int			map_height;
	// int			block_size;
	// t_texture	texture;
	t_texture	texture[4];
	// t_wind_rose	c;
	// t_ray		ray;
	// t_settings	settings;
	t_walker	walker;
	t_hero		hero;
	t_hero		mini_hero;

	// t_window	w;
	// double		time;
	// double		prev_time;
	t_config	config;
	t_map		map;
	t_keys		keys;
}	t_game;

// static char *barrel[] = {};
// static char *bluestone[] = {};
// static char *colorstone[] = {};
// static char *eagle[] = {};
// static char *greenlight[] = {};
// static char *greystone[] = {};
// static char *mossy[] = {};
// static char *pillar[] = {};
// static const char *purplestone[] = {};
// static const char *redbrick[] = {};
// static const char *wood[] = {};

// char		*get_next_line(int fd);
int			ft_isxdigit(int c);
int			hex_pair_to_int(char c1, char c2);
char		*skip_lines(int xpm_fd);
// int			**init_xpm_pixel_map(t_game game);
// int			ft_strcmp(char const *s1, char const *s2);
// time_t		get_current_time(void);
void		init_game(t_game *g);
void		init_game_logic(t_game *g);
t_texture	parse_xpm_file(const char *filename, t_game *game);
void		init_intro_window(t_game *g);
int			**init_map(int map_width, int map_height);
t_hero		init_hero(bool mini, t_game *game);
// t_hero	init_mini_hero(t_hero *hero);
// t_ray	init_ray(t_hero *hero);int
int			intro_loop(t_game *game);
// void		check_wall_integrity(t_game *game);
void		init_game_window(t_game *g);
int			game_loop(t_game *game);
void		draw_line_loop(int screen_x, t_line line, t_game *game);
int			key_press(int keycode, t_game *game);
int			key_release(int keycode, t_game *game);
void		hero_action(t_hero *hero, t_map *map);
int			hero_sonar(t_hero *hero, t_map *map);
// void		go_forward(t_hero *h, int **map);
// void		go_backward(t_hero *h, int **map);
// void		go_port(t_hero *h, int **map);
// void		go_starboard(t_hero *h, int **map);
// void		turn_hero(double dir_x, double plane_x, t_hero *h);
int			get_fd(const char *filename);
void		ft_usleep(int usec);
time_t		get_current_time(void);
t_square	get_offset(bool intro);
bool		collision(int x, int y, t_map *map);
void		put_pixel(int x, int y, int color, t_game *game);
void		draw_walker(int x, int y, t_game *game);
void		draw_empty_square(t_square s, int size, int color, t_game *game);
void		draw_filled_square(t_square s, int size, int color, t_game *game);
void		draw_floor_and_ceiling(t_game *game);
void		draw_map(bool intro, t_game *game);
void		draw_hero(bool intro, t_vector pos, int size, t_game *game);
// void		draw_sonar(t_game game);
void		cast_ray(t_hero *hero);
void		dda(t_game *game);
void		draw_radar(t_game *game);
void		draw_walls(t_game *game);
void		clear_image(t_game *game);
int			close_game(t_game *game);
void		go_slower(t_game *game);
void		go_faster(t_game *game);
int			game(void);

/* ========================= PARSING FUNCTIONS FROM SHOLZ ========================= */

int			parse_cub_file(const char *filename, t_config *config, t_map *map);
void		free_config(t_config *config);
void		free_map(t_map *map);
void		init_config(t_config *config);
int			config_complete(t_config *config);
int			parse_config_section(int fd, t_config *config, char **first_map_line);
int			setup_map(int fd, char *first_line, t_map *map);
char		*ft_strdup_custom(const char *s);
char		*trim_whitespace(char *str);
int			is_empty_line(const char *line);
int			is_valid_filename(const char *filename);
int			parse_color(char *line, int *r, int *g, int *b);
int			rgb_to_int(int r, int g, int b);
int			parse_texture(char *line, char **texture_path);
int			parse_texture_identifier(char *id, char *value, t_config *config);
int			parse_color_identifier(char *id, char *value, t_config *config);
int			parse_identifier(char *line, t_config *config);
int			is_map_char(char c);
int			is_map_line(const char *line);
int			**allocate_map(int height, int width);
int			count_map_lines(int fd);
void		count_map_dimensions(int fd, t_map *map);
void		find_player(t_map *map);
char		*clean_map_line(char *line);
int			parse_map_section(int fd, t_map *map);
void		copy_line_to_grid(char *cleaned, int *grid_row);
char		**read_temp_lines(int fd, char *first_line, int *height, int *max_width);
void		free_temp_lines(char **temp, int count);
char		*skip_spaces(char *str);
char		*find_end_of_word(char *str);
char		*get_identifier(char *line, char **rest);
char		*get_value(char *rest);
int			process_identifier_value(char *id, char *value, t_config *config);
int			is_valid_map(t_map *map);
int			i_walk_the_line(t_map *map);
void		print_map_row(const int *row, int width);
void		display_map(t_map *map, t_config *config);

#endif

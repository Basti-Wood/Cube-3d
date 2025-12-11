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

# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"
# include "../libft/get_next_line.h"
# include <stdio.h>
# include <stdbool.h>
# include <math.h>
# include <sys/time.h>
# include <fcntl.h>

typedef enum e_colors
{
	HERO_COLOR = 0X00FFFF,
	//HERO_CLR = 0x00FF7F,
	WALKER_COLOR = 0xC8C800,
	TILE_COLOR = 0x007777,
	//TILE_CLR = 0x007FAA,
	DOOR_COLOR = 0xCC884D,
	WHITE = 0xFFFFFF,
	BEAM_COLOR = 0xC8C800
}	t_colors;

typedef enum e_dimensions
{
	WIN_WIDTH = 1280,
	WIN_HEIGHT = 800,
	NUM_TEXTURES = 4,
	NUM_COLOR_SYMBOLS = 95,
	TEXEL_SIZE = 16,
	TILE_SIZE = 32,
	BLOCK_SIZE = 16,
	MAX_NODE_SIZE = WIN_HEIGHT * 33/100,
	NUM_DIR = 4,
	MAX_DOORS = 16,
	CHECK_AFTER = 420,
	CLOSE_AFTER = 4200,
	ANIMATION_STEP = 210,
	STEP = 8400000
}	t_dimensions;

typedef enum e_texture_id
{
	FLOOR = 0,
	WALL = 1,
	DOOR = 2,
	CEILING = 3
}	t_texture_id;

// typedef enum e_cardinal_directions
// {
// 	NORTH = 0,
// 	EAST = 1,
// 	SOUTH = 2,
// 	WEST = 3
// }	t_cardinal_directions;

typedef enum e_door_states
{
	CLOSING = -1,
	CLOSED = 0,
	OPENING = 1,
	OPEN = 2
}	t_door_states;

typedef enum e_key_codes
{
	WIN_X_BTN = 17,
	KEY_ESC = 65307,
	// KEY_TAB = 65289,
	KEY_SHIFT_L = 65505,
	KEY_SHIFT_R = 65506,
	KEY_CTRL_L = 65507,
	KEY_CTRL_R = 65508,
	KEY_1 = 49,
	KEY_2 = 50,
	KEY_3 = 51,
	KEY_4 = 52,
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

typedef struct s_horizon
{
	t_vector	ray_dir_start;
	t_vector	ray_dir_end;
	int			p;
	double		z_pos;
	double		dist_row;
	t_vector	step;
	t_vector	pos;
	t_square	tex;
}	t_horizon;

typedef struct s_texture
{
	int	width;
	int	height;
	int	color_count;
	int	color_table[NUM_COLOR_SYMBOLS];
	int	*pixel_map;
}	t_texture;

typedef struct s_line
{
	double	start;
	double	end;
	double	height;
}	t_line;

typedef struct s_ray
{
	t_vector	dir;
	t_square	map;
	t_square	step;
	t_vector	side_dist;
	t_vector	delta_dist;
	double		perp_dist;
	double		inv_perp_dist;
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
	double		z_buffer[WIN_WIDTH];
	bool		move_forward;
	bool		move_backward;
	bool		move_port;
	bool		move_starboard;
	double		move_speed;
	bool		turn_sinistral;
	bool		turn_dextral;
	double		turn_speed;
	int			axes_of_travel;
	double		collision_radius;
	bool		mouse_control;
}	t_hero;

typedef struct s_walker
{
	t_square	pos;
	t_square	dir;
	t_square	start;
	t_square	first;
	t_square	last;
	t_square	dir_set[NUM_DIR];
	int			prev;
}	t_walker;

typedef struct s_door
{
	t_square	pos;
	int			id;
	int			state;
	bool		interrupt;
	time_t		start;
	double		counter;
	time_t		last_check;
	time_t		last_opened;
}	t_door;

typedef struct s_map
{
	int			*grid;
	int			width;
	int			height;
	int			tile_size;
	t_square	node_size;
	t_square	player;
	char		player_dir;
	t_door		door[MAX_DOORS];
	int			number_of_doors;
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

typedef struct s_dev_mode
{
	bool		render_ceiling;
	bool		render_floor;
	bool		render_walls;
	bool		render_map;
}	t_dev_mode;

typedef struct s_game
{
	t_dev_mode	dev_mode;
	bool		skip_intro;
	void		*mlx;
	void		*win;
	t_img		img;
	double		half_screen;
	t_map		map;
	t_texture	texture[NUM_TEXTURES];
	char		*texture_path[NUM_TEXTURES];
	int			floor_color;
	int			ceiling_color;
	int			present_num;
	t_walker	walker;
	t_hero		hero;
	t_hero		mini_hero;
	t_horizon	horizon;
	time_t		last_check;
}	t_game;

void		set_dev_mode(t_dev_mode *dev_mode);

t_texture	parse_xpm_file(const char *filename, t_game *game);
int			get_fd(const char *filename);
char		**parse_header_line(char *line);
void		free_tokens(void **token);
int			parse_color_table_line(char *line, t_texture *texture);
int			parse_hex_color(const char *line);
int			init_xpm_pixel_map(t_texture *texture);
int			parse_pixel_map_line(char *line, int y, t_texture *tx);
char		*skip_lines(int xpm_fd);
void		init_presenter_window(t_game *g);
int			presenter_loop(t_game *game);
// int			init_map(t_game *game);
void		init_walker_window(t_game *g);
t_walker	init_walker(void);
// int			set_walker_start_tile(t_game *game);
int			move_walker(t_game *game);
t_hero		init_hero(bool mini);
int			walker_loop(t_game *game);
void		draw_map(bool intro, t_game *game);
void		draw_filled_square(t_square s, int size, int color, t_game *game);
void		draw_empty_square(t_square s, int size, int color, t_game *game);
t_square	get_offset(bool intro, t_game *game);
void		draw_walker(int x, int y, t_game *game);
void		ft_usleep(int usec);
void		init_game_window(t_game *g);
// void		set_node_size(t_game *game);
int			key_press(int keycode, t_game *game);
int			key_release(int keycode, t_game *game);
void		handle_door(t_hero *hero, t_map *map);
// bool		is_open(t_door *door);
t_door		*get_door(int x, int y, t_map *map);
time_t		get_current_time(void);
int			hero_sonar(t_hero *hero, t_map *map);
int			game_loop(t_game *game);
void		reset_doors(t_hero *hero, t_map *map);
void		hero_action(t_hero *hero, t_map *map);
bool		collision(int x, int y, t_map *map);
void		draw_floor_and_ceiling(t_game *game);
void		legacy_floor_and_ceiling(t_game *game);
void		draw_hero(bool intro, t_vector pos, int size, t_game *game);
void		draw_radar(t_game *game);
void		init_ray(t_hero *hero);
void		dda(t_game *game);
int			get_texture_id(int x, int y, t_map *map);
void		draw_walls(t_game *game);
// void		draw_line(int i, double d, t_line line, t_game *game);
int			get_texture_x(int id, t_game *g);
int			door_opening(int tex_x, int tex_width, t_door *door, t_map *map);
int			door_closing(int tex_x, int tex_width, t_door *door, t_map *map);
void		set_door_counter(t_door *door, t_map *map);
int			get_texel_color(t_square tex, t_texture *texture);
void		put_pixel(int x, int y, int color, t_game *game);
void		clear_image(t_game *game);
void		free_game_resources(t_game *game);
void		free_texture(t_texture *texture);
int			close_game(t_game *game);

// Parsing functions
int			parse_cub_file(const char *filename, t_game *game);
void		free_map(t_map *map);
void		free_texture_paths(t_game *game);
int			setup_map(int fd, char *first_line, t_map *map);
char		*ft_strdup_custom(const char *s);
char		*trim_whitespace(char *str);
int			is_empty_line(const char *line);
int			is_valid_filename(const char *filename);
int			parse_color(char *line, int *r, int *g, int *b);
int			rgb_to_int(int r, int g, int b);
int			is_map_char(char c);
int			is_map_line(const char *line);
int			count_map_lines(int fd);
void		count_map_dimensions(int fd, t_map *map);
int			*allocate_map(int height, int width);
void		find_player(t_map *map);
char		*clean_map_line(char *line);
int			parse_map_section(int fd, t_map *map);
void		copy_line_to_grid(char *cleaned, int *grid_row);
char		**read_temp_lines(int fd, char *first_line,
				int *height, int *max_width);
void		free_temp_lines(char **temp, int count);
char		*skip_spaces(char *str);
char		*find_end_of_word(char *str);
char		*get_identifier(char *line, char **rest);
char		*get_value(char *rest);
int			is_valid_map(t_map *map);
int			i_walk_the_line(t_map *map);
void		print_map_row(const int *row, int width);
void		init_game_for_parsing(t_game *game);
int			config_complete(t_game *game);
int			parse_config_section(int fd, t_game *game, char **first_map_line);
int			parse_identifier(char *line, t_game *game);
int			parse_texture_identifier(char *id, char *value, t_game *game);
int			parse_color_identifier(char *id, char *value, t_game *game);
int			parse_texture(char *line, char **texture_path);

// Map validation functions
int			get_cell(t_map *map, int x, int y);
int			check_direction_x(t_map *map, int x, int y, int dx);
int			check_direction_y(t_map *map, int x, int y, int dy);
int			check_zero_enclosed(t_map *map, int x, int y);
int			is_player_or_empty(int cell);
int			validate_map_with_walker(t_map *map);

// Hero initialization
void		init_hero_from_map(t_hero *hero, t_map *map);

// Raycasting game initialization and loop
int			start_game(t_game *game);
int			init_game_for_raycasting(t_game *game);
int			init_doors(t_game *game);
void		load_textures_from_paths(t_game *game);

// Debug functions
void		display_map(t_game *game);

//Mouse functions
int			mouse_move(int x, int y, t_game *game);

#endif

#ifndef CUB3D_H
# define CUB3D_H

/* ========================= INCLUDES ========================= */
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

/* ========================= DEFINES ========================= */
/* Window settings */
# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define WIN_TITLE "cub3D"

/* Movement and rotation speeds */
# define MOVE_SPEED 0.05
# define ROT_SPEED 0.03

/* Key codes (Linux) - adjust for your system */
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307

/* Map characters */
# define EMPTY '0'
# define WALL '1'
# define NORTH 'N'
# define SOUTH 'S'
# define EAST 'E'
# define WEST 'W'
# define SPACE ' '

/* Directions for textures */
# define TEX_NORTH 0
# define TEX_SOUTH 1
# define TEX_EAST 2
# define TEX_WEST 3

/* ========================= STRUCTURES ========================= */

typedef struct s_ivec
{
	int			x;
	int			y;
}				t_ivec;

typedef struct s_vec
{
	double		x;
	double		y;
}				t_vec;

typedef struct s_walker
{
	t_ivec		pos;
	t_ivec		start;
	t_ivec		wind_rose[4];
	t_ivec		first;
	t_ivec		last;
	int			prev;
}				t_walker;

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

typedef struct s_texture
{
	t_img		img;
	int			width;
	int			height;
}				t_texture;

typedef struct s_player
{
	t_vec		pos;
	t_vec		dir;
	t_vec		plane;
	double		move_speed;
	double		rot_speed;
}				t_player;

typedef struct s_ray
{
	double		camera_x;
	t_vec		ray_dir;
	t_ivec		map;
	t_vec		side_dist;
	t_vec		delta_dist;
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
	double		wall_x;
	int			tex_x;
	int			tex_y;
}				t_ray;

typedef struct s_keys
{
	int			w;
	int			a;
	int			s;
	int			d;
	int			left;
	int			right;
}				t_keys;

typedef struct s_map
{
	int			**grid;
	int			width;
	int			height;
	t_ivec		player;
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

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_texture	textures[4];
	t_player	player;
	t_map		map;
	t_config	config;
	t_keys		keys;
	t_ray		ray;
}				t_game;

//========================= DEBUG FUNCTIONS =========================//
void			print_map_row(const int *row);
void			display_map(t_map *map, t_config *config);

//========================= PARSING FUNCTIONS =========================//
int				parse_cub_file(const char *filename, t_config *config,
					t_map *map);
void			free_config(t_config *config);
void			free_map(t_map *map);

void			init_config(t_config *config);
int				config_complete(t_config *config);

int				parse_config_section(int fd, t_config *config,
					char **first_map_line);

int				setup_map(int fd, char *first_line, t_map *map);

char			*ft_strdup_custom(const char *s);
char			*trim_whitespace(char *str);
int				is_empty_line(const char *line);

int				is_valid_filename(const char *filename);

int				parse_color(char *line, int *r, int *g, int *b);
int				rgb_to_int(int r, int g, int b);

int				parse_texture(char *line, char **texture_path);

int				parse_texture_identifier(char *id, char *value,
					t_config *config);
int				parse_color_identifier(char *id, char *value, t_config *config);
int				parse_identifier(char *line, t_config *config);

int				is_map_char(char c);
int				is_map_line(const char *line);

int				**allocate_map(int height, int width);
int				count_map_lines(int fd);
void			count_map_dimensions(int fd, t_map *map);

void			find_player(t_map *map);
char			*clean_map_line(char *line);

int				parse_map_section(int fd, t_map *map);

void			copy_line_to_grid(char *cleaned, int *grid_row);
char			**read_temp_lines(int fd, char *first_line, int *height,
					int *max_width);
void			free_temp_lines(char **temp, int count);
char			*skip_spaces(char *str);
char			*find_end_of_word(char *str);
char			*get_identifier(char *line, char **rest);
char			*get_value(char *rest);
int				process_identifier_value(char *id, char *value,
					t_config *config);
//========================= CHECKER FUNCTIONS =========================//

int				is_valid_map(t_map *map);
int				i_walk_the_line(t_map *map);

//========================= GAME FUNCTIONS =========================//

// Window initialization
void			init_game(t_game *game);
int				init_mlx(t_game *game);
int				init_image(t_game *game);
void			init_player(t_game *game);

// Event hooks
int				key_press(int keycode, t_game *game);
int				key_release(int keycode, t_game *game);
int				close_game(t_game *game);
void			setup_hooks(t_game *game);

// Rendering
void			put_pixel(t_img *img, int x, int y, int color);
void			draw_test_pattern(t_game *game);
int				render_frame(t_game *game);

#endif

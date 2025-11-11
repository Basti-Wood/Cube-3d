#ifndef GAME_H
#define GAME_H

// # define WIDTH 2240 //1280+768
// # define WIDTH 1280
# define WIDTH 1920 //960+960
# define HEIGHT 768
# define BLOCK 64

# define W 119
# define A 97
# define S 115
# define D 100
// # define W 101 //'E'
// # define A 115 //'S'
// # define S 100 //'D'
// # define D 102 //'F'
# define J 106
# define L 108
# define LEFT 65361
# define RIGHT 65363

# define PI 3.14159265359

#include "./mlx/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef struct s_player
{
	bool mini;

	float posX;
	float posY;
	float angle;

	bool move_forward;
	bool move_backward;
	bool move_port;
	bool move_starboard;

	bool rotate_sinistral;
	bool rotate_dextral;
}   t_player;

typedef struct s_game
{
	void *mlx;
	void *win;
	void *img;

	char *data;
	int bpp;
	int size_line;
	int endian;
	t_player player;
	t_player mini_player;

    char **map;
} t_game;

void init_player(t_player *player);
// void init_mini_player(t_player *player);
int key_press(int keycode, t_game *game);
int key_release(int keycode, t_game *game);
void move_player(t_player *player);
int	close_game(t_game *game);
#endif

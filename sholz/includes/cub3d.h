#ifndef CUB3D_H
# define CUB3D_H

/* ========================= MAIN HEADER ========================= */
/* All structures and parsing functions are now in game.h */
# include "game.h"

/* ========================= CONSTANTS ========================= */

# define WIN_TITLE "Cub3D"
# define MOVE_SPEED 0.05
# define ROT_SPEED 0.03

/* ========================= ADDITIONAL STRUCTURES FOR SHOLZ SPECIFIC CODE ========================= */

/* Alternative player structure - can be converted to/from t_hero */
typedef struct s_player
{
	t_vector	pos;
	t_vector	dir;
	t_vector	plane;
	double		move_speed;
	double		rot_speed;
}				t_player;

/* ========================= SHOLZ WINDOW FUNCTIONS ========================= */

// Window initialization
int				init_mlx(t_game *game);
int				init_image(t_game *game);
void			init_player(t_game *game);
void			setup_hooks(t_game *game);

// Rendering helpers
void			draw_test_pattern(t_game *game);
int				render_frame(t_game *game);

#endif

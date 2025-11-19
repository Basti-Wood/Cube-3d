#include "../includes/game.h"

int	key_press_extended(int keycode, t_game *game)
{
	if (keycode == KEY_W)
	{
		game->player.move_forward = true;
		game->mini_player.move_forward = true;
	}
	if (keycode == KEY_S)
	{
		game->player.move_backward = true;
		game->mini_player.move_backward = true;
	}
	if (keycode == KEY_A)
	{
		game->player.move_port = true;
		game->mini_player.move_port = true;
	}
	if (keycode == KEY_D)
	{
		game->player.move_starboard = true;
		game->mini_player.move_starboard = true;
	}
	return (0);
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		close_game(game);
	if (keycode == KEY_SPACE)
		game->skip_intro = true;
	if (keycode == KEY_LEFT || keycode == KEY_J)
	{
		game->player.turn_sinistral = true;
		game->mini_player.turn_sinistral = true;
	}
	if (keycode == KEY_RIGHT || keycode == KEY_L)
	{
		game->player.turn_dextral = true;
		game->mini_player.turn_dextral = true;
	}
	else
		key_press_extended(keycode, game);
	return (0);
}

int	key_release_extended(int keycode, t_game *game)
{
	if (keycode == KEY_LEFT || keycode == KEY_J)
	{
		game->player.turn_sinistral = false;
		game->mini_player.turn_sinistral = false;
	}
	if (keycode == KEY_RIGHT || keycode == KEY_L)
	{
		game->player.turn_dextral = false;
		game->mini_player.turn_dextral = false;
	}
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == KEY_W)
	{
		game->player.move_forward = false;
		game->mini_player.move_forward = false;
	}
	if (keycode == KEY_S)
	{
		game->player.move_backward = false;
		game->mini_player.move_backward = false;
	}
	if (keycode == KEY_A)
	{
		game->player.move_port = false;
		game->mini_player.move_port = false;
	}
	if (keycode == KEY_D)
	{
		game->player.move_starboard = false;
		game->mini_player.move_starboard = false;
	}
	else
		key_release_extended(keycode, game);
	return (0);
}

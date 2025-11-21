/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstorck <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 15:23:24 by bstorck           #+#    #+#             */
/*   Updated: 2025/11/21 15:23:26 by bstorck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"

int	key_press_extended(int keycode, t_game *game)
{
	if (keycode == KEY_W)
	{
		game->hero.move_forward = true;
		game->mini_hero.move_forward = true;
	}
	if (keycode == KEY_S)
	{
		game->hero.move_backward = true;
		game->mini_hero.move_backward = true;
	}
	if (keycode == KEY_A)
	{
		game->hero.move_port = true;
		game->mini_hero.move_port = true;
	}
	if (keycode == KEY_D)
	{
		game->hero.move_starboard = true;
		game->mini_hero.move_starboard = true;
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
		game->hero.turn_sinistral = true;
		game->mini_hero.turn_sinistral = true;
	}
	if (keycode == KEY_RIGHT || keycode == KEY_L)
	{
		game->hero.turn_dextral = true;
		game->mini_hero.turn_dextral = true;
	}
	else
		key_press_extended(keycode, game);
	return (0);
}

int	key_release_extended(int keycode, t_game *game)
{
	if (keycode == KEY_LEFT || keycode == KEY_J)
	{
		game->hero.turn_sinistral = false;
		game->mini_hero.turn_sinistral = false;
	}
	if (keycode == KEY_RIGHT || keycode == KEY_L)
	{
		game->hero.turn_dextral = false;
		game->mini_hero.turn_dextral = false;
	}
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == KEY_W)
	{
		game->hero.move_forward = false;
		game->mini_hero.move_forward = false;
	}
	if (keycode == KEY_S)
	{
		game->hero.move_backward = false;
		game->mini_hero.move_backward = false;
	}
	if (keycode == KEY_A)
	{
		game->hero.move_port = false;
		game->mini_hero.move_port = false;
	}
	if (keycode == KEY_D)
	{
		game->hero.move_starboard = false;
		game->mini_hero.move_starboard = false;
	}
	else
		key_release_extended(keycode, game);
	return (0);
}

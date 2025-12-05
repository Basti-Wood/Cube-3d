/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstorck <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 15:23:24 by bstorck           #+#    #+#             */
/*   Updated: 2025/12/04 00:30:38 by bstorck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/game.h"

// static int	key_press_dev_mode(int key, t_game *game)
// {
// 	if (key == KEY_I)
// 	{
// 		game->map.max_node_size *= 1.2;
// 		set_node_size(game);
// 	}
// 	if (key == KEY_K)
// 	{
// 		game->map.max_node_size /= 1.2;
// 		set_node_size(game);
// 	}
// 	return (0);
// }

int	key_press_extended(int key, t_game *game)
{
	game->hero.axes_of_travel += 1;
	game->mini_hero.axes_of_travel += 1;
	if (key == KEY_W)
	{
		game->hero.move_forward = true;
		game->mini_hero.move_forward = true;
	}
	if (key == KEY_S)
	{
		game->hero.move_backward = true;
		game->mini_hero.move_backward = true;
	}
	if (key == KEY_A)
	{
		game->hero.move_port = true;
		game->mini_hero.move_port = true;
	}
	if (key == KEY_D)
	{
		game->hero.move_starboard = true;
		game->mini_hero.move_starboard = true;
	}
	return (0);
}

int	key_press(int key, t_game *game)
{
	if (key == KEY_ESC)
		close_game(game);
	if (key == KEY_SHIFT_L || key == KEY_SHIFT_R)
		game->skip_intro = true;
	if (key == KEY_LEFT || key == KEY_J)
	{
		game->hero.turn_sinistral = true;
		game->mini_hero.turn_sinistral = true;
	}
	if (key == KEY_RIGHT || key == KEY_L)
	{
		game->hero.turn_dextral = true;
		game->mini_hero.turn_dextral = true;
	}
	if (key == KEY_W || key == KEY_A || key == KEY_S || key == KEY_D)
		return (key_press_extended(key, game));
	return (0);
}

int	key_release_extended(int key, t_game *game)
{
	game->hero.axes_of_travel -= 1;
	game->mini_hero.axes_of_travel -= 1;
	if (key == KEY_W)
	{
		game->hero.move_forward = false;
		game->mini_hero.move_forward = false;
	}
	if (key == KEY_S)
	{
		game->hero.move_backward = false;
		game->mini_hero.move_backward = false;
	}
	if (key == KEY_A)
	{
		game->hero.move_port = false;
		game->mini_hero.move_port = false;
	}
	if (key == KEY_D)
	{
		game->hero.move_starboard = false;
		game->mini_hero.move_starboard = false;
	}
	return (0);
}

int	key_release(int key, t_game *game)
{
	if (key == KEY_SHIFT_L || key == KEY_SHIFT_R)
		game->skip_intro = false;
	if (key == KEY_LEFT || key == KEY_J)
	{
		game->hero.turn_sinistral = false;
		game->mini_hero.turn_sinistral = false;
	}
	if (key == KEY_RIGHT || key == KEY_L)
	{
		game->hero.turn_dextral = false;
		game->mini_hero.turn_dextral = false;
	}
	if (key == KEY_W || key == KEY_A || key == KEY_S || key == KEY_D)
		return (key_release_extended(key, game));
	return (0);
}

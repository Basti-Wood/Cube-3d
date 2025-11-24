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
	game->hero.axes_of_travel += 1;
	game->mini_hero.axes_of_travel += 1;
	// if (game->hero.axes_of_travel >= 2)
	// {
	// 	game->hero.move_speed = (double)1 / 100;
	// 	game->mini_hero.move_speed = (double)1 / 100;
	// }
	// printf("\taxes=%i\t", game->hero.axes_of_travel);
	// printf("\tspeed=%f\t", game->hero.move_speed);
	// printf("\tspeed=%f\n", game->mini_hero.move_speed);
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

int	key_press(int key, t_game *game)
{
	if (key == KEY_ESC)
		close_game(game);
	if (key == KEY_SPACE)
		game->skip_intro = true;
	if (key == KEY_T)
	// {
		// game->level_of_speed++;
		// printf("\n\tlevel %i\n", game->level_of_speed);
		go_faster(game);
	// }
	if (key == KEY_G)
	// {
		// game->level_of_speed--;
		// printf("\n\tlevel %i\n", game->level_of_speed);
		go_slower(game);
	// }
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
		key_press_extended(key, game);
	return (0);
}

int	key_release_extended(int keycode, t_game *game)
{
	game->hero.axes_of_travel -= 1;
	game->mini_hero.axes_of_travel -= 1;
	// if (game->hero.axes_of_travel < 2)
	// {
	// 	game->hero.move_speed = sqrt(2) / 100;
	// 	game->mini_hero.move_speed = sqrt(2) / 100;
	// }
	// printf("\taxes=%i\t", game->hero.axes_of_travel);
	// printf("\tspeed=%f\t", game->hero.move_speed);
	// printf("\tspeed=%f\n", game->mini_hero.move_speed);
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
	return (0);
}

int	key_release(int key, t_game *game)
{
	if (key == KEY_LEFT || key == KEY_J)
	{
		game->hero.turn_sinistral = false;
		game->mini_hero.turn_sinistral = false;
	}
	if (key == KEY_SPACE)
		game->skip_intro = false;
	if (key == KEY_RIGHT || key == KEY_L)
	{
		game->hero.turn_dextral = false;
		game->mini_hero.turn_dextral = false;
	}
	if (key == KEY_W || key == KEY_A || key == KEY_S || key == KEY_D)
		key_release_extended(key, game);
	return (0);
}

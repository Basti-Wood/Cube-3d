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

#include "../../includes/cub3d.h"

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

int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		close_game(game);
	else if (keycode == KEY_W)
		game->keys.w = 1;
	else if (keycode == KEY_S)
		game->keys.s = 1;
	else if (keycode == KEY_A)
		game->keys.a = 1;
	else if (keycode == KEY_D)
		game->keys.d = 1;
	else if (keycode == KEY_LEFT)
		game->keys.left = 1;
	else if (keycode == KEY_RIGHT)
		game->keys.right = 1;
	else if (keycode == KEY_TAB)
		game->display_map = true;
	else if (keycode == KEY_I)
		go_faster(game);
	else if (keycode == KEY_K)
		go_slower(game);
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->keys.w = 0;
	else if (keycode == KEY_S)
		game->keys.s = 0;
	else if (keycode == KEY_A)
		game->keys.a = 0;
	else if (keycode == KEY_D)
		game->keys.d = 0;
	else if (keycode == KEY_LEFT)
		game->keys.left = 0;
	else if (keycode == KEY_RIGHT)
		game->keys.right = 0;
	else if (keycode == KEY_TAB)
		game->display_map = false;
	return (0);
}

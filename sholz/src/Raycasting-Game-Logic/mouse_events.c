/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstorck <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 15:23:24 by bstorck           #+#    #+#             */
/*   Updated: 2025/12/06 00:00:00 by bstorck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/game.h"

int mouse_move(int x, int y, t_game *game)
{
	static int	center_x = WIN_WIDTH / 2;
	static int	center_y = WIN_HEIGHT / 2;
	int			delta_x;

	(void)y;
	delta_x = x - center_x;
	
	if (delta_x < -2)
	{
		game->hero.turn_sinistral = true;
		game->mini_hero.turn_sinistral = true;
		game->hero.turn_dextral = false;
		game->mini_hero.turn_dextral = false;
	}
	else if (delta_x > 2)
	{
		game->hero.turn_dextral = true;
		game->mini_hero.turn_dextral = true;
		game->hero.turn_sinistral = false;
		game->mini_hero.turn_sinistral = false;
	}
	else
	{
		game->hero.turn_sinistral = false;
		game->hero.turn_dextral = false;
		game->mini_hero.turn_sinistral = false;
		game->mini_hero.turn_dextral = false;
	}
	
	mlx_mouse_move(game->mlx, game->win, center_x, center_y);
	
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstorck <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+   +#+     */
/*   Created: 2025/12/09 00:00:00 by bstorck           #+#    #+#             */
/*   Updated: 2025/12/09 00:00:00 by bstorck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"

static void	wrap_mouse_position(int *x, int *y, t_game *game)
{
	int	margin;

	(void) y;
	margin = 50;
	if (*x > WIN_WIDTH - margin)
	{
		*x = margin;
		mlx_mouse_move(game->mlx, game->win, *x,  WIN_HEIGHT/2);
	}
	else if (*x < margin)
	{
		*x = WIN_WIDTH - margin;
		mlx_mouse_move(game->mlx, game->win, *x,  WIN_HEIGHT/2);
	}
}

int	mouse_move(int x, int y, t_game *game)
{
	static int	old_x;

	if (old_x == 0)
		old_x = x;
	wrap_mouse_position(&x, &y, game);
	if (x == old_x)
	{
		game->hero.turn_dextral = false;
		game->mini_hero.turn_dextral = false;
		game->hero.turn_sinistral = false;
		game->mini_hero.turn_sinistral = false;
		return (0);
	}
	else if (x < old_x)
	{
		game->hero.turn_sinistral = true;
		game->mini_hero.turn_sinistral = true;
		game->hero.turn_dextral = false;
		game->mini_hero.turn_dextral = false;
	}
	else if (x > old_x)
	{
		game->hero.turn_dextral = true;
		game->mini_hero.turn_dextral = true;
		game->hero.turn_sinistral = false;
		game->mini_hero.turn_sinistral = false;
	}
	old_x = x;
	return (0);
}

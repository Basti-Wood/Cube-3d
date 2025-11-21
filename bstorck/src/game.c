/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstorck <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 15:25:38 by bstorck           #+#    #+#             */
/*   Updated: 2025/11/21 15:25:41 by bstorck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"

int	game_loop(t_game *game)
{
	move_hero(game->map, &game->hero);
	move_hero(game->map, &game->mini_hero);
	clear_image(game);
	draw_map(game);
	draw_hero(game->mini_hero.pos.x, game->mini_hero.pos.y, 5, game);
	draw_radar(game);
	draw_floor_and_ceiling(game);
	draw_walls(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}

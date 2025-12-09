/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstorck <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 15:23:57 by bstorck           #+#    #+#             */
/*   Updated: 2025/12/09 07:32:48 by bstorck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/game.h"

void	draw_walker(int x, int y, t_game *game)
{
	t_vector	pos;

	pos.x = x + 0.5;
	pos.y = y + 0.5;
	clear_image(game);
	draw_map(true, game);
	draw_hero(true, pos, (TILE_SIZE / 2) - 1, game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.ptr, 0, 0);
	ft_usleep(10000);
}

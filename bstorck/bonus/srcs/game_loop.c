/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstorck <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 00:14:56 by bstorck           #+#    #+#             */
/*   Updated: 2025/12/04 00:14:57 by bstorck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/game.h"

void	init_game_window(t_game *g)
{
	t_img	*i;

	i = &g->img;
	i->width = WIN_WIDTH;
	i->height = WIN_HEIGHT;
	i->aspect_ratio = (double)i->width / (double)i->height;
	set_node_size(g);
	g->half_screen = (double)i->height / 2;
	g->win = mlx_new_window(g->mlx, i->width, i->height, "Picostein No D");
	i->ptr = mlx_new_image(g->mlx, i->width, i->height);
	i->data = mlx_get_data_addr(i->ptr, &i->bpp, &i->size_line, &i->endian);
	mlx_hook(g->win, 2, 1L << 0, key_press, g);
	mlx_hook(g->win, 3, 1L << 1, key_release, g);
	mlx_hook(g->win, WIN_X_BTN, 0, close_game, g);
}

//0.15625 * game->map.tile_size
int	game_loop(t_game *game)
{
	hero_action(&game->hero, &game->map);
	hero_action(&game->mini_hero, &game->map);
	clear_image(game);
	draw_floor_and_ceiling(game);
	draw_walls(game);
	draw_radar(game);
	draw_map(false, game);
	draw_hero(false, game->mini_hero.pos, game->map.tile_size / 6, game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.ptr, 0, 0);
	return (0);
}

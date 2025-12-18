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

#include "../../includes/game.h"

static void	set_node_size(t_game *game)
{
	t_map	*m;

	m = &game->map;
	m->node_size.x = MAX_NODE_SIZE;
	m->node_size.y = MAX_NODE_SIZE;
	if (m->width > m->height)
	{
		m->tile_size = m->node_size.x / m->width;
		m->node_size.x = m->tile_size * m->width;
		m->node_size.y = m->tile_size * m->height;
	}
	else
	{
		m->tile_size = m->node_size.y / m->height;
		m->node_size.x = m->tile_size * m->width;
		m->node_size.y = m->tile_size * m->height;
	}
}

void	init_game_window(t_game *g)
{
	t_img	*i;

	i = &g->img;
	i->width = WIN_WIDTH;
	i->height = WIN_HEIGHT;
	i->aspect_ratio = (double)i->width / (double)i->height;
	set_node_size(g);
	g->half_screen_height = (double)i->height / 2;
	g->half_screen_width = (double)i->width / 2;
	g->win = mlx_new_window(g->mlx, i->width, i->height, "Picostein: Zero D");
	i->ptr = mlx_new_image(g->mlx, i->width, i->height);
	i->data = mlx_get_data_addr(i->ptr, &i->bpp, &i->size_line, &i->endian);
	mlx_hook(g->win, 2, 1L << 0, key_press, g);
	mlx_hook(g->win, 3, 1L << 1, key_release, g);
	mlx_hook(g->win, 6, 1L << 6, mouse_move, g);
	mlx_hook(g->win, WIN_X_BTN, 0, close_game, g);
}

int	game_loop(t_game *game)
{
	if (get_current_time() > (game->last_check + CHECK_AFTER))
	{
		reset_doors(&game->hero, &game->map);
		game->last_check = get_current_time();
	}
	hero_action(&game->hero, &game->map);
	hero_action(&game->mini_hero, &game->map);
	clear_image(game);
	draw_floor_and_ceiling(game);
	draw_walls(game);
	draw_sprites(game);
	draw_radar(game);
	draw_map(false, game);
	draw_hero(false, game->mini_hero.pos, game->map.tile_size / 6, game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.ptr, 0, 0);
	return (0);
}

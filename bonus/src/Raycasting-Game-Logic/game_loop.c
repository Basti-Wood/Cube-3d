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

static void	init_door(int x, int y, int i, t_door *door)
{
	door->pos.x = x;
	door->pos.y = y;
	door->id = i;
	door->state = CLOSED;
	door->interrupt = false;
	door->start = 0;
	door->counter = 0;
	door->last_check = get_current_time();
	door->last_opened = 0;
}

int	init_doors(t_game *game)
{
	int			x;
	int			y;
	int			i;

	i = -1;
	y = -1;
	while (++y < game->map.height)
	{
		x = -1;
		while (++x < game->map.width)
		{
			if (game->map.grid[y * game->map.width + x] == DOOR)
			{
				i++;
				if (i == MAX_DOORS)
				{
					printf("Error: Number of doors exceeds threshold\n");
					return (1);
				}
				init_door(x, y, i, &game->map.door[i]);
			}
		}
	}
	game->map.number_of_doors = i + 1;
	return (0);
}

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
	g->half_screen = (double)i->height / 2;
	g->win = mlx_new_window(g->mlx, i->width, i->height, "Picostein: Zero D");
	i->ptr = mlx_new_image(g->mlx, i->width, i->height);
	i->data = mlx_get_data_addr(i->ptr, &i->bpp, &i->size_line, &i->endian);
	mlx_hook(g->win, 2, 1L << 0, key_press, g);
	mlx_hook(g->win, 3, 1L << 1, key_release, g);
	mlx_hook(g->win, 6, 1L << 6, mouse_move, g);
	mlx_hook(g->win, WIN_X_BTN, 0, close_game, g);
}

//0.15625 * game->map.tile_size
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
	if (game->dev_mode.render_walls)
		draw_walls(game);
	if (game->dev_mode.render_map)
	{
		draw_radar(game);
		draw_map(false, game);
		draw_hero(false, game->mini_hero.pos, game->map.tile_size / 6, game);
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img.ptr, 0, 0);
	mlx_mouse_move(game->mlx, game->win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	return (0);
}

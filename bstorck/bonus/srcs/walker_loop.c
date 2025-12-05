/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walker_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstorck <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 15:23:02 by bstorck           #+#    #+#             */
/*   Updated: 2025/12/04 00:31:58 by bstorck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/game.h"

void	init_walker_window(t_game *g)
{
	t_img	*i;

	i = &g->img;
	i->width = g->map.width * TILE_SIZE;
	i->height = g->map.height * TILE_SIZE;
	g->map.tile_size = TILE_SIZE;
	g->win = mlx_new_window(g->mlx, i->width, i->height, "Map Checker");
	i->ptr = mlx_new_image(g->mlx, i->width, i->height);
	i->data = mlx_get_data_addr(i->ptr, &i->bpp, &i->size_line, &i->endian);
	mlx_hook(g->win, 2, 1L << 0, key_press, g);
	mlx_hook(g->win, 3, 1L << 1, key_release, g);
	mlx_hook(g->win, WIN_X_BTN, 0, close_game, g);
}

t_walker	init_walker(t_game *game)
{
	t_walker	walker;

	walker.pos.x = 0;
	walker.pos.y = 0;
	walker.start.x = 0;
	walker.start.y = 0;
	walker.dir_set[0].x = -1;
	walker.dir_set[0].y = 0;
	walker.dir_set[1].x = 0;
	walker.dir_set[1].y = -1;
	walker.dir_set[2].x = 1;
	walker.dir_set[2].y = 0;
	walker.dir_set[3].x = 0;
	walker.dir_set[3].y = 1;
	walker.first.x = 0;
	walker.first.y = 0;
	walker.last.x = 0;
	walker.last.y = 0;
	walker.dir.x = 0;
	walker.dir.y = 0;
	walker.prev = 0;
	walker.first = walker.dir_set[walker.prev];
	return (walker);
}

int	is_valid_move(t_game *game)
{
	t_walker	*w;
	int			x;
	int			y;

	w = &game->walker;
	x = w->pos.x + w->dir.x;
	y = w->pos.y + w->dir.y;
	if (x >= 0 && x < game->map.width && y >= 0 && y < game->map.height)
		return (game->map.grid[y * game->map.width + x]);
	return (0);
}

int	move_walker(t_game *game)
{
	t_walker	*walker;
	int			i;

	walker = &game->walker;
	i = 0;
	while (++i < 5)
	{
		walker->dir = walker->dir_set[(walker->prev + i) % 4];
		if (is_valid_move(game))
		{
			walker->prev = (walker->prev + i + 2) % 4;
			walker->pos.x += walker->dir.x;
			walker->pos.y += walker->dir.y;
			return (0);
		}
	}
	printf("Error\nWalker: No vaild move");
	return (1);
}

int	walker_loop(t_game *game)
{
	t_walker	*w;

	w = &game->walker;
	if (move_walker(game))
	{
		printf("Error\nInvalid map.\n");
		close_game(game);
	}
	w->last = w->dir_set[w->prev];
	if (!game->skip_intro)
		draw_walker(w->pos.x, w->pos.y, game);
	if (w->pos.x == w->start.x && w->pos.y == w->start.y)
	{
		if ((w->first.x + w->last.x == 0) && (w->first.y + w->last.y == 0))
		{
			printf("Error\nThe map must be closed/surrounded by walls.\n");
			close_game(game);
		}
		mlx_destroy_image(game->mlx, game->img.ptr);
		mlx_destroy_window(game->mlx, game->win);
	}
	return (0);
}

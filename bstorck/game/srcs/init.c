/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstorck <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 09:03:18 by bstorck           #+#    #+#             */
/*   Updated: 2025/11/25 09:03:20 by bstorck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/game.h"

t_hero	init_hero(bool mini, t_game *g)
{
	t_hero	h;

	if (mini == true)
		h.mini = true;
	h.pos.x = 11;
	h.pos.y = 28;
	h.probe.x = 0;
	h.probe.y = 0;
	h.dir.x = 0;
	h.dir.y = -1;
	h.plane.x = 0.66;
	h.plane.y = 0;
	h.scan_x = 0;
	h.fov = 2 * atan(fabs(h.plane.x + h.plane.y) / fabs(h.dir.x + h.dir.y));
	h.move_forward = false;
	h.move_backward = false;
	h.move_port = false;
	h.move_starboard = false;
	h.move_speed = sqrt(2) / 50;
	h.turn_sinistral = false;
	h.turn_dextral = false;
	h.turn_speed = PI / 100;
	h.axes_of_travel = 0;
	h.collision_radius = 5;
	return (h);
}

t_walker	init_walker(t_game *game)
{
	t_walker	walker;

	walker.pos.x = 0;
	walker.pos.y = 0;
	walker.start.x = 0;
	walker.start.y = 0;
	walker.wind_rose[0].x = -1;
	walker.wind_rose[0].y = 0;
	walker.wind_rose[1].x = 0;
	walker.wind_rose[1].y = -1;
	walker.wind_rose[2].x = 1;
	walker.wind_rose[2].y = 0;
	walker.wind_rose[3].x = 0;
	walker.wind_rose[3].y = 1;
	walker.first.x = 0;
	walker.first.y = 0;
	walker.last.x = 0;
	walker.last.y = 0;
	walker.dir.x = 0;
	walker.dir.y = 0;
	walker.prev = 0;
	return (walker);
}

void	init_game_window(t_game *g)
{
	g->w_width = GAME_WIDTH;
	g->w_height = GAME_HEIGHT;
	g->win = mlx_new_window(g->mlx, g->w_width, g->w_height, "Picostein No D");
	g->img = mlx_new_image(g->mlx, g->w_width, g->w_height);
	g->data = mlx_get_data_addr(g->img, &g->bpp, &g->size_line, &g->endian);
	mlx_hook(g->win, 2, 1L << 0, key_press, g);
	mlx_hook(g->win, 3, 1L << 1, key_release, g);
	mlx_hook(g->win, WIN_X_BTN, 0, close_game, g);
}

void	init_intro_window(t_game *g)
{
	g->w_width = INTRO_WIDTH;
	g->w_height = INTRO_HEIGHT;
	g->win = mlx_new_window(g->mlx, g->w_width, g->w_height, "Map Checker");
	g->img = mlx_new_image(g->mlx, g->w_width, g->w_height);
	g->data = mlx_get_data_addr(g->img, &g->bpp, &g->size_line, &g->endian);
	mlx_hook(g->win, 2, 1L << 0, key_press, g);
	mlx_hook(g->win, 3, 1L << 1, key_release, g);
	mlx_hook(g->win, WIN_X_BTN, 0, close_game, g);
}

void	init_game(t_game *g)
{
	g->skip_intro = false;
	g->map_width = 30;
	g->map_height = 30;
	g->map = init_map(g->map_width, g->map_width);
	g->walker = init_walker(g);
	if (get_start(g))
	{
		printf("Error\nUnknown error.\n");
		close_game(g);
	}
	if (get_direction(g))
	{
		printf("Error\nUnknown error.\n");
		close_game(g);
	}
	g->walker.first = g->walker.wind_rose[g->walker.prev];
	g->hero = init_hero(false, g);
	g->mini_hero = init_hero(true, g);
	g->mlx = mlx_init();
}

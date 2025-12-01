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
	t_hero		h;

	if (mini == true)
		h.mini = true;
	h.pos.x = 11;
	h.pos.y = 28;
	h.probe.x = 0;
	h.probe.y = 0;
	h.dir.x = 0;
	h.dir.y = -1;
	h.plane.x = 0.66 * (1.0 * WIN_WIDTH / WIN_HEIGHT);
	h.plane.y = 0;
	h.scan_x = 0;
	h.fov = 2 * atan(fabs(h.plane.x + h.plane.y) / fabs(h.dir.x + h.dir.y));
	h.move_forward = false;
	h.move_backward = false;
	h.move_port = false;
	h.move_starboard = false;
	h.move_speed = /*1.771561 * */sqrt(2) / 25/*100*/;
	h.turn_sinistral = false;
	h.turn_dextral = false;
	h.turn_speed = /*1.265319018496 * */PI / 75/*200*/;
	h.axes_of_travel = 0;
	h.collision_radius = 0.15625 * BLOCK_SIZE;
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
	// walker.c = &game->c;
	walker.first.x = 0;
	walker.first.y = 0;
	walker.last.x = 0;
	walker.last.y = 0;
	walker.dir.x = 0;
	walker.dir.y = 0;
	walker.prev = 0;
	return (walker);
}

// int	**init_xpm_pixel_map(t_game *game)
// {
// 	int	**pixel_map;
// 	int			i;
//
// 	pixel_map = (int**)malloc(sizeof(int*) * game->texture.height);
// 	if (!pixel_map)
// 	{
// 		printf("Error\nFailed to allocate memory [textures]\n");
// 		close_game(game);
// 	}
// 	i = -1;
// 	while (++i < game->texture.height)
// 	{
// 		pixel_map[i] = (int*)malloc(sizeof(int) * game->texture.width);
// 		if (!pixel_map[i])
// 		{
// 			printf("Error\nFailed to allocate memory [textures]\n");
// 			close_game(game);
// 		}
// 	}
// 	return (pixel_map);
// }

void	init_game_window(t_game *g)
{
	g->w_width = WIN_WIDTH;
	g->w_height = WIN_HEIGHT;
	g->win = mlx_new_window(g->mlx, g->w_width, g->w_height, "Picostein No D");
	g->img = mlx_new_image(g->mlx, g->w_width, g->w_height);
	g->data = mlx_get_data_addr(g->img, &g->bpp, &g->size_line, &g->endian);
	// mlx_put_image_to_window(g->mlx, g->win, g->img, 0, 0);
	mlx_hook(g->win, 2, 1L << 0, key_press, g);
	mlx_hook(g->win, 3, 1L << 1, key_release, g);
	mlx_hook(g->win, WIN_X_BTN, 0, close_game, g);
}

void	init_intro_window(t_game *g)
{
	g->w_width = g->map_width * TILE_SIZE;
	g->w_height = g->map_height * TILE_SIZE;
	g->win = mlx_new_window(g->mlx, g->w_width, g->w_height, "Map Checker");
	g->img = mlx_new_image(g->mlx, g->w_width, g->w_height);
	g->data = mlx_get_data_addr(g->img, &g->bpp, &g->size_line, &g->endian);
	// mlx_put_image_to_window(g->mlx, g->win, g->img, 0, 0);
	mlx_hook(g->win, 2, 1L << 0, key_press, g);
	mlx_hook(g->win, 3, 1L << 1, key_release, g);
	mlx_hook(g->win, WIN_X_BTN, 0, close_game, g);
}

void	init_game(t_game *g)
{
	int		i;
	char	*path[5];

	// game->time = 0;
	// game->prev_time = 0;
	g->skip_intro = false;
	g->display_map = false;
	path[0] = "texs/bluestone.xpm";
	path[1] = "texs/greystone.xpm";
	path[2] = "texs/redbrick.xpm";
	path[3] = "texs/mossy.xpm";
	path[4] = NULL;
	i = -1;
	while (++i < 4)
		g->texture[i] = parse_xpm_file(path[i], g);
	g->map_width = 30;
	g->map_height = 30;
	g->map = init_map(g->map_width, g->map_width);
	// int	i;
	// i = -1;
	// while (++i < 4)
	// 	g->texture[i].pixel_map = init_xpm_pixel_map(g);
	// g->c = init_wind_rose();
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
	// g->settings.speed_factor = 1;
	// g->level_of_speed = 0;
	g->walker.first = g->walker.wind_rose[g->walker.prev];
	g->hero = init_hero(false, g);
	g->mini_hero = init_hero(true, g);
	// game->hero.ray = init_ray(&game->hero);
	// game->ray = game->hero.ray;
	g->mlx = mlx_init();
}

// void	check_wall_integrity(t_game *game)
// {
// 	// t_walker	*w;
//
// 	// w = &game->walker;
// 	// game->walker = init_walker();
// 	// if (get_start(&game->walker, game))
// 	// 	close_game(game);
// 	// game->walker.prev = get_direction(&game->walker, game);
// 	// if (game->walker.prev == -1)
// 	// 	close_game(game);
// 	// game->walker.first = game->walker.wind_rose[game->walker.prev];
// 	// mlx_loop_hook(game->mlx, intro_loop, &game);
// 	// mlx_loop(game->mlx);
// 	// if ((game->walker.first.x + game->walker.last.x == 0) && (game->walker.first.y + game->walker.last.y == 0))
// 	// 	close_game(game);
// 	// mlx_destroy_image(game->mlx, game->img);
// 	// mlx_destroy_window(game->mlx, game->win);
// 	init_intro_window(game);
// 	// mlx_hook(game->win, 2, 1L << 0, key_press, &game);
// 	// mlx_hook(game->win, 3, 1L << 1, key_release, &game);
// 	// mlx_hook(game->win, WIN_X_BTN, 0, close_game, &game);
// 	// check_wall_integrity(&game);
// 	mlx_loop_hook(game->mlx, intro_loop, game);
// 	mlx_loop(game->mlx);
// 	// printf("\tfirst\t%i\t%i\n", game.walker.first.x, game.walker.first.y);
// 	// printf("\tlast\t%i\t%i\n\n", game.walker.last.x, game.walker.last.y);
// 	// if ((w->first.x + w->last.x == 0) && (w->first.y + w->last.y == 0))
// 	// {
// 	// 	printf("Error\nThe map must be closed/surrounded by walls.\n");
// 	// 	game->win = mlx_new_window(game->mlx, FRM_WIDTH, SCRN_HEIGHT, "Error");
// 	// 	game->img = mlx_new_image(game->mlx, FRM_WIDTH, SCRN_HEIGHT);
// 	// 	// game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, &game->endian);
// 	// 	// mlx_hook(game->win, WIN_X_BTN, 0, close_game, game);
// 	// 	close_game(game);
// 	// }
// }

// int	main(int argc, char **argv)
// {
// 	t_game	game;
// 	// char	*flag;
//
// 	// if (argc == 2)
// 	// 	flag = argv[1];
// 	// else
// 	// 	flag = "intro";
// 	// init
// 	init_game(&game);
// 	init_intro(&game);
// 	// hooks
// 	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
// 	mlx_hook(game.win, 3, 1L << 1, key_release, &game);
// 	mlx_hook(game.win, WIN_X_BTN, 0, close_game, &game);
// 	check_wall_integrity(&game);
// 	init_game2(&game);
// 	// draw loop
// 	// mlx_loop_hook(game.mlx, i_walk_the_line, &game);
// 	// mlx_loop(game.mlx);
// 	mlx_loop_hook(game.mlx, game_loop, &game);
// 	mlx_loop(game.mlx);
// 	return (0);
// }

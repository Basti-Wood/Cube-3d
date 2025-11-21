/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstorck <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 15:22:40 by bstorck           #+#    #+#             */
/*   Updated: 2025/11/21 15:22:42 by bstorck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"

int	close_game(t_game *game)
{
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	while (game->map_height--)
		free(game->map[game->map_height]);
	free(game->map);
	exit(0);
	return (0);
}

void	init_game_window(t_game *g)
{
	g->win = mlx_new_window(g->mlx, SCRN_WIDTH, SCRN_HEIGHT, "Picostein No D");
	g->img = mlx_new_image(g->mlx, SCRN_WIDTH, SCRN_HEIGHT);
	g->data = mlx_get_data_addr(g->img, &g->bpp, &g->size_line, &g->endian);
	// mlx_put_image_to_window(g->mlx, g->win, g->img, 0, 0);
	mlx_hook(g->win, 2, 1L << 0, key_press, g);
	mlx_hook(g->win, 3, 1L << 1, key_release, g);
	mlx_hook(g->win, WIN_X_BTN, 0, close_game, g);
}

void	init_intro_window(t_game *g)
{
	g->win = mlx_new_window(g->mlx, FRM_WIDTH, SCRN_HEIGHT, "Map Checker");
	g->img = mlx_new_image(g->mlx, FRM_WIDTH, SCRN_HEIGHT);
	g->data = mlx_get_data_addr(g->img, &g->bpp, &g->size_line, &g->endian);
	// mlx_put_image_to_window(g->mlx, g->win, g->img, 0, 0);
	mlx_hook(g->win, 2, 1L << 0, key_press, g);
	mlx_hook(g->win, 3, 1L << 1, key_release, g);
	mlx_hook(g->win, WIN_X_BTN, 0, close_game, g);
}

void	init_game(t_game *g)
{
	// game->time = 0;
	// game->prev_time = 0;
	g->skip_intro = false;
	g->map_width = 30;
	g->map_height = 30;
	g->map = init_map(g->map_width, g->map_width);
	g->walker = init_walker();
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
	g->hero = init_hero(false);
	g->mini_hero = init_hero(true);
	// game->hero.ray = init_ray(&game->hero);
	// game->ray = game->hero.ray;
	g->mlx = mlx_init();
}

int	main(void)
{
	t_game	game;

	init_game(&game);
	init_intro_window(&game);
	mlx_loop_hook(game.mlx, intro_loop, &game);
	mlx_loop(game.mlx);
	init_game_window(&game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}

	// char	*flag;

	// if (argc == 2)
	// 	flag = argv[1];
	// else
	// 	flag = "intro";
	// init
	// init_game(&game);
	// init_intro(&game);
	// hooks
	// mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	// mlx_hook(game.win, 3, 1L << 1, key_release, &game);
	// mlx_hook(game.win, WIN_X_BTN, 0, close_game, &game);
	// // check_wall_integrity(&game);
	// mlx_loop_hook(game.mlx, intro_loop, &game);
	// mlx_loop(game.mlx);
	// // printf("\tfirst\t%i\t%i\n", game.walker.first.x, game.walker.first.y);
	// // printf("\tlast\t%i\t%i\n\n", game.walker.last.x, game.walker.last.y);
	// if ((game.walker.first.x + game.walker.last.x == 0) && (game.walker.first.y + game.walker.last.y == 0))
	// 	close_game(&game);
	// mlx_destroy_image(game.mlx, game.img);
	// mlx_destroy_window(game.mlx, game.win);
	// check_wall_integrity(&game);
	// init_intro_window(&game);
	// mlx_loop_hook(game.mlx, intro_loop, &game);
	// mlx_loop(game.mlx);
	// init_game_window(&game);
	// mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	// mlx_hook(game.win, 3, 1L << 1, key_release, &game);
	// mlx_hook(game.win, WIN_X_BTN, 0, close_game, &game);
	// draw loop
// 	mlx_loop_hook(game.mlx, game_loop, &game);
// 	mlx_loop(game.mlx);
// 	return (0);
// }

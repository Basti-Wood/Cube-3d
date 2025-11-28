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

void	move_hero(int **map, t_hero *hero)
{
	if (hero->move_forward)
		go_forward(hero, map);
	if (hero->move_backward)
		go_backward(hero, map);
	if (hero->move_port)
		go_port(hero, map);
	if (hero->move_starboard)
		go_starboard(hero, map);
	if (hero->turn_sinistral || hero->turn_dextral)
		turn_hero(hero->dir.x, hero->plane.x, hero);
}

int	game_loop(t_game *game)
{
	// printf("\tspeed=%f\t", game->hero.move_speed);
	// printf("\tspeed=%f\n", game->mini_hero.move_speed);
	move_hero(game->map, &game->hero);
	move_hero(game->map, &game->mini_hero);
	clear_image(game);
	draw_map(game);
	draw_hero(game->mini_hero.pos.x, game->mini_hero.pos.y, 5, game);
	draw_radar(game);
	// draw_sonar(game);
	draw_floor_and_ceiling(game);
	draw_walls(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
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

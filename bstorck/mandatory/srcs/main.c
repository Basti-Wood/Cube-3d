/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstorck <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 15:22:40 by bstorck           #+#    #+#             */
/*   Updated: 2025/12/04 00:30:52 by bstorck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/game.h"

static void	ft_swap(t_texture *a, t_texture *b)
{
	t_texture	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

t_hero	init_hero(bool mini, t_game *g)
{
	t_hero		h;

	h.mini = mini;
	h.pos.x = 11;
	h.pos.y = 28;
	h.probe.x = 0;
	h.probe.y = 0;
	h.dir.x = 0;
	h.dir.y = -1;
	h.plane.x = 0.7679;
	h.plane.y = 0;
	h.scan_x = 0;
	h.fov = 2 * atan(fabs(h.plane.x));
	h.move_forward = false;
	h.move_backward = false;
	h.move_port = false;
	h.move_starboard = false;
	h.move_speed = sqrt(2) * 0.04;
	h.turn_sinistral = false;
	h.turn_dextral = false;
	h.turn_speed = PI / 75;
	h.axes_of_travel = 0;
	h.collision_radius = 0.15625 * BLOCK_SIZE;
	return (h);
}

void	load_textures(t_game *game)
{
	game->texture[0] = parse_xpm_file("texs/bluestone.xpm", game);
	game->texture[1] = parse_xpm_file("texs/greystone.xpm", game);
	game->texture[2] = parse_xpm_file("texs/redbrick.xpm", game);
	game->texture[3] = parse_xpm_file("texs/mossy.xpm", game);
}

int	init_game_resources(t_game *game)
{
	game->skip_intro = false;
	game->display_map = false;
	game->map.width = 30;
	game->map.height = 30;
	if (init_map(game))
		return (1);
	load_textures(game);
	game->walker = init_walker(game);
	if (get_walker_start(game))
	{
		printf("Error\nUnknown error.\n");
		close_game(game);
	}
	if (move_walker(game))
	{
		printf("Error\nUnknown error.\n");
		close_game(game);
	}
	game->walker.first = game->walker.dir_set[game->walker.prev];
	game->hero = init_hero(false, game);
	game->mini_hero = init_hero(true, game);
	game->mlx = mlx_init();
	return (0);
}

int	main(void)
{
	t_game	game;

	if (init_game_resources(&game))
	{
		printf("Failed to initialize game\n");
		free_game_resources(&game);
		return (1);
	}
	// init_presenter_window(&game);
	// mlx_loop_hook(game.mlx, presenter_loop, &game);
	// mlx_loop(game.mlx);
	// ft_swap(&game.texture[0], &game.texture[1]);
	// init_presenter_window(&game);
	// mlx_loop_hook(game.mlx, presenter_loop, &game);
	// mlx_loop(game.mlx);
	// ft_swap(&game.texture[0], &game.texture[2]);
	// init_presenter_window(&game);
	// mlx_loop_hook(game.mlx, presenter_loop, &game);
	// mlx_loop(game.mlx);
	// ft_swap(&game.texture[0], &game.texture[3]);
	// init_presenter_window(&game);
	// mlx_loop_hook(game.mlx, presenter_loop, &game);
	// mlx_loop(game.mlx);
	// ft_swap(&game.texture[0], &game.texture[1]);
	// ft_swap(&game.texture[1], &game.texture[2]);
	// ft_swap(&game.texture[2], &game.texture[3]);
	init_walker_window(&game);
	mlx_loop_hook(game.mlx, walker_loop, &game);
	mlx_loop(game.mlx);
	init_game_window(&game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}

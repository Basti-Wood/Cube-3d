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

// static void	ft_swap(t_texture *a, t_texture *b)
// {
// 	t_texture	tmp;
//
// 	tmp = *a;
// 	*a = *b;
// 	*b = tmp;
// }

int	close_game(t_game *game)
{
	free_game_resources(game);
	exit(0);
	return (0);
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
	int	i;

	i = -1;
	while (++i < NUM_TEXTURES)
		game->texture[i].pixel_map = NULL;
	game->map.grid = NULL;
	game->img.ptr = NULL;
	game->win = NULL;
	game->mlx = NULL;
	if (init_map(game))
		return (1);
	load_textures(game);
	game->walker = init_walker(game);
	if (get_walker_start(game))
		return (1);
	if (move_walker(game))
		return (1);
	game->walker.first = game->walker.dir_set[game->walker.prev];
	game->skip_intro = false;
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
	game.present_num = -1;
	while (++game.present_num < NUM_TEXTURES)
	{
		init_presenter_window(&game);
		mlx_loop_hook(game.mlx, presenter_loop, &game);
		mlx_loop(game.mlx);
	}
	init_walker_window(&game);
	mlx_loop_hook(game.mlx, walker_loop, &game);
	mlx_loop(game.mlx);
	init_game_window(&game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}

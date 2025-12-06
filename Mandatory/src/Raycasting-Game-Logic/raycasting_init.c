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

#include "../../includes/cub3d.h"

void	load_textures(t_game *game)
{
	game->texture[0] = parse_xpm_file("texs/bluestone.xpm", game);
	game->texture[1] = parse_xpm_file("texs/greystone.xpm", game);
	game->texture[2] = parse_xpm_file("texs/redbrick.xpm", game);
	game->texture[3] = parse_xpm_file("texs/mossy.xpm", game);
}

void	load_textures_from_paths(t_game *game)
{
	game->texture[0] = parse_xpm_file(game->texture_paths[0], game);
	game->texture[1] = parse_xpm_file(game->texture_paths[1], game);
	game->texture[2] = parse_xpm_file(game->texture_paths[2], game);
	game->texture[3] = parse_xpm_file(game->texture_paths[3], game);
}

static void	init_helper(t_game *game)
{
	game->walker.first = game->walker.dir_set[game->walker.prev];
	game->skip_intro = false;
	init_hero_from_map(&game->hero, &game->map);
	game->hero.mini = false;
	game->mini_hero = game->hero;
	game->mini_hero.mini = true;
}

int	init_game_for_raycasting(t_game *game)
{
	game->img.ptr = NULL;
	game->win = NULL;
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		printf("Error: Failed to initialize MLX\n");
		return (1);
	}
	load_textures_from_paths(game);
	game->walker = init_walker(game);
	if (get_walker_start(game))
	{
		printf("Error: Failed to get walker start\n");
		return (1);
	}
	if (move_walker(game))
	{
		printf("Error: Failed to move walker\n");
		return (1);
	}
	init_helper(game);
	return (0);
}

int	start_game(t_game *game)
{
	if (init_game_for_raycasting(game))
	{
		printf("Failed to initialize game\n");
		return (1);
	}
	init_game_window(game);
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_loop(game->mlx);
	return (0);
}

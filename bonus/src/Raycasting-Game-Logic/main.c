/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstorck <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 15:22:40 by bstorck           #+#    #+#             */
/*   Updated: 2025/12/09 07:34:27 by bstorck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/game.h"

int	close_game(t_game *game)
{
	free_game_resources(game);
	exit(0);
	return (0);
}

static int	set_walker_start_tile(t_game *game)
{
	t_walker	*walker;

	walker = &game->walker;
	walker->pos.y = -1;
	while (++walker->pos.y < game->map.height)
	{
		walker->pos.x = -1;
		while (++walker->pos.x < game->map.width)
		{
			if (wall_collision(walker->pos.x, walker->pos.y, &game->map))
			{
				walker->start.x = walker->pos.x;
				walker->start.y = walker->pos.y;
				return (0);
			}
		}
	}
	printf("Error\nWalker: Could not retrieve start tile");
	return (1);
}

void	load_textures(t_game *game)
{
	game->texture[FLOOR] = parse_xpm_file("texs/greystone.xpm", game);
	game->texture[WALL] = parse_xpm_file("texs/redbrick.xpm", game);
	game->texture[DOOR] = parse_xpm_file("texs/door.xpm", game);
	game->texture[CEILING] = parse_xpm_file("texs/wood.xpm", game);
	game->texture[BARREL] = parse_xpm_file("texs/barrel.xpm", game);
	game->texture[PILLAR] = parse_xpm_file("texs/pillar.xpm", game);
	game->texture[LIGHT] = parse_xpm_file("texs/greenlight.xpm", game);
	game->texture[TREE_0] = parse_xpm_file("texs/tree_0.xpm", game);
	game->texture[TREE_1] = parse_xpm_file("texs/tree_1.xpm", game);
	game->texture[TREE_2] = parse_xpm_file("texs/tree_2.xpm", game);
	game->texture[TREE_3] = parse_xpm_file("texs/tree_3.xpm", game);
	game->texture[TREE_4] = parse_xpm_file("texs/tree_4.xpm", game);
}

int	init_game_resources(t_game *game)
{
	int	i;

	i = -1;
	while (++i < MAX_TEXTURES)
		game->texture[i].pixel_map = NULL;
	game->map.grid = NULL;
	game->img.ptr = NULL;
	game->win = NULL;
	game->mlx = NULL;
	if (init_map(game))
		return (1);
	load_textures(game);
	init_sprites(game);
	game->walker = init_walker();
	if (set_walker_start_tile(game))
		return (1);
	if (move_walker(game))
		return (1);
	game->walker.first = game->walker.dir_set[game->walker.prev];
	game->skip_intro = true;
	game->hero = init_hero(false);
	game->mini_hero = init_hero(true);
	game->last_check = get_current_time();
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
	set_dev_mode(&game.dev_mode);
	// game.present_num = -1;
	// while (++game.present_num < MAX_TEXTURES)
	// {
	// 	init_presenter_window(&game);
	// 	mlx_loop_hook(game.mlx, presenter_loop, &game);
	// 	mlx_loop(game.mlx);
	// }
	init_walker_window(&game);
	mlx_loop_hook(game.mlx, walker_loop, &game);
	mlx_loop(game.mlx);
	init_game_window(&game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}

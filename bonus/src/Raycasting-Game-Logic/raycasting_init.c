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

#include "../../includes/game.h"

// void	load_textures(t_game *game)
// {
// 	game->texture[0] = parse_xpm_file("texs/bluestone.xpm", game);
// 	game->texture[1] = parse_xpm_file("texs/greystone.xpm", game);
// 	game->texture[2] = parse_xpm_file("texs/redbrick.xpm", game);
// 	game->texture[3] = parse_xpm_file("texs/mossy.xpm", game);
// }

static void	init_helper(t_game *game)
{
	game->walker.first = game->walker.dir_set[game->walker.prev];
	game->skip_intro = false;
	init_hero_from_map(&game->hero, &game->map);
	game->hero.mini = false;
	game->mini_hero = game->hero;
	game->mini_hero.mini = true;
	game->last_check = get_current_time();
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

// static void	assign_sprite_textures(t_game *game)
// {
// 	int	i;
// 	int	j;
//
// 	i = 0;
// 	while (i < game->sprites.count)
// 	{
// 		game->sprites.sprites[i].texture =
//			&game->texture[game->sprites.sprites[i].type];
// 		i++;
// 	}
// 	i = 0;
// 	while (i < game->sprites.tree_count)
// 	{
// 		j = 0;
// 		while (j < NUM_ASPRITE_FRAMES)
// 		{
// 			game->sprites.trees[i].frames[j] = &game->asprite_texture[j];
// 			j++;
// 		}
// 		i++;
// 	}
// }

void	load_textures_from_paths(t_game *game)
{
	game->texture[FLOOR] = parse_xpm_file(game->texture_path[FLOOR], game);
	game->texture[WALL] = parse_xpm_file(game->texture_path[WALL], game);
	game->texture[DOOR] = parse_xpm_file(game->texture_path[DOOR], game);
	game->texture[CEILING] = parse_xpm_file(game->texture_path[CEILING], game);
	game->texture[BARREL] = parse_xpm_file(game->texture_path[BARREL], game);
	game->texture[PILLAR] = parse_xpm_file(game->texture_path[PILLAR], game);
	game->texture[LIGHT] = parse_xpm_file(game->texture_path[LIGHT], game);
	game->texture[TREE_0] = parse_xpm_file(game->texture_path[TREE_0], game);
	game->texture[TREE_1] = parse_xpm_file(game->texture_path[TREE_1], game);
	game->texture[TREE_2] = parse_xpm_file(game->texture_path[TREE_2], game);
	game->texture[TREE_3] = parse_xpm_file(game->texture_path[TREE_3], game);
	game->texture[TREE_4] = parse_xpm_file(game->texture_path[TREE_4], game);
}

int	init_game_for_raycasting(t_game *game)
{
	int	i;

	game->img.ptr = NULL;
	game->win = NULL;
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		printf("Error: Failed to initialize MLX\n");
		return (1);
	}
	i = -1;
	while (++i < MAX_TEXTURES)
		game->texture[i].pixel_map = NULL;
	load_textures_from_paths(game);
	if (init_doors(game))
		return (1);
	game->walker = init_walker();
	if (set_walker_start_tile(game))
		return (1);
	if (move_walker(game))
		return (1);
	init_helper(game);
	return (0);
}

int	start_game(t_game *game)
{
	if (init_game_for_raycasting(game))
	{
		printf("Failed to initialize game\n");
		free_game_resources(game);
		return (1);
	}
	init_game_window(game);
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_loop(game->mlx);
	return (0);
}

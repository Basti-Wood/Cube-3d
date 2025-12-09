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

static void	set_dev_mode(t_dev_mode *dev_mode)
{
	dev_mode->render_ceiling = true;
	dev_mode->render_floor = true;
	dev_mode->render_walls = true;
	dev_mode->render_map = true;
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
			if (collision(walker->pos.x, walker->pos.y, &game->map))
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
	// game->texture[4] = parse_xpm_file("texs/colorstone.xpm", game);
	// game->texture[5] = parse_xpm_file("texs/mossy.xpm", game);
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
	if (set_walker_start_tile(game))
		return (1);
	if (move_walker(game))
		return (1);
	game->walker.first = game->walker.dir_set[game->walker.prev];
	game->skip_intro = false;
	game->hero = init_hero(false, game);
	game->mini_hero = init_hero(true, game);
	game->last_check = get_current_time();
	set_dev_mode(&game->dev_mode);
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

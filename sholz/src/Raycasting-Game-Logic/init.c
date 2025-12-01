/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstorck <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 15:23:07 by bstorck           #+#    #+#             */
/*   Updated: 2025/11/21 15:23:11 by bstorck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Forward declarations */
int	key_press(int key, t_game *game);
int	key_release(int key, t_game *game);

t_hero	init_hero(bool mini, t_game *g)
{
	t_hero		h;

	if (mini == true)
		h.mini = true;
	h.pos.x = g->map.player.x + 0.5;
	h.pos.y = g->map.player.y + 0.5;
	h.probe.x = 0;
	h.probe.y = 0;
	// Set direction based on player_dir
	if (g->map.player_dir == 'N')
	{
		h.dir.x = 0;
		h.dir.y = -1;
		h.plane.x = 0.66 * (1.0 * WIN_WIDTH / WIN_HEIGHT);
		h.plane.y = 0;
	}
	else if (g->map.player_dir == 'S')
	{
		h.dir.x = 0;
		h.dir.y = 1;
		h.plane.x = -0.66 * (1.0 * WIN_WIDTH / WIN_HEIGHT);
		h.plane.y = 0;
	}
	else if (g->map.player_dir == 'E')
	{
		h.dir.x = 1;
		h.dir.y = 0;
		h.plane.x = 0;
		h.plane.y = 0.66 * (1.0 * WIN_WIDTH / WIN_HEIGHT);
	}
	else if (g->map.player_dir == 'W')
	{
		h.dir.x = -1;
		h.dir.y = 0;
		h.plane.x = 0;
		h.plane.y = -0.66 * (1.0 * WIN_WIDTH / WIN_HEIGHT);
	}
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

	(void)game;
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
	g->win = mlx_new_window(g->mlx, WIN_WIDTH, WIN_HEIGHT, "Picostein No D");
	g->img.img_ptr = mlx_new_image(g->mlx, WIN_WIDTH, WIN_HEIGHT);
	g->img.addr = mlx_get_data_addr(g->img.img_ptr, &g->img.bits_per_pixel,
		&g->img.line_length, &g->img.endian);
	g->img.width = WIN_WIDTH;
	g->img.height = WIN_HEIGHT;
	mlx_hook(g->win, 2, 1L << 0, key_press, g);
	mlx_hook(g->win, 3, 1L << 1, key_release, g);
	mlx_hook(g->win, WIN_X_BTN, 0, close_game, g);
}

void	init_intro_window(t_game *g)
{
	int	w_width = g->map.width * TILE_SIZE;
	int	w_height = g->map.height * TILE_SIZE;
	g->win = mlx_new_window(g->mlx, w_width, w_height, "Map Checker");
	g->img.img_ptr = mlx_new_image(g->mlx, w_width, w_height);
	g->img.addr = mlx_get_data_addr(g->img.img_ptr, &g->img.bits_per_pixel, 
		&g->img.line_length, &g->img.endian);
	g->img.width = w_width;
	g->img.height = w_height;
	mlx_hook(g->win, 2, 1L << 0, key_press, g);
	mlx_hook(g->win, 3, 1L << 1, key_release, g);
	mlx_hook(g->win, WIN_X_BTN, 0, close_game, g);
}

void	init_game(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->img.img_ptr = NULL;
	game->img.addr = NULL;
	game->keys.w = 0;
	game->keys.a = 0;
	game->keys.s = 0;
	game->keys.d = 0;
	game->keys.left = 0;
	game->keys.right = 0;
	game->skip_intro = false;
	game->display_map = false;
}

int	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		printf("Error: Failed to initialize MLX\n");
		return (0);
	}
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, WIN_TITLE);
	if (!game->win)
	{
		printf("Error: Failed to create window\n");
		return (0);
	}
	return (1);
}

int	init_image(t_game *game)
{
	game->img.img_ptr = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game->img.img_ptr)
	{
		printf("Error: Failed to create image\n");
		return (0);
	}
	game->img.addr = mlx_get_data_addr(game->img.img_ptr,
			&game->img.bits_per_pixel,
			&game->img.line_length,
			&game->img.endian);
	if (!game->img.addr)
	{
		printf("Error: Failed to get image address\n");
		return (0);
	}
	game->img.width = WIN_WIDTH;
	game->img.height = WIN_HEIGHT;
	return (1);
}

void	init_player(t_game *game)
{
	(void)game;
}

void	setup_hooks(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
	mlx_hook(game->win, 17, 0, close_game, game);
	mlx_loop_hook(game->mlx, game_loop, game);
}

int	close_game(t_game *game)
{
	int	i;
	int	j;

	if (game->img.img_ptr)
		mlx_destroy_image(game->mlx, game->img.img_ptr);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	i = -1;
	while (++i < 4)
	{
		if (game->texture[i].pixel_map)
		{
			j = -1;
			while (++j < game->texture[i].height)
				free(game->texture[i].pixel_map[j]);
			free(game->texture[i].pixel_map);
		}
	}
	free_config(&game->config);
	free_map(&game->map);
	exit(0);
	return (0);
}

void	init_game_logic(t_game *g)
{
	// Initialize game flags
	g->skip_intro = false;
	g->display_map = false;
	
	// Load textures from parsed config
	g->texture[0] = parse_xpm_file(g->config.north_tex, g);
	g->texture[1] = parse_xpm_file(g->config.south_tex, g);
	g->texture[2] = parse_xpm_file(g->config.west_tex, g);
	g->texture[3] = parse_xpm_file(g->config.east_tex, g);
	
	// Initialize walker for map validation (already done in parsing)
	g->walker = init_walker(g);
	
	// Initialize hero and mini_hero from parsed map data
	g->hero = init_hero(false, g);
	g->mini_hero = init_hero(true, g);
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


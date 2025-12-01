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

#include "../../includes/cub3d.h"
#include <stdbool.h>

/* Forward declarations */
int	key_press(int key, t_game *game);

int	old_close_game(t_game *game)
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
		j = -1;
		while (++j < game->texture[i].height)
			free(game->texture[i].pixel_map[j]);
		free(game->texture[i].pixel_map);
	}
	// j = -1;
	// while (++j < game->texture.height)
	// 	free(game->texture.pixel_map[j]);
	// free(game->texture.pixel_map);
	while (game->map.height--)
		free(game->map.grid[game->map.height]);
	free(game->map.grid);
	exit(0);
	return (0);
}

int	game_loop(t_game *game)
{
	// Process player movement based on keys
	game->hero.move_forward = game->keys.w;
	game->hero.move_backward = game->keys.s;
	game->hero.move_port = game->keys.a;
	game->hero.move_starboard = game->keys.d;
	game->hero.turn_sinistral = game->keys.left;
	game->hero.turn_dextral = game->keys.right;
	game->mini_hero.move_forward = game->keys.w;
	game->mini_hero.move_backward = game->keys.s;
	game->mini_hero.move_port = game->keys.a;
	game->mini_hero.move_starboard = game->keys.d;
	game->mini_hero.turn_sinistral = game->keys.left;
	game->mini_hero.turn_dextral = game->keys.right;

	// Update hero positions
	hero_action(&game->hero, &game->map);
	hero_action(&game->mini_hero, &game->map);
	
	// Render scene
	clear_image(game);
	draw_floor_and_ceiling(game);
	draw_walls(game);
	
	// Draw minimap if enabled
	if (game->display_map)
	{
		draw_map(false, game);
		draw_hero(false, game->mini_hero.pos, 0.15625 * TILE_SIZE, game);
		draw_radar(game);
	}
	
	mlx_put_image_to_window(game->mlx, game->win, game->img.img_ptr, 0, 0);
	return (0);
}

void	draw_texture(t_game *g)
{
	int			x;
	int			y;
	int			size;
	t_square	square;

	size = TEXEL_SIZE;
	y = -1;
	while (++y < g->texture->height)
	{
		// printf("\t%i < %i\n", y, g->texture.height);
		x = -1;
		while (++x < g->texture->width)
		{
			square.x = x * size;
			square.y = y * size;
			draw_filled_square(square, size, g->texture->pixel_map[y][x], g);
		}
	}
	// printf("\t%i\t%i\t%X\n", y, x, g->texture.pixel_map[y - 1][x - 1]);
}

int	presenter_loop(t_game *game)
{
	clear_image(game);
	draw_texture(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img_ptr, 0, 0);
	if (game->skip_intro)
	{
		game->skip_intro = false;
		mlx_destroy_image(game->mlx, game->img.img_ptr);
		mlx_destroy_window(game->mlx, game->win);
	}
	return (0);
}

void	init_presenter_window(t_game *g)
{
	int	w_width;
	int	w_height;

	w_width = g->texture->width * TEXEL_SIZE;
	w_height = g->texture->height * TEXEL_SIZE;
	g->win = mlx_new_window(g->mlx, w_width, w_height, "XPM Presenter");
	g->img.img_ptr = mlx_new_image(g->mlx, w_width, w_height);
	g->img.addr = mlx_get_data_addr(g->img.img_ptr, &g->img.bits_per_pixel, &g->img.line_length, &g->img.endian);
	// mlx_put_image_to_window(g->mlx, g->win, g->img, 0, 0);
	mlx_hook(g->win, 2, 1L << 0, key_press, g);
	mlx_hook(g->win, 3, 1L << 1, key_release, g);
	mlx_hook(g->win, WIN_X_BTN, 0, old_close_game, g);
}

// This main function is commented out because the actual main is in src/main.c
// This was the original raycasting standalone main - kept for reference

// void ft_swap(t_texture *a, t_texture *b)
// {
// 	t_texture tmp = *a;
// 	*a = *b;
// 	*b = tmp;
// }

// int	main(void)
// {
// 	// int		x, y;
// 	t_game	game;
//
// 	// parse_xpm_file("texs/redbrick.xpm", &game);
// 	// y = -1;
// 	// while (++y < game.texture.height)
// 	// {
// 	// 	// printf("\n%p\t", game.texture.pixel_map[y]);
// 	// 	printf("\n");
// 	// 	x = -1;
// 	// 	while (++x < game.texture.width)
// 	// 		printf("%X ", game.texture.pixel_map[y][x]);
// 	// }
// 	init_game(&game);
// 	init_presenter_window(&game);
// 	mlx_loop_hook(game.mlx, presenter_loop, &game);
// 	mlx_loop(game.mlx);
// 	ft_swap(&game.texture[0], &game.texture[1]);
// 	init_presenter_window(&game);
// 	mlx_loop_hook(game.mlx, presenter_loop, &game);
// 	mlx_loop(game.mlx);
// 	ft_swap(&game.texture[0], &game.texture[2]);
// 	init_presenter_window(&game);
// 	mlx_loop_hook(game.mlx, presenter_loop, &game);
// 	mlx_loop(game.mlx);
// 	ft_swap(&game.texture[0], &game.texture[3]);
// 	init_presenter_window(&game);
// 	mlx_loop_hook(game.mlx, presenter_loop, &game);
// 	mlx_loop(game.mlx);
// 	ft_swap(&game.texture[0], &game.texture[1]);
// 	ft_swap(&game.texture[1], &game.texture[2]);
// 	ft_swap(&game.texture[2], &game.texture[3]);
// 	init_intro_window(&game);
// 	mlx_loop_hook(game.mlx, intro_loop, &game);
// 	mlx_loop(game.mlx);
// 	init_game_window(&game);
// 	mlx_loop_hook(game.mlx, game_loop, &game);
// 	mlx_loop(game.mlx);
// 	return (0);
// }

// int	main(void)
// {
// 	t_game	game;
// 	char	*flag;
//
// 	if (argc == 2)
// 		flag = argv[1];
// 	else
// 		flag = "intro";
// 	init
// 	init_game(&game);
// 	init_intro(&game);
// 	hooks
// 	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
// 	mlx_hook(game.win, 3, 1L << 1, key_release, &game);
// 	mlx_hook(game.win, WIN_X_BTN, 0, close_game, &game);
// 	// check_wall_integrity(&game);
// 	mlx_loop_hook(game.mlx, intro_loop, &game);
// 	mlx_loop(game.mlx);
// 	// printf("\tfirst\t%i\t%i\n", game.walker.first.x, game.walker.first.y);
// 	// printf("\tlast\t%i\t%i\n\n", game.walker.last.x, game.walker.last.y);
// 	if ((game.walker.first.x + game.walker.last.x == 0) && (game.walker.first.y + game.walker.last.y == 0))
// 		close_game(&game);
// 	mlx_destroy_image(game.mlx, game.img);
// 	mlx_destroy_window(game.mlx, game.win);
// 	check_wall_integrity(&game);
// 	init_intro_window(&game);
// 	mlx_loop_hook(game.mlx, intro_loop, &game);
// 	mlx_loop(game.mlx);
// 	init_game_window(&game);
// 	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
// 	mlx_hook(game.win, 3, 1L << 1, key_release, &game);
// 	mlx_hook(game.win, WIN_X_BTN, 0, close_game, &game);
// 	draw loop
// 	mlx_loop_hook(game.mlx, game_loop, &game);
// 	mlx_loop(game.mlx);
// 	return (0);
// }

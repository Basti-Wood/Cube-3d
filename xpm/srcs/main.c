/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstorck <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 04:51:21 by bstorck           #+#    #+#             */
/*   Updated: 2025/11/28 04:51:23 by bstorck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/game.h"

int	close_game(t_game *game)
{
	int	y;

	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	// while (game->map_height--)
	// 	free(game->map[game->map_height]);
	// free(game->map);
	y = -1;
	while (++y < game->texture.height)
		free(game->texture.image_data[y]);
	free(game->texture.image_data);
	exit(0);
	return (0);
}

int	key_press(int key, t_game *game)
{
	if (key == KEY_ESC)
		close_game(game);
	return (0);
}

void	draw_filled_square(t_square square, int size, int color, t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < size)
			put_pixel(square.x + i, square.y + j, color, game);
	}
}

void	draw_image_data(t_game *game)
{
	int			x;
	int			y;
	t_square	square;

	y = -1;
	while (++y < game->texture.height)
	{
		// printf("\t%i < %i\n", y, game->texture.height);
		x = -1;
		while (++x < game->texture.width)
		{
			square.x = x * BLOCK_SIZE;
			square.y = y * BLOCK_SIZE;
			draw_filled_square(square, BLOCK_SIZE, game->texture.image_data[y][x], game);
		}
	}
	// printf("\t%i\t%i\t%X\n", y, x, game->texture.image_data[y - 1][x - 1]);
}

int	game_loop(t_game *game)
{
	// printf("\tspeed=%f\t", game->hero.move_speed);
	// printf("\tspeed=%f\n", game->mini_hero.move_speed);
	// relocate_hero(&game->hero, game->map);
	// relocate_hero(&game->mini_hero, game->map);
	clear_image(game);
	// draw_map(game);
	// draw_hero(game->mini_hero.pos.x, game->mini_hero.pos.y, 5, game);
	// draw_sonar(game);
	// draw_radar(game);
	// draw_floor_and_ceiling(game);
	// draw_walls(game);
	draw_image_data(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}

void	init_game_window(t_texture *texture, t_game *g)
{
	g->win = mlx_new_window(g->mlx, texture->width * BLOCK_SIZE, texture->height * BLOCK_SIZE, "XPM Presenter");
	g->img = mlx_new_image(g->mlx, texture->width * BLOCK_SIZE, texture->height * BLOCK_SIZE);
	g->data = mlx_get_data_addr(g->img, &g->bpp, &g->size_line, &g->endian);
	// mlx_put_image_to_window(g->mlx, g->win, g->img, 0, 0);
	mlx_hook(g->win, 2, 1L << 0, key_press, g);
	// mlx_hook(g->win, 3, 1L << 1, key_release, g);
	mlx_hook(g->win, WIN_X_BTN, 0, close_game, g);
}

void	init_game(t_game *g)
{
	// game->time = 0;
	// game->prev_time = 0;
	// g->skip_intro = true;
	// g->map_width = 30;
	// g->map_height = 30;
	// g->map = init_map(g->map_width, g->map_width);
	// g->c = init_wind_rose();
	// g->walker = init_walker(g);
	// if (get_start(g))
	// {
	// 	printf("Error\nUnknown error.\n");
	// 	close_game(g);
	// }
	// if (get_direction(g))
	// {
	// 	printf("Error\nUnknown error.\n");
	// 	close_game(g);
	// }
	// g->settings.speed_factor = 1;
	// g->level_of_speed = 0;
	// g->walker.first = g->walker.wind_rose[g->walker.prev];
	// g->hero = init_hero(false, g);
	// g->mini_hero = init_hero(true, g);
	// game->hero.ray = init_ray(&game->hero);
	// game->ray = game->hero.ray;
	g->mlx = mlx_init();
}

int	main(int argc, char **argv)
{
	// int			x;
	// int			y;
	// t_texture	texture;
	// t_square	square;
	t_game		game;

	if (argc != 2)
		return (1);
	parse_xpm_file(argv[1], &game.texture);
	// y = -1;
	// while (++y < game.texture.height)
	// {
	// 	// printf("\n%p\t", game.texture.image_data[y]);
	// 	printf("\n");
	// 	x = -1;
	// 	while (++x < game.texture.width)
	// 		printf("%X ", game.texture.image_data[y][x]);
	// }
	init_game(&game);
	init_game_window(&game.texture, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	// y = -1;
	// while (++y < game.texture.height)
	// 	free(game.texture.image_data[y]);
	// free(game.texture.image_data);
	// close_game(&game);
	return (0);
}

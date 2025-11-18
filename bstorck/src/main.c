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
	// int i = 0;
	while (game->map_height--)
	// {
		free(game->map[game->map_height]);
		// i++;
	// }
	free(game->map);
	exit(0);
	return (0);
}

int	game_loop(t_game *game)
{
	move_player(game->map, &game->player);
	move_player(game->map, &game->mini_player);
	clear_image(game);
	draw_map(game);
	draw_player(game);
	draw_radar(game);
	draw_floor_and_ceiling(game);
	draw_walls(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}

void	init_game(t_game *game)
{
	// game->time = 0;
	// game->prev_time = 0;
	game->map_width = 30;
	game->map_height = 30;
	game->map = init_map(game->map_width, game->map_width);
	game->player = init_player(false);
	game->mini_player = init_player(true);
	// game->player.ray = init_ray(&game->player);
	// game->ray = game->player.ray;
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, SCRN_WIDTH, SCRN_HEIGHT, "Game");
	game->img = mlx_new_image(game->mlx, SCRN_WIDTH, SCRN_HEIGHT);
	game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, &game->endian);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

int	main(void)
{
	t_game game;
	// init
	init_game(&game);
	if (i_walk_the_line(&game))
		close_game(&game);
	// hooks
	mlx_hook(game.win, 2, 1L<<0, key_press, &game);
	mlx_hook(game.win, 3, 1L<<1, key_release, &game);
	mlx_hook(game.win, WIN_X_BTN, 0, close_game, &game);
	// draw loop
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}

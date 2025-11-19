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

void	throw_error(int num_error, t_game *game)
{
	if (num_error == 99)
		printf("Error\nThe map must be closed/surrounded by walls.\n");
	else if (num_error == 1)
		printf("Error\nInvalid map.\n");
	else
		printf("Error\nUnknown error.\n");
	close_game(game);
}

int	game_loop(t_game *game)
{
	move_player(game->map, &game->player);
	move_player(game->map, &game->mini_player);
	clear_image(game);
	draw_map(game);
	// draw_player((game);
	draw_hero(game->mini_player.pos.x, game->mini_player.pos.y, 5, game);
	draw_radar(game);
	draw_floor_and_ceiling(game);
	draw_walls(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}

void	init_game(char *flag, t_game *g)
{
	// game->time = 0;
	// game->prev_time = 0;
	g->skip_intro = false;
	if (ft_strcmp(flag, "no-intro") == 0)
		g->skip_intro = true;
	g->map_width = 30;
	g->map_height = 30;
	g->map = init_map(g->map_width, g->map_width);
	g->player = init_player(false);
	g->mini_player = init_player(true);
	// game->player.ray = init_ray(&game->player);
	// game->ray = game->player.ray;
	g->mlx = mlx_init();
	g->win = mlx_new_window(g->mlx, SCRN_WIDTH, SCRN_HEIGHT, "Game");
	g->img = mlx_new_image(g->mlx, SCRN_WIDTH, SCRN_HEIGHT);
	g->data = mlx_get_data_addr(g->img, &g->bpp, &g->size_line, &g->endian);
	mlx_put_image_to_window(g->mlx, g->win, g->img, 0, 0);
}

int	main(int argc, char **argv)
{
	t_game	game;
	char	*flag;
	// init
	if (argc == 2)
		flag = argv[1];
	else
		flag = "intro";
	init_game(flag, &game);
	// i_walk_the_line(&game);
	// hooks
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game);
	mlx_hook(game.win, WIN_X_BTN, 0, close_game, &game);
	// draw loop
	i_walk_the_line(&game);
	// mlx_loop_hook(game.mlx, i_walk_the_line, &game);
	// mlx_loop(game.mlx);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}

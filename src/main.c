#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_game		game;

	if (argc < 2)
	{
		printf("Usage: ./cub3d <map.cub>\n");
		return (1);
	}
	init_game(&game);
	if (!parse_cub_file(argv[1], &game.config, &game.map))
	{
		printf("Error: Failed to parse map\n");
		return (1);
	}
	if (!is_valid_map(&game.map))
	{
		printf("Error: Invalid map\n");
		free_config(&game.config);
		free_map(&game.map);
		return (1);
	}
	if (!init_mlx(&game))
	{
		free_config(&game.config);
		free_map(&game.map);
		return (1);
	}
	if (!init_image(&game))
	{
		close_game(&game);
		return (1);
	}
	init_player(&game);
	setup_hooks(&game);
	mlx_loop(game.mlx);
	return (0);
}

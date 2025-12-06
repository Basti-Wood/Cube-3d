#include "../includes/cub3d.h"

int	close_game(t_game *game)
{
	free_game_resources(game);
	exit(0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game		game;

	if (argc < 2)
	{
		printf("Usage: ./cub3d <map.cub>\n");
		return (1);
	}
	if (!parse_cub_file(argv[1], &game))
	{
		printf("Error: Failed to parse map\n");
		return (1);
	}
	
	// Display parsed map information
	display_map(&game);
	
	// Start the raycasting game
	if (start_game(&game))
	{
		printf("Error: Failed to start game\n");
		free_texture_paths(&game);
		free_map(&game.map);
		return (1);
	}
	
	// Cleanup
	free_texture_paths(&game);
	free_map(&game.map);
	return (0);
}

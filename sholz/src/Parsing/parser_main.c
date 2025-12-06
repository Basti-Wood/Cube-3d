#include "../../includes/cub3d.h"

static int	open_and_validate_file(const char *filename)
{
	int	fd;

	if (!is_valid_filename(filename))
	{
		printf("Error: Invalid filename\n");
		return (-1);
	}
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		printf("Error: Cannot open file %s\n", filename);
		return (-1);
	}
	return (fd);
}

static int	parse_config_and_validate(int fd, t_game *game,
	char **first_map_line)
{
	int	result;

	result = parse_config_section(fd, game, first_map_line);
	if (result == -2 || !config_complete(game))
	{
		printf("Error: Incomplete configuration\n");
		if (*first_map_line)
			free(*first_map_line);
		return (0);
	}
	if (result == -1)
	{
		printf("Error: No map found in file\n");
		return (0);
	}
	return (1);
}

static int	setup_and_validate_map(int fd, char *first_line, t_game *game)
{
	if (!setup_map(fd, first_line, &game->map))
	{
		free_texture_paths(game);
		if (game->map.grid)
			free_map(&game->map);
		return (0);
	}
	return (1);
}

int	parse_cub_file(const char *filename, t_game *game)
{
	int		fd;
	char	*first_map_line;

	fd = open_and_validate_file(filename);
	if (fd < 0)
		return (0);
	init_game_for_parsing(game);
	if (!parse_config_and_validate(fd, game, &first_map_line))
	{
		close(fd);
		free_texture_paths(game);
		return (0);
	}
	if (!setup_and_validate_map(fd, first_map_line, game))
	{
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

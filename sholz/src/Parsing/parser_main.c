#include "../../includes/cub3d.h"

static FILE	*open_and_validate_file(const char *filename)
{
	FILE	*file;

	if (!is_valid_filename(filename))
	{
		printf("Error: Invalid filename\n");
		return (NULL);
	}
	file = fopen(filename, "r");
	if (!file)
	{
		printf("Error: Cannot open file %s\n", filename);
		return (NULL);
	}
	return (file);
}

static int	parse_config_and_validate(FILE *file, t_config *config)
{
	long	map_start_pos;

	map_start_pos = parse_config_section(file, config);
	if (map_start_pos == -2 || !config_complete(config))
	{
		printf("Error: Incomplete configuration\n");
		return (-2);
	}
	if (map_start_pos == -1)
	{
		printf("Error: No map found in file\n");
		return (-1);
	}
	return (map_start_pos);
}

static int	setup_and_validate_map(FILE *file, t_config *config, t_map *map,
		long map_start_pos)
{
	if (!setup_map(file, map, map_start_pos))
	{
		free_config(config);
		if (map->grid)
			free_map(map);
		return (0);
	}
	return (1);
}

int	parse_cub_file(const char *filename, t_config *config, t_map *map)
{
	FILE	*file;
	long	map_start_pos;

	file = open_and_validate_file(filename);
	if (!file)
		return (0);
	init_config(config);
	map_start_pos = parse_config_and_validate(file, config);
	if (map_start_pos < 0)
	{
		fclose(file);
		free_config(config);
		return (0);
	}
	if (!setup_and_validate_map(file, config, map, map_start_pos))
	{
		fclose(file);
		return (0);
	}
	fclose(file);
	return (1);
}

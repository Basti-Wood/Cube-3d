#include "../../includes/cub3d.h"

int	setup_map(FILE *file, t_map *map, long map_start_pos)
{
	int	map_height;

	map_height = count_map_lines(file, map_start_pos);
	if (map_height == 0)
	{
		printf("Error: Empty map\n");
		return (0);
	}
	map->grid = allocate_map(map_height);
	if (!map->grid)
	{
		printf("Error: Memory allocation failed for map\n");
		return (0);
	}
	if (!parse_map_section(file, map, map_start_pos))
	{
		printf("Error: Failed to parse map\n");
		return (0);
	}
	return (1);
}

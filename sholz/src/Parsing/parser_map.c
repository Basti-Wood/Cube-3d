#include "../../includes/cub3d.h"

static void	update_max_width(int *max_width, int current_len)
{
	if (current_len > *max_width)
		*max_width = current_len;
}

static int	process_map_line(t_map *map, char *line, int *i, int *max_width)
{
	int	current_len;

	map->grid[*i] = clean_map_line(line);
	free(line);
	if (!map->grid[*i])
		return (0);
	current_len = strlen(map->grid[*i]);
	update_max_width(max_width, current_len);
	(*i)++;
	return (1);
}

static int	read_map_lines(FILE *file, t_map *map, int *max_width)
{
	char	*line;
	int		i;

	i = 0;
	line = read_line(file);
	while (line != NULL)
	{
		if (!is_map_line(line))
		{
			free(line);
			line = read_line(file);
			continue ;
		}
		if (!process_map_line(map, line, &i, max_width))
			return (0);
		line = read_line(file);
	}
	return (i);
}

static int	validate_map(t_map *map)
{
	if (map->height == 0)
	{
		printf("Error: No map found\n");
		return (0);
	}
	find_player(map);
	if (map->player.x == -1 || map->player.y == -1)
	{
		printf("Error: No player position found in map\n");
		return (0);
	}
	return (1);
}

int	parse_map_section(FILE *file, t_map *map, long start_pos)
{
	int	max_width;
	int	height;

	fseek(file, start_pos, SEEK_SET);
	max_width = 0;
	height = read_map_lines(file, map, &max_width);
	if (height == 0)
		return (0);
	map->height = height;
	map->width = max_width;
	if (!validate_map(map))
		return (0);
	return (1);
}

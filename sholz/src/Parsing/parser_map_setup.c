#include "../../includes/cub3d.h"

static void	convert_spaces_to_zeros(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->grid[y][x] == (int)' ')
				map->grid[y][x] = (int)'0';
			x++;
		}
		y++;
	}
}

static int	validate_and_find_player(t_map *map)
{
	find_player(map);
	if (map->player.x == -1 || map->player.y == -1)
	{
		printf("Error: No player position found in map\n");
		return (0);
	}
	return (1);
}

static void	copy_temp_to_grid(char **temp_lines, t_map *map)
{
	int	i;

	i = 0;
	while (i < map->height)
	{
		copy_line_to_grid(temp_lines[i], map->grid[i]);
		i++;
	}
}

int	setup_map(int fd, char *first_line, t_map *map)
{
	char	**temp_lines;

	temp_lines = read_temp_lines(fd, first_line, &map->height, &map->width);
	if (!temp_lines || map->height == 0)
	{
		if (temp_lines)
			free(temp_lines);
		printf("Error: Empty map\n");
		return (0);
	}
	map->grid = allocate_map(map->height, map->width);
	if (!map->grid)
		return (free_temp_lines(temp_lines, map->height), 0);
	copy_temp_to_grid(temp_lines, map);
	free_temp_lines(temp_lines, map->height);
	if (!validate_and_find_player(map))
		return (0);
	if (!i_walk_the_line(map))
		return (0);
	convert_spaces_to_zeros(map);
	return (1);
}

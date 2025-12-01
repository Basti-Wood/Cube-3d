#include "../../includes/cub3d.h"

static int	is_player_char(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

static int	check_duplicate_player(t_map *map)
{
	if (map->player.x != -1)
	{
		printf("Error: Multiple player positions found\n");
		return (0);
	}
	return (1);
}

static void	set_player_position(t_map *map, int x, int y, char dir)
{
	map->player.x = x;
	map->player.y = y;
	map->player_dir = dir;
}

static void	search_row(t_map *map, int y)
{
	int	x;

	x = 0;
	while (x < map->width)
	{
		if (is_player_char((char)map->grid[y][x]))
		{
			if (check_duplicate_player(map))
				set_player_position(map, x, y, (char)map->grid[y][x]);
		}
		x++;
	}
}

void	find_player(t_map *map)
{
	int	y;

	map->player.x = -1;
	map->player.y = -1;
	map->player_dir = '\0';
	y = 0;
	while (y < map->height)
	{
		search_row(map, y);
		y++;
	}
	if (map->player.x != -1 && map->player.y != -1)
		map->grid[map->player.y][map->player.x] = (int)'0';
}

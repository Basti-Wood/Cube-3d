#include "../../includes/cub3d.h"

static int	get_cell(t_map *map, int x, int y)
{
	if (y < 0 || y >= map->height)
		return ((int) ' ');
	if (x < 0 || x >= map->width)
		return ((int) ' ');
	if (!map->grid[y])
		return ((int) ' ');
	return (map->grid[y][x]);
}

static int	is_walkable(int c)
{
	return (c == (int) '0' || c == (int) 'N'
		|| c == (int) 'S' || c == (int) 'E' || c == (int) 'W');
}

static int	check_cell_enclosed(t_map *map, int x, int y)
{
	int	cell;
	int	up;
	int	down;
	int	left;
	int	right;

	cell = get_cell(map, x, y);
	if (!is_walkable(cell))
		return (1);
	up = get_cell(map, x, y - 1);
	down = get_cell(map, x, y + 1);
	left = get_cell(map, x - 1, y);
	right = get_cell(map, x + 1, y);
	if (up == (int) ' ' || down == (int) ' '
		|| left == (int) ' ' || right == (int) ' ')
		return (0);
	return (1);
}

int	is_valid_map(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (!check_cell_enclosed(map, x, y))
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

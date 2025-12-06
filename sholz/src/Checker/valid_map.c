#include "../../includes/cub3d.h"

static int	get_cell(t_map *map, int x, int y)
{
	if (y < 0 || y >= map->height)
		return ((int)' ');
	if (x < 0 || x >= map->width)
		return ((int)' ');
	if (!map->grid)
		return ((int)' ');
	return (map->grid[y * map->width + x]);
}

static int	check_direction_x(t_map *map, int x, int y, int dx)
{
	int	nx;
	int	cell;

	nx = x + dx;
	while (nx >= 0 && nx < map->width)
	{
		cell = get_cell(map, nx, y);
		if (cell == 1)
			return (1);
		nx += dx;
	}
	return (0);
}

static int	check_direction_y(t_map *map, int x, int y, int dy)
{
	int	ny;
	int	cell;

	ny = y + dy;
	while (ny >= 0 && ny < map->height)
	{
		cell = get_cell(map, x, ny);
		if (cell == 1)
			return (1);
		ny += dy;
	}
	return (0);
}

static int	check_zero_enclosed(t_map *map, int x, int y)
{
	if (!check_direction_x(map, x, y, -1))
		return (0);
	if (!check_direction_x(map, x, y, 1))
		return (0);
	if (!check_direction_y(map, x, y, -1))
		return (0);
	if (!check_direction_y(map, x, y, 1))
		return (0);
	return (1);
}

static int	is_player_or_empty(int cell)
{
	return (cell == 0 || cell == (int)'N' || cell == (int)'S'
		|| cell == (int)'E' || cell == (int)'W');
}

int	is_valid_map(t_map *map)
{
	int	x;
	int	y;
	int	cell;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			cell = get_cell(map, x, y);
			if (is_player_or_empty(cell))
			{
				if (!check_zero_enclosed(map, x, y))
					return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

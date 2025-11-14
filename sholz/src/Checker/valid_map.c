#include "../../includes/cub3d.h"

static char	get_cell(t_map *map, int x, int y)
{
	int	row_len;

	if (y < 0 || y >= map->height)
		return (' ');
	if (x < 0)
		return (' ');
	if (!map->grid[y])
		return (' ');
	row_len = ft_strlen(map->grid[y]);
	if (x >= row_len)
		return (' ');
	return (map->grid[y][x]);
}

static int	is_walkable(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	check_cell_enclosed(t_map *map, int x, int y)
{
	char	cell;
	char	up;
	char	down;
	char	left;
	char	right;

	cell = get_cell(map, x, y);
	if (!is_walkable(cell))
		return (1);
	up = get_cell(map, x, y - 1);
	down = get_cell(map, x, y + 1);
	left = get_cell(map, x - 1, y);
	right = get_cell(map, x + 1, y);
	if (up == ' ' || down == ' ' || left == ' ' || right == ' ')
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

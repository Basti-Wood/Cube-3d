#include "../../includes/cub3d.h"

static int	probe_direction(int x, int y, t_map *map)
{
	if (x >= 0 && x < map->width && y >= 0 && y < map->height)
	{
		if (map->grid[y * map->width + x] == 1)
			return (1);
	}
	return (0);
}

static int	get_direction(t_walker *walker, t_map *map)
{
	t_square	dir;
	int			prev;
	int			i;

	i = 0;
	while (++i < 5)
	{
			dir = walker->dir_set[(walker->prev + i) % 4];
		if (probe_direction(walker->pos.x + dir.x, walker->pos.y + dir.y, map))
		{
			prev = (walker->prev + i + 2) % 4;
			walker->pos.x += dir.x;
			walker->pos.y += dir.y;
			return (prev);
		}
	}
	return (-1);
}

static int	get_start(t_walker *walker, t_map *map)
{
	walker->pos.y = -1;
	while (++walker->pos.y < map->height)
	{
		walker->pos.x = -1;
		while (++walker->pos.x < map->width)
		{
			if (map->grid[walker->pos.y * map->width + walker->pos.x] == 1)
			{
				walker->start.x = walker->pos.x;
				walker->start.y = walker->pos.y;
				return (0);
			}
		}
	}
	printf("Error: No wall found to start walker\n");
	return (1);
}

static void	init_walker_checker(t_walker *w)
{
	w->pos.x = 0;
	w->pos.y = 0;
	w->start.x = 0;
	w->start.y = 0;
	w->dir_set[0].x = -1;
	w->dir_set[0].y = 0;
	w->dir_set[1].x = 0;
	w->dir_set[1].y = -1;
	w->dir_set[2].x = 1;
	w->dir_set[2].y = 0;
	w->dir_set[3].x = 0;
	w->dir_set[3].y = 1;
	w->first.x = 0;
	w->first.y = 0;
	w->last.x = 0;
	w->last.y = 0;
	w->prev = 0;
}

int	i_walk_the_line(t_map *map)
{
	t_walker	w;
	int			i;

	init_walker_checker(&w);
	if (get_start(&w, map))
		return (0);
	i = 0;
	while (1)
	{
		w.prev = get_direction(&w, map);
		if (w.prev == -1)
		{
			printf("Error: Map is not closed\n");
			return (0);
		}
		if (!i)
				w.first = w.dir_set[w.prev];
		i++;
		w.last = w.dir_set[w.prev];
		if (w.pos.x == w.start.x && w.pos.y == w.start.y)
			break ;
	}
	if ((w.first.x + w.last.x == 0) && (w.first.y + w.last.y == 0))
	{
		printf("Error: Invalid map corner\n");
		return (0);
	}
	return (1);
}

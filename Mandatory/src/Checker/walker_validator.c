/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walker_validator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstorck <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 00:00:00 by bstorck           #+#    #+#             */
/*   Updated: 2025/12/06 00:00:00 by bstorck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static t_walker	init_validator_walker(void)
{
	t_walker	walker;

	walker.pos.x = 0;
	walker.pos.y = 0;
	walker.start.x = 0;
	walker.start.y = 0;
	walker.dir_set[0].x = -1;
	walker.dir_set[0].y = 0;
	walker.dir_set[1].x = 0;
	walker.dir_set[1].y = -1;
	walker.dir_set[2].x = 1;
	walker.dir_set[2].y = 0;
	walker.dir_set[3].x = 0;
	walker.dir_set[3].y = 1;
	walker.first.x = 0;
	walker.first.y = 0;
	walker.last.x = 0;
	walker.last.y = 0;
	walker.dir.x = 0;
	walker.dir.y = 0;
	walker.prev = 0;
	walker.first = walker.dir_set[walker.prev];
	return (walker);
}

static int	find_validator_walker_start(t_map *map, t_walker *walker)
{
	walker->pos.y = -1;
	while (++walker->pos.y < map->height)
	{
		walker->pos.x = -1;
		while (++walker->pos.x < map->width)
		{
			if (get_cell(map, walker->pos.x, walker->pos.y) == 1)
			{
				walker->start.x = walker->pos.x;
				walker->start.y = walker->pos.y;
				return (0);
			}
		}
	}
	return (1);
}

static int	is_valid_validator_move(t_map *map, t_walker *w)
{
	int	x;
	int	y;

	x = w->pos.x + w->dir.x;
	y = w->pos.y + w->dir.y;
	if (x >= 0 && x < map->width && y >= 0 && y < map->height)
		return (get_cell(map, x, y) == 1);
	return (0);
}

static int	move_validator_walker(t_map *map, t_walker *walker)
{
	int	i;

	i = 0;
	while (++i < 5)
	{
		walker->dir = walker->dir_set[(walker->prev + i) % 4];
		if (is_valid_validator_move(map, walker))
		{
			walker->prev = (walker->prev + i + 2) % 4;
			walker->pos.x += walker->dir.x;
			walker->pos.y += walker->dir.y;
			return (0);
		}
	}
	return (1);
}

int	validate_map_with_walker(t_map *map)
{
	t_walker	walker;
	int			steps;

	walker = init_validator_walker();
	if (find_validator_walker_start(map, &walker))
		return (0);
	if (move_validator_walker(map, &walker))
		return (0);
	walker.last = walker.dir_set[walker.prev];
	steps = 0;
	while (steps < map->width * map->height * 4)
	{
		if (move_validator_walker(map, &walker))
			return (0);
		if (walker.pos.x == walker.start.x && walker.pos.y == walker.start.y)
			return (1);
		steps++;
	}
	return (0);
}

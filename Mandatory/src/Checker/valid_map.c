/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstorck <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 00:14:56 by bstorck           #+#    #+#             */
/*   Updated: 2025/12/04 00:14:57 by bstorck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	get_cell(t_map *map, int x, int y)
{
	if (y < 0 || y >= map->height)
		return ((int) ' ');
	if (x < 0 || x >= map->width)
		return ((int) ' ');
	if (!map->grid)
		return ((int) ' ');
	return (map->grid[y * map->width + x]);
}

int	check_direction_x(t_map *map, int x, int y, int dx)
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

int	check_direction_y(t_map *map, int x, int y, int dy)
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

int	check_zero_enclosed(t_map *map, int x, int y)
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

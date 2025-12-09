/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstorck <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 00:14:56 by bstorck           #+#    #+#             */
/*   Updated: 2025/12/04 00:14:57 by bstorck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_player_or_empty(int cell)
{
	return (cell == 0 || cell == (int) 'N' || cell == (int) 'S'
		|| cell == (int) 'E' || cell == (int) 'W');
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

int	i_walk_the_line(t_map *map)
{
	if (!is_valid_map(map))
		return (0);
	return (validate_map_with_walker(map));
}

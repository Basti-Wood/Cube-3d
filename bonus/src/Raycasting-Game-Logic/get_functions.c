/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstorck <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 00:15:04 by bstorck           #+#    #+#             */
/*   Updated: 2025/12/09 07:33:38 by bstorck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/game.h"

int	get_fd(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("Error");
		return (-1);
	}
	return (fd);
}

t_square	get_offset(bool intro, t_game *game)
{
	t_square	offset;

	offset.x = 0;
	offset.y = 0;
	if (!intro)
	{
		offset.x = (game->img.width - game->map.node_size.x - 20);
		if (offset.x < 0 || game->img.width < offset.x)
			offset.x = 0;
		offset.y = 20;
	}
	return (offset);
}

t_door	*get_door(int x, int y, t_map *map)
{
	int	i;

	i = -1;
	while (++i < map->num_doors)
	{
		if (map->door[i].pos.x == x && map->door[i].pos.y == y)
			return (&map->door[i]);
	}
	return (NULL);
}

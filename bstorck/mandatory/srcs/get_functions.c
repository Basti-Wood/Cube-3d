/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstorck <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 00:15:04 by bstorck           #+#    #+#             */
/*   Updated: 2025/12/04 00:15:05 by bstorck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/game.h"

int	get_fd(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("Error\n");
		return (-1);
	}
	return (fd);
}

int	get_walker_start(t_game *game)
{
	t_walker	*walker;

	walker = &game->walker;
	walker->pos.y = -1;
	while (++walker->pos.y < game->map.height)
	{
		walker->pos.x = -1;
		while (++walker->pos.x < game->map.width)
		{
			if (collision(walker->pos.x, walker->pos.y, &game->map))
			{
				walker->start.x = walker->pos.x;
				walker->start.y = walker->pos.y;
				return (0);
			}
		}
	}
	printf("Error\nWalker: Could not retrieve start tile");
	return (1);
}

t_square	get_offset(bool intro, t_game *game)
{
	t_square	offset;

	offset.x = 0;
	offset.y = 0;
	if (!intro)
	{
		offset.x = (game->img.width - game->map.node_size.x) / 2;
		if (offset.x < 0)
			offset.x = 0;
		offset.y = (game->img.height - game->map.node_size.y) / 2;
		if (offset.y < 0)
			offset.y = 0;
	}
	return (offset);
}

void	set_node_size(t_game *game)
{
	t_map	*m;

	m = &game->map;
	m->node_size.x = MAX_NODE_WIDTH;
	m->node_size.y = MAX_NODE_HEIGHT;
	if (m->width > (m->height * game->img.aspect_ratio))
	{
		m->tile_size = m->node_size.x / m->width;
		m->node_size.x = m->tile_size * m->width;
		m->node_size.y = m->tile_size * m->height;
	}
	else
	{
		m->tile_size = m->node_size.y / m->height;
		m->node_size.x = m->tile_size * m->width;
		m->node_size.y = m->tile_size * m->height;
	}
}

// t_square	get_offset(bool intro, t_game *game)
// {
// 	t_square	offset;
//
// 	offset.x = 0;
// 	offset.y = 0;
// 	if (!intro)
// 	{
// 		offset.x = (game->img.width - (game->map.width * TILE_SIZE)) / 2;
// 		if (offset.x < 0)
// 			offset.x = 0;
// 		offset.y = (game->img.height - (game->map.height * TILE_SIZE)) / 2;
// 		if (offset.y < 0)
// 			offset.y = 0;
// 	}
// 	return (offset);
// }

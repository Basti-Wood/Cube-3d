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
	return (1);
}

t_square	get_offset(bool intro, t_game *game)
{
	t_square	offset;

	offset.x = 0;
	offset.y = 0;
	if (!intro)
	{
		offset.x = (game->img.width - (game->map.width * TILE_SIZE)) / 2;
		if (offset.x < 0)
			offset.x = 0;
		offset.y = (game->img.height - (game->map.height * TILE_SIZE)) / 2;
		if (offset.y < 0)
			offset.y = 0;
	}
	return (offset);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstorck <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 12:29:41 by bstorck           #+#    #+#             */
/*   Updated: 2025/12/18 12:29:44 by bstorck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/game.h"

static void	init_door(int x, int y, t_door *door)
{
	door->pos.x = x;
	door->pos.y = y;
	door->state = CLOSED;
	door->interrupt = false;
	door->animation_start = 0;
	door->counter = 0;
	door->last_check = get_current_time();
	door->last_opened = 0;
}

int	init_doors(t_game *game)
{
	int			x;
	int			y;
	int			i;

	i = -1;
	y = -1;
	while (++y < game->map.height)
	{
		x = -1;
		while (++x < game->map.width)
		{
			if (game->map.grid[y * game->map.width + x] == DOOR)
			{
				i++;
				if (i == MAX_DOORS)
				{
					printf("Error: Number of doors exceeds threshold\n");
					return (1);
				}
				init_door(x, y, &game->map.door[i]);
			}
		}
	}
	game->map.num_doors = i + 1;
	return (0);
}

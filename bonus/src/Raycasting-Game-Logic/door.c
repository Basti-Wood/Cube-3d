/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstorck <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 07:32:20 by bstorck           #+#    #+#             */
/*   Updated: 2025/12/09 07:32:22 by bstorck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/game.h"

void	set_door_counter(t_door *door, t_map *map)
{
	if (door->state == CLOSED)
		door->counter = 0;
	if (get_current_time() > (door->last_check + 21))
	{
		door->last_check = get_current_time();
		if (door->interrupt)
			door->counter = 1 - door->counter;
		else
			door->counter += 1.0
				* (get_current_time() - door->animation_start) / STEP_SIZE;
		door->interrupt = false;
		if (door->counter >= 1)
		{
			door->counter = 0;
			door->state = door->state + 1;
			if (door->state == OPEN)
			{
				door->last_opened = get_current_time();
				map->grid[door->pos.y * map->width + door->pos.x] = 0;
			}
		}
	}
}

static void	open_door(t_door *door)
{
	door->state = OPENING;
	door->animation_start = get_current_time();
}

static void	close_door(t_hero *hero, t_door *door, t_map *map)
{
	map->grid[door->pos.y * map->width + door->pos.x] = 2;
	if (hero_sonar(hero, map))
	{
		map->grid[door->pos.y * map->width + door->pos.x] = 0;
		door->state = OPEN;
	}
	else
	{
		door->state = CLOSING;
		door->animation_start = get_current_time();
	}
}

void	handle_door(t_hero *hero, t_map *map)
{
	t_door	*door;
	int		x;
	int		y;

	hero->probe = hero->pos;
	x = (int)hero->pos.x + round(hero->dir.x);
	y = (int)hero->pos.y + round(hero->dir.y);
	door = get_door(x, y, map);
	if (door != NULL)
	{
		if (door->state == OPENING || door->state == CLOSING)
			door->interrupt = true;
		if (door->state == OPEN || door->state == OPENING)
			close_door(hero, door, map);
		else
			open_door(door);
	}
}

void	reset_doors(t_hero *hero, t_map *map)
{
	int		i;

	i = -1;
	while (++i < map->num_doors)
	{
		if (map->door[i].state == OPEN)
		{
			if (get_current_time() > (map->door[i].last_opened + CLOSE_AFTER))
				close_door(hero, &map->door[i], map);
		}
	}
}

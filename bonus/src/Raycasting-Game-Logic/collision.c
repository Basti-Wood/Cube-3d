/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstorck <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 09:02:49 by bstorck           #+#    #+#             */
/*   Updated: 2025/12/09 07:31:38 by bstorck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/game.h"

bool	wall_collision(int x, int y, t_map *map)
{
	return (map->grid[y * map->width + x] != 0);
}

bool	sprite_collision(t_vector pos, double collision_radius, t_map *map)
{
	int	i;

	i = map->num_sprites;
	while (i--)
		if (fabs(pos.x - map->sprite[i].pos.x) <= collision_radius)
			if (fabs(pos.y - map->sprite[i].pos.y) <= collision_radius)
				if (map->sprite[i].impermeable)
					return (true);
	return (false);
}

static double	get_pulse_distance(t_vector start, t_vector pulse, double dir)
{
	return (fabs((pulse.y - start.y) / sin(dir)));
}

static t_vector	sonar_pulse(double dir, t_hero *hero)
{
	t_vector	start;
	t_vector	pulse;
	double		collision_radius;

	collision_radius = hero->collision_radius * BLOCK_SIZE;
	pulse.x = hero->probe.x * BLOCK_SIZE;
	pulse.y = hero->probe.y * BLOCK_SIZE;
	start.x = pulse.x;
	start.y = pulse.y;
	while (get_pulse_distance(start, pulse, dir) <= collision_radius)
	{
		pulse.x += cos(dir);
		pulse.y += sin(dir);
		if ((pulse.x < -10000 || 10000 < pulse.x)
			|| (pulse.y < -10000 || 10000 < pulse.y))
			break ;
	}
	pulse.x /= BLOCK_SIZE;
	pulse.y /= BLOCK_SIZE;
	return (pulse);
}

bool	hero_sonar(t_hero *hero, t_map *map)
{
	t_vector	tmp_pos;
	double		dir;
	double		delta_dir;
	int			i;

	dir = atan2(fabs(hero->dir.y), fabs(hero->dir.x));
	delta_dir = PI / 45;
	i = -1;
	while (++i < 90)
	{
		tmp_pos = sonar_pulse(dir, hero);
		if (wall_collision((int)(tmp_pos.x), (int)(tmp_pos.y), map))
			return (true);
		if (sprite_collision(tmp_pos, hero->collision_radius, map))
			return (true);
		dir += delta_dir;
	}
	return (false);
}

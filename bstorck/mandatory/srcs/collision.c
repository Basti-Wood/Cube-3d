/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstorck <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 09:02:49 by bstorck           #+#    #+#             */
/*   Updated: 2025/12/04 00:14:04 by bstorck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/game.h"

bool	collision(int x, int y, t_map *map)
{
	return (map->grid[y * map->width + x] == 1);
}

double	pulse_distance(t_vector start, t_vector pulse, double dir)
{
	return (fabs((pulse.y - start.y) / sin(dir)));
}

t_vector	sonar_pulse(double dir, t_hero *hero)
{
	t_vector	pulse;
	t_vector	start;

	pulse.x = hero->probe.x * BLOCK_SIZE;
	pulse.y = hero->probe.y * BLOCK_SIZE;
	start.x = pulse.x;
	start.y = pulse.y;
	while (pulse_distance(start, pulse, dir) <= hero->collision_radius)
	{
		pulse.x += cos(dir);
		pulse.y += sin(dir);
	}
	return (pulse);
}

int	hero_sonar(t_hero *hero, t_map *map)
{
	t_vector	tmp_pos;
	double		dir;
	double		delta_dir;
	int			col;
	int			i;

	dir = atan2(hero->dir.y, hero->dir.x);
	delta_dir = PI / 45;
	col = 0;
	i = -1;
	while (++i < 90)
	{
		tmp_pos = sonar_pulse(dir, hero);
		tmp_pos.x /= BLOCK_SIZE;
		tmp_pos.y /= BLOCK_SIZE;
		col += collision((int)(tmp_pos.x), (int)(tmp_pos.y), map);
		dir += delta_dir;
	}
	return (col);
}

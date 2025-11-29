/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstorck <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 09:02:49 by bstorck           #+#    #+#             */
/*   Updated: 2025/11/25 09:02:50 by bstorck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/game.h"

bool	collision(int x, int y, int **map)
{
	// int	x = rx / BLOCK_SIZE;
	// printf("\tX = %i", x);
	// int	y = ry / BLOCK_SIZE;
	// printf("\tY = %i\n", y);
	if (map[y][x] > 0)
		return (true);
	return (false);
}

double	pulse_distance(t_vector start, t_vector pulse, double dir)
{
	// printf("\theavy\t%f\n", sqrt(pow((pulse.x - start.x), 2) + pow((pulse.y - start.y), 2)));
	// printf("\tcos\t%f\n", fabs((pulse.x - start.x) / cos(dir)));
	// printf("\tsin\t%f\n\n", fabs((pulse.y - start.y) / sin(dir)));
	// double	c = fabs((pulse.x - start.x) / cos(dir));
	// double	s = fabs((pulse.y - start.y) / sin(dir));
	// printf("\tcos\t%f\n", c);
	// printf("\tsin\t%f\n\n", s);
	// double d = fabs(c - s);
	// if (d == 1)
		// printf("\n\t\t\t\tDING!\n");
	// return (sqrt(pow((pulse.x - start.x), 2) + pow((pulse.y - start.y), 2)));
	// return (fabs((pulse.x - start.x) / cos(dir)));
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
		// printf("\tpulse=%f\n", sqrt(powf((pulse.x - start.x), 2) +  powf((pulse.y - start.y), 2)));
		pulse.x += cos(dir);
		pulse.y += sin(dir);
	}
	// printf("\tx=%f\ty=%f\n", pulse.x, pulse.y);
	return (pulse);
}

int	hero_sonar(t_hero *hero, int **map)
{
	t_vector	tmp_pos;
	double		dir;
	double		delta_dir;
	int			col;
	int			i;

	// hero = &game->mini_hero;
	dir = atan2(hero->dir.y, hero->dir.x);
	delta_dir = PI / 90;//hero->fov / FRM_WIDTH;
	col = 0;
	i = -1;
	while (++i < 2 * PI / (PI / 90))
	{
		tmp_pos = sonar_pulse(dir, hero);
		tmp_pos.x /= BLOCK_SIZE;
		tmp_pos.y /= BLOCK_SIZE;
		col += collision((int)(tmp_pos.x), (int)(tmp_pos.y), map);
		dir += delta_dir;
	}
	return (col);
}

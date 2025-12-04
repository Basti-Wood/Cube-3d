/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstorck <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 09:02:21 by bstorck           #+#    #+#             */
/*   Updated: 2025/11/25 09:02:26 by bstorck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/game.h"

void	turn_hero(double dir_x, double plane_x, t_hero *h)
{
	double	speed;

	speed = h->turn_speed;
	if (h->turn_sinistral)
	{
		h->dir.x = dir_x * cos(-speed) - h->dir.y * sin(-speed);
		h->plane.x = plane_x * cos(-speed) - h->plane.y * sin(-speed);
		h->dir.y = dir_x * sin(-speed) + h->dir.y * cos(-speed);
		h->plane.y = plane_x * sin(-speed) + h->plane.y * cos(-speed);
	}
	else if (h->turn_dextral)
	{
		h->dir.x = dir_x * cos(speed) - h->dir.y * sin(speed);
		h->plane.x = plane_x * cos(speed) - h->plane.y * sin(speed);
		h->dir.y = dir_x * sin(speed) + h->dir.y * cos(speed);
		h->plane.y = plane_x * sin(speed) + h->plane.y * cos(speed);
	}
}

void	move_hero(t_hero *h, double move_x, double move_y, int **map)
{
	double		speed;
	t_vector	new_pos;

	speed = h->move_speed;
	if (h->axes_of_travel >= 2)
		speed /= sqrt(2);
	h->probe = h->pos;
	h->probe.x = h->pos.x + move_x * speed;
	if (hero_sonar(h, map) == 0)
		new_pos.x = h->probe.x;
	else
		new_pos.x = h->pos.x - move_x / 100000;
	h->probe = h->pos;
	h->probe.y = h->pos.y + move_y * speed;
	if (hero_sonar(h, map) == 0)
		new_pos.y = h->probe.y;
	else
		new_pos.y = h->pos.y - move_y / 100000;
	h->pos = new_pos;
}

void	hero_action(t_hero *hero, int **map)
{
	double	cos_dir;
	double	sin_dir;

	cos_dir = cos(atan2(hero->dir.y, hero->dir.x));
	sin_dir = sin(atan2(hero->dir.y, hero->dir.x));
	if (hero->move_forward)
		move_hero(hero, cos_dir, sin_dir, map);
	if (hero->move_backward)
		move_hero(hero, -cos_dir, -sin_dir, map);
	if (hero->move_port)
		move_hero(hero, +sin_dir, -cos_dir, map);
	if (hero->move_starboard)
		move_hero(hero, -sin_dir, +cos_dir, map);
	if (hero->turn_sinistral || hero->turn_dextral)
		turn_hero(hero->dir.x, hero->plane.x, hero);
}

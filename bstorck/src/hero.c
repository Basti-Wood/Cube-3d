/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hero.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstorck <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 15:23:13 by bstorck           #+#    #+#             */
/*   Updated: 2025/11/21 15:23:15 by bstorck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"

t_hero	init_hero(bool mini)
{
	t_hero		h;
	double		dir_len;
	double		plane_len;

	if (mini == true)
		h.mini = true;
	h.pos.x = 11;
	h.pos.y = 28;
	h.dir.x = 0;
	h.dir.y = -1;
	h.plane.x = 1;
	h.plane.y = 0;
	h.plane.x = 1;
	h.fov = 2 * atan(fabs(h.plane.x + h.plane.y) / fabs(h.dir.x + h.dir.y));
	h.scan_x = 0;
	h.move_forward = false;
	h.move_backward = false;
	h.move_port = false;
	h.move_starboard = false;
	h.move_speed = (double)1 / 30;
	h.turn_sinistral = false;
	h.turn_dextral = false;
	h.turn_speed = PI / 100;
	return (h);
}

	// dir_len = fabs(h.dir.x + h.dir.y);
	// plane_len = fabs(h.plane.x + h.plane.y);
	// hero.fov = 2 * atan(plane_len / dir_len);

void	turn_hero(double dir_x, double plane_x, t_hero *h)
{
	if (h->turn_sinistral)
	{
		h->dir.x = dir_x * cos(-PI / 100) - h->dir.y * sin(-PI / 100);
		h->plane.x = plane_x * cos(-PI / 100) - h->plane.y * sin(-PI / 100);
		h->dir.y = dir_x * sin(-PI / 100) + h->dir.y * cos(-PI / 100);
		h->plane.y = plane_x * sin(-PI / 100) + h->plane.y * cos(-PI / 100);
	}
	if (h->turn_dextral)
	{
		h->dir.x = dir_x * cos(PI / 100) - h->dir.y * sin(PI / 100);
		h->plane.x = plane_x * cos(PI / 100) - h->plane.y * sin(PI / 100);
		h->dir.y = dir_x * sin(PI / 100) + h->dir.y * cos(PI / 100);
		h->plane.y = plane_x * sin(PI / 100) + h->plane.y * cos(PI / 100);
	}
}

t_vector	move_longitudal(t_hero *h)
{
	t_vector	tmp_pos;

	if (h->move_forward)
	{
		tmp_pos.x = h->pos.x + cos(atan2(h->dir.y, h->dir.x)) * h->move_speed;
		tmp_pos.y = h->pos.y + sin(atan2(h->dir.y, h->dir.x)) * h->move_speed;
	}
	if (h->move_backward)
	{
		tmp_pos.x = h->pos.x - cos(atan2(h->dir.y, h->dir.x)) * h->move_speed;
		tmp_pos.y = h->pos.y - sin(atan2(h->dir.y, h->dir.x)) * h->move_speed;
	}
	return (tmp_pos);
}

// void	move_longitudal(int **map, t_hero *h)
// {
// 	double	tmp_x;
// 	double	tmp_y;
//
// 	tmp_x = h->pos.x;
// 	tmp_y = h->pos.y;
// 	if (h->move_forward)
// 	{
// 		tmp_x += cos(atan2(h->dir.y, h->dir.x)) * h->move_speed * 15;
// 		tmp_y += sin(atan2(h->dir.y, h->dir.x)) * h->move_speed * 15;
// 		if (!collision((int)tmp_x, (int)tmp_y, map))
// 		{
// 			h->pos.x += cos(atan2(h->dir.y, h->dir.x)) * h->move_speed;
// 			h->pos.y += sin(atan2(h->dir.y, h->dir.x)) * h->move_speed;
// 		}
// 	}
// 	if (h->move_backward)
// 	{
// 		tmp_x -= cos(atan2(h->dir.y, h->dir.x)) * h->move_speed * 15;
// 		tmp_y -= sin(atan2(h->dir.y, h->dir.x)) * h->move_speed * 15;
// 		if (!collision((int)tmp_x, (int)tmp_y, map))
// 		{
// 			h->pos.x -= cos(atan2(h->dir.y, h->dir.x)) * h->move_speed;
// 			h->pos.y -= sin(atan2(h->dir.y, h->dir.x)) * h->move_speed;
// 		}
// 	}
// }

t_vector	move_lateral(t_hero *h)
{
	t_vector	tmp_pos;

	if (h->move_port)
	{
		tmp_pos.x = h->pos.x + sin(atan2(h->dir.y, h->dir.x)) * h->move_speed;
		tmp_pos.y = h->pos.y - cos(atan2(h->dir.y, h->dir.x)) * h->move_speed;
	}
	if (h->move_starboard)
	{
		tmp_pos.x = h->pos.x - sin(atan2(h->dir.y, h->dir.x)) * h->move_speed;
		tmp_pos.y = h->pos.y + cos(atan2(h->dir.y, h->dir.x)) * h->move_speed;
	}
	return (tmp_pos);
}

// void	move_lateral(int **map, t_hero *h)
// {
// 	double	tmp_x;
// 	double	tmp_y;
//
// 	tmp_x = h->pos.x;
// 	tmp_y = h->pos.y;
// 	if (h->move_port)
// 	{
// 		tmp_x += sin(atan2(h->dir.y, h->dir.x)) * h->move_speed * 15;
// 		tmp_y -= cos(atan2(h->dir.y, h->dir.x)) * h->move_speed * 15;
// 		if (!collision((int)tmp_x, (int)tmp_y, map))
// 		{
// 			h->pos.x += sin(atan2(h->dir.y, h->dir.x)) * h->move_speed;
// 			h->pos.y -= cos(atan2(h->dir.y, h->dir.x)) * h->move_speed;
// 		}
// 	}
// 	if (h->move_starboard)
// 	{
// 		tmp_x -= sin(atan2(h->dir.y, h->dir.x)) * h->move_speed * 15;
// 		tmp_y += cos(atan2(h->dir.y, h->dir.x)) * h->move_speed * 15;
// 		if (!collision((int)tmp_x, (int)tmp_y, map))
// 		{
// 			h->pos.x -= sin(atan2(h->dir.y, h->dir.x)) * h->move_speed;
// 			h->pos.y += cos(atan2(h->dir.y, h->dir.x)) * h->move_speed;
// 		}
// 	}
// }

void	move_hero(int **map, t_hero *hero)
{
	t_vector	tmp_pos;

	if (hero->turn_sinistral || hero->turn_dextral)
		turn_hero(hero->dir.x, hero->plane.x, hero);
	// if (hero->move_forward || hero->move_backward)
		// move_longitudal(map, hero);
	// if (hero->move_port || hero->move_starboard)
		// move_lateral(map, hero);
	if (hero->move_forward || hero->move_backward)
		tmp_pos = move_longitudal(hero);
	if (hero->move_port || hero->move_starboard)
		tmp_pos = move_lateral(hero);
	if ((!collision((int)tmp_pos.x, (int)tmp_pos.y, map)))
	{
		hero->pos.x = tmp_pos.x;
		hero->pos.y = tmp_pos.y;
	}
}

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
#include <math.h>
#include <stdbool.h>

t_hero	init_hero(bool mini, t_game *g)
{
	t_hero		h;

	if (mini == true)
		h.mini = true;
	h.pos.x = 11;
	h.pos.y = 28;
	h.probe.x = 0;
	h.probe.y = 0;
	h.dir.x = 0;
	h.dir.y = -1;
	h.plane.x = 1;
	h.plane.y = 0;
	h.scan_x = 0;
	h.fov = 2 * atan(fabs(h.plane.x + h.plane.y) / fabs(h.dir.x + h.dir.y));
	h.move_forward = false;
	h.move_backward = false;
	h.move_port = false;
	h.move_starboard = false;
	h.move_speed = sqrt(2) / 100;
	h.turn_sinistral = false;
	h.turn_dextral = false;
	h.turn_speed = PI / 200;
	h.axes_of_travel = 0;
	h.collision_radius = 5;
	return (h);
}

	// dir_len = fabs(h.dir.x + h.dir.y);
	// plane_len = fabs(h.plane.x + h.plane.y);
	// hero.fov = 2 * atan(plane_len / dir_len);

void	turn_hero(double dir_x, double plane_x, t_hero *h)
{
	if (h->turn_sinistral)
	{
		h->dir.x = dir_x * cos(-h->turn_speed) - h->dir.y * sin(-h->turn_speed);
		h->plane.x = plane_x * cos(-h->turn_speed) - h->plane.y * sin(-h->turn_speed);
		h->dir.y = dir_x * sin(-h->turn_speed) + h->dir.y * cos(-h->turn_speed);
		h->plane.y = plane_x * sin(-h->turn_speed) + h->plane.y * cos(-h->turn_speed);
	}
	if (h->turn_dextral)
	{
		h->dir.x = dir_x * cos(h->turn_speed) - h->dir.y * sin(h->turn_speed);
		h->plane.x = plane_x * cos(h->turn_speed) - h->plane.y * sin(h->turn_speed);
		h->dir.y = dir_x * sin(h->turn_speed) + h->dir.y * cos(h->turn_speed);
		h->plane.y = plane_x * sin(h->turn_speed) + h->plane.y * cos(h->turn_speed);
	}
}

t_vector	move_longitudal(t_hero *h, bool probe)
{
	t_vector	new_pos;
	t_vector	tmp_pos;
	double		speed;

	tmp_pos = h->pos;
	if (probe)
	// {
		tmp_pos = h->probe;
		// speed = h->probe_speed;
	// }
	speed = h->move_speed;
	if (h->axes_of_travel >= 2)
		speed /= sqrt(2);
	// if (!h->mini)
	// {
	// // 	printf("\tmini-hero");
	// // else
	// // 	printf("\t\thero");
	// printf("\taxes=%i\t", h->axes_of_travel);
	// printf("\tspeed=%f\t\n", speed);
	// }
	if (h->move_forward)
	{
		new_pos.x = tmp_pos.x + cos(atan2(h->dir.y, h->dir.x)) * speed;
		// printf("\tx\t%f\n", new_pos.x);
		new_pos.y = tmp_pos.y + sin(atan2(h->dir.y, h->dir.x)) * speed;
		// printf("\ty\t%f\n", new_pos.y);
	}
	if (h->move_backward)
	{
		new_pos.x = tmp_pos.x - cos(atan2(h->dir.y, h->dir.x)) * speed;
		// printf("\tx\t%f\n", new_pos.x);
		new_pos.y = tmp_pos.y - sin(atan2(h->dir.y, h->dir.x)) * speed;
		// printf("\ty\t%f\n", new_pos.y);
	}
	return (new_pos);
}

// int	probe_longitudal(t_hero *hero, int **map)
// {
// 	int			col;
// 	int			i;
//
// 	col = 0;
// 	i = -1;
// 	while (++i < 4)
// 	{
// 		hero->probe = hero->pos;
// 		// printf("\n\n\twind_rose_x\t%i\twind_rose_y\t%i\n", hero->c->wind_rose[i].x, hero->c->wind_rose[i].y);
// 		// printf("\t%i:\tLONG-pos_x\t%f\tLONG-pos_y\t%f\n", i, hero->probe.x, hero->probe.y);
// 		hero->probe.x = hero->pos.x + (double)hero->c->wind_rose[i].x / 3;
// 		hero->probe.y = hero->pos.y + (double)hero->c->wind_rose[i].y / 3;
// 		// printf("\t%i:\tLONG-pos_x\t%f\tLONG-pos_y\t%f", i, hero->probe.x, hero->probe.y);
// 		hero->probe = move_longitudal(hero, true);
// 		col += collision((int)hero->probe.x, (int)hero->probe.y, map);
// 		// printf("\tlong-col\t%i\n\n", col);
// 	}
// 	return (col);
// }

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

t_vector	move_lateral(t_hero *h, bool probe)
{
	t_vector	new_pos;
	t_vector	tmp_pos;
	double		speed;

	tmp_pos = h->pos;
	if (probe)
	// {
		tmp_pos = h->probe;
		// speed = h->probe_speed;
	// }
	speed = h->move_speed;
		if (h->axes_of_travel >= 2)
		speed /= sqrt(2);
	// if (!h->mini)
	// {
	// // 	printf("\tmini-hero");
	// // else
	// // 	printf("\t\thero");
	// printf("\taxes=%i\t", h->axes_of_travel);
	// printf("\tspeed=%f\t\n", speed);
	// }
	if (h->move_port)
	{
		new_pos.x = tmp_pos.x + sin(atan2(h->dir.y, h->dir.x)) * speed;
		// printf("\tx\t%f\n", new_pos.x);
		new_pos.y = tmp_pos.y - cos(atan2(h->dir.y, h->dir.x)) * speed;
		// printf("\ty\t%f\n", new_pos.y);
	}
	if (h->move_starboard)
	{
		new_pos.x = tmp_pos.x - sin(atan2(h->dir.y, h->dir.x)) * speed;
		// printf("\tx\t%f\n", new_pos.x);
		new_pos.y = tmp_pos.y + cos(atan2(h->dir.y, h->dir.x)) * speed;
		// printf("\ty\t%f\n", new_pos.y);
	}
	return (new_pos);
}

// int	probe_lateral(t_hero *hero, int **map)
// {
// 	int			col;
// 	int			i;
//
// 	col = 0;
// 	i = -1;
// 	while (++i < 4)
// 	{
// 		hero->probe = hero->pos;
// 		// printf("\n\n\twind_rose_x\t%i\twind_rose_y\t%i\n", hero->c->wind_rose[i].x, hero->c->wind_rose[i].y);
// 		// printf("\t%i:\tLAT-pos_x\t%f\tLAT-pos_y\t%f\n", i, hero->probe.x, hero->probe.y);
// 		hero->probe.x = (hero->pos.x + (double)hero->c->wind_rose[i].x / 3);
// 		hero->probe.y = (hero->pos.y + (double)hero->c->wind_rose[i].y / 3);
// 		// printf("\t%i:\tLAT-pos_x\t%f\tLAT-pos_y\t%f", i, hero->probe.x, hero->probe.y);
// 		hero->probe = move_lateral(hero, true);
// 		col += collision((int)hero->probe.x, (int)hero->probe.y, map);
// 		// printf("\tlat-col\t\t%i\n\n", col);
//
// 	}
// 	return (col);
// }

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

double	pulse_distance(t_vector start, t_vector pulse)
{
	return (sqrt(pow((pulse.x - start.x), 2) + pow((pulse.y - start.y), 2)));
}

t_vector	pulse(double dir, t_hero *hero)
{
	t_vector	pulse;
	t_vector	start;
	// double	pulse_x;
	// double	pulse_y;
	// double	start_x;
	// double	start_y;

	pulse.x = hero->probe.x * BLOCK_SIZE;
	pulse.y = hero->probe.y * BLOCK_SIZE;
	start.x = pulse.x;
	start.y = pulse.y;
	while (pulse_distance(start, pulse) <= hero->collision_radius)
	{
		// printf("\tpulse=%f\n", sqrt(powf((pulse.x - start.x), 2) +  powf((pulse.y - start.y), 2)));
		pulse.x += cos(dir);
		pulse.y += sin(dir);
	}
	// printf("\tx=%f\ty=%f\n", pulse.x, pulse.y);
	return (pulse);
}

int	sonar(t_hero *hero, int **map)
{
	// t_hero		*hero;
	// t_vector	ping;
	t_vector	tmp_pos;
	double		dir;
	double		delta_dir;
	int			col;
	int			i;

	// hero = &game->mini_hero;
	dir = atan2(hero->dir.y, hero->dir.x);
	delta_dir = PI / 100;//hero->fov / FRM_WIDTH;
	col = 0;
	i = -1;
	while (++i < 2 * PI / (PI / 100))
	{
		tmp_pos = pulse(dir, hero);
		tmp_pos.x /= BLOCK_SIZE;
		tmp_pos.y /= BLOCK_SIZE;
		col += collision((int)(tmp_pos.x), (int)(tmp_pos.y), map);
		dir += delta_dir;
	}
	return (col);
}

void	move_hero(int **map, t_hero *hero)
{
	// int			col;
	// t_vector	tmp_pos;
	// t_vector	new_pos;

	// col = 0;
	// tmp_pos = hero->pos;
	// new_pos = hero->pos;
	// if (hero->turn_sinistral || hero->turn_dextral)
	// 	turn_hero(hero->dir.x, hero->plane.x, hero);
	hero->probe = hero->pos;
	//
	if (hero->move_forward || hero->move_backward)
	{
		hero->probe = move_longitudal(hero, true);
		// if (sonar(hero, map) == 0)
			// hero->pos = move_longitudal(hero, false);
	}
	if (hero->move_port || hero->move_starboard)
	{
		hero->probe = move_lateral(hero, true);
		// if (sonar(hero, map) == 0)
			// hero->pos = move_lateral(hero, false);
	}
	//
	if (sonar(hero, map) == 0)
	{
		if (hero->move_forward || hero->move_backward)
			hero->pos = move_longitudal(hero, false);
		if (hero->move_port || hero->move_starboard)
			hero->pos = move_lateral(hero, false);
		if (hero->turn_sinistral || hero->turn_dextral)
			turn_hero(hero->dir.x, hero->plane.x, hero);
	}
	//
	// hero->pos = new_pos;
	// if (hero->move_forward || hero->move_backward)
	// 	col += probe_longitudal(hero, map);
	// if (hero->move_port || hero->move_starboard)
	// 	col += probe_lateral(hero, map);
	// printf("\tcol\t%i\n", col);
	// if (col == 0)
	// {
	// 	if (hero->move_forward || hero->move_backward)
	// 		new_pos = move_longitudal(hero, false);
	// 	if (hero->move_port || hero->move_starboard)
	// 		new_pos = move_lateral(hero, false);
	// 	hero->pos = new_pos;
	// }
}

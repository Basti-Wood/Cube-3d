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
		// printf("\tdir_x=%f\t\tdir_y=%f\n", h->dir.x, h->dir.y);
		// printf("\tplane_x=%f\tplane_y=%f\n\n", h->plane.x, h->plane.y);
	}
	else if (h->turn_dextral)
	{
		h->dir.x = dir_x * cos(speed) - h->dir.y * sin(speed);
		h->plane.x = plane_x * cos(speed) - h->plane.y * sin(speed);
		h->dir.y = dir_x * sin(speed) + h->dir.y * cos(speed);
		h->plane.y = plane_x * sin(speed) + h->plane.y * cos(speed);
		// printf("\tdir_x=%f\t\tdir_y=%f\n", h->dir.x, h->dir.y);
		// printf("\tplane_x=%f\tplane_y=%f\n\n", h->plane.x, h->plane.y);
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
	double		cos_dir;
	double		sin_dir;

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

// void	go_forward(t_hero *h, int **map)
// {
// 	double		speed;
// 	t_vector	new_pos;
//
// 	speed = h->move_speed;
// 	if (h->axes_of_travel >= 2)
// 		speed /= sqrt(2);
// 	h->probe = h->pos;
// 	h->probe.x = h->pos.x + cos(atan2(h->dir.y, h->dir.x)) * speed;
// 	if (sonar(h, map) == 0)
// 		new_pos.x = h->probe.x;
// 	else
// 		new_pos.x = h->pos.x - cos(atan2(h->dir.y, h->dir.x)) / 100000;
// 	h->probe = h->pos;
// 	h->probe.y = h->pos.y + sin(atan2(h->dir.y, h->dir.x)) * speed;
// 	if (sonar(h, map) == 0)
// 		new_pos.y = h->probe.y;
// 	else
// 		new_pos.y = h->pos.y - sin(atan2(h->dir.y, h->dir.x)) / 100000;
// 	h->pos = new_pos;
// }
//
// void	go_backward(t_hero *h, int **map)
// {
// 	double		speed;
// 	t_vector	new_pos;
//
// 	speed = h->move_speed;
// 	if (h->axes_of_travel >= 2)
// 		speed /= sqrt(2);
// 	h->probe = h->pos;
// 	h->probe.x = h->pos.x - cos(atan2(h->dir.y, h->dir.x)) * speed;
// 	if (sonar(h, map) == 0)
// 		new_pos.x = h->probe.x;
// 	else
// 		new_pos.x = h->pos.x + cos(atan2(h->dir.y, h->dir.x)) / 100000;
// 	h->probe = h->pos;
// 	h->probe.y = h->pos.y - sin(atan2(h->dir.y, h->dir.x)) * speed;
// 	if (sonar(h, map) == 0)
// 		new_pos.y = h->probe.y;
// 	else
// 		new_pos.y = h->pos.y + sin(atan2(h->dir.y, h->dir.x)) / 100000;
// 	h->pos = new_pos;
// }
//
// void	go_port(t_hero *h, int **map)
// {
// 	double		speed;
// 	t_vector	new_pos;
//
// 	speed = h->move_speed;
// 	if (h->axes_of_travel >= 2)
// 		speed /= sqrt(2);
// 	h->probe = h->pos;
// 	h->probe.x = h->pos.x + sin(atan2(h->dir.y, h->dir.x)) * speed;
// 	if (sonar(h, map) == 0)
// 		new_pos.x = h->probe.x;
// 	else
// 		new_pos.x = h->pos.x - sin(atan2(h->dir.y, h->dir.x)) / 100000;
// 	h->probe = h->pos;
// 	h->probe.y = h->pos.y - cos(atan2(h->dir.y, h->dir.x)) * speed;
// 	if (sonar(h, map) == 0)
// 		new_pos.y = h->probe.y;
// 	else
// 		new_pos.y = h->pos.y + cos(atan2(h->dir.y, h->dir.x)) / 100000;
// 	h->pos = new_pos;
// }
//
// void	go_starboard(t_hero *h, int **map)
// {
// 	double		speed;
// 	t_vector	new_pos;
//
// 	speed = h->move_speed;
// 	if (h->axes_of_travel >= 2)
// 		speed /= sqrt(2);
// 	h->probe = h->pos;
// 	h->probe.x = h->pos.x - sin(atan2(h->dir.y, h->dir.x)) * speed;
// 	if (sonar(h, map) == 0)
// 		new_pos.x = h->probe.x;
// 	else
// 		new_pos.x = h->pos.x + sin(atan2(h->dir.y, h->dir.x)) / 100000;
// 	h->probe = h->pos;
// 	h->probe.y = h->pos.y + cos(atan2(h->dir.y, h->dir.x)) * speed;
// 	if (sonar(h, map) == 0)
// 		new_pos.y = h->probe.y;
// 	else
// 		new_pos.y = h->pos.y - cos(atan2(h->dir.y, h->dir.x)) / 100000;
// 	h->pos = new_pos;
// }

// void	move_hero(t_hero *hero, int **map)
// {
// 	if (hero->move_forward)
// 		go_forward(hero, map);
// 	if (hero->move_backward)
// 		go_backward(hero, map);
// 	if (hero->move_port)
// 		go_port(hero, map);
// 	if (hero->move_starboard)
// 		go_starboard(hero, map);
// 	if (hero->turn_sinistral || hero->turn_dextral)
// 		turn_hero(hero->dir.x, hero->plane.x, hero);
// }

// dir_len = fabs(h.dir.x + h.dir.y);
// plane_len = fabs(h.plane.x + h.plane.y);
// hero.fov = 2 * atan(plane_len / dir_len);

// void	move_longitudal(t_hero *h, int **map)
// {
// 	double		speed;
// 	t_vector	new_pos;
//
// 	speed = h->move_speed;
// 	if (h->axes_of_travel >= 2)
// 		speed /= sqrt(2);
// 	// if (!h->mini)
// 	// {
// 	// // 	printf("\tmini-hero");
// 	// // else
// 	// // 	printf("\t\thero");
// 	// printf("\taxes=%i\t", h->axes_of_travel);
// 	// printf("\tspeed=%f\t\n", speed);
// 	// }
// 	if (h->move_forward)
// 	{
// 		h->probe = h->pos;
// 		h->probe.x = h->pos.x + cos(atan2(h->dir.y, h->dir.x)) * speed;
// 		if (sonar(h, map) == 0)
// 			new_pos.x = h->probe.x;
// 		else
// 			new_pos.x = h->pos.x - cos(atan2(h->dir.y, h->dir.x)) / 100000;
// 		h->probe = h->pos;
// 		h->probe.y = h->pos.y + sin(atan2(h->dir.y, h->dir.x)) * speed;
// 		if (sonar(h, map) == 0)
// 			new_pos.y = h->probe.y;
// 		else
// 			new_pos.y = h->pos.y - sin(atan2(h->dir.y, h->dir.x)) / 100000;
// 	}
// 	if (h->move_backward)
// 	{
// 		h->probe = h->pos;
// 		h->probe.x = h->pos.x - cos(atan2(h->dir.y, h->dir.x)) * speed;
// 		if (sonar(h, map) == 0)
// 			new_pos.x = h->probe.x;
// 		else
// 			new_pos.x = h->pos.x + cos(atan2(h->dir.y, h->dir.x)) / 100000;
// 		h->probe = h->pos;
// 		h->probe.y = h->pos.y - sin(atan2(h->dir.y, h->dir.x)) * speed;
// 		if (sonar(h, map) == 0)
// 			new_pos.y = h->probe.y;
// 		else
// 			new_pos.y = h->pos.y + sin(atan2(h->dir.y, h->dir.x)) / 100000;
// 	}
// 	h->pos = new_pos;
// }

// void	move_lateral(t_hero *h, int **map)
// {
// 	double		speed;
// 	t_vector	new_pos;
//
// 	speed = h->move_speed;
// 		if (h->axes_of_travel >= 2)
// 		speed /= sqrt(2);
// 	// if (!h->mini)
// 	// {
// 	// // 	printf("\tmini-hero");
// 	// // else
// 	// // 	printf("\t\thero");
// 	// printf("\taxes=%i\t", h->axes_of_travel);
// 	// printf("\tspeed=%f\t\n", speed);
// 	// }
// 	if (h->move_port)
// 	{
// 		h->probe = h->pos;
// 		h->probe.x = h->pos.x + sin(atan2(h->dir.y, h->dir.x)) * speed;
// 		if (sonar(h, map) == 0)
// 			new_pos.x = h->probe.x;
// 		else
// 			new_pos.x = h->pos.x - sin(atan2(h->dir.y, h->dir.x)) / 100000;
// 		h->probe = h->pos;
// 		h->probe.y = h->pos.y - cos(atan2(h->dir.y, h->dir.x)) * speed;
// 		if (sonar(h, map) == 0)
// 			new_pos.y = h->probe.y;
// 		else
// 			new_pos.y = h->pos.y + cos(atan2(h->dir.y, h->dir.x)) / 100000;
// 	}
// 	if (h->move_starboard)
// 	{
// 		h->probe = h->pos;
// 		h->probe.x = h->pos.x - sin(atan2(h->dir.y, h->dir.x)) * speed;
// 		if (sonar(h, map) == 0)
// 			new_pos.x = h->probe.x;
// 		else
// 			new_pos.x = h->pos.x + sin(atan2(h->dir.y, h->dir.x)) / 100000;
// 		h->probe = h->pos;
// 		h->probe.y = h->pos.y + cos(atan2(h->dir.y, h->dir.x)) * speed;
// 		if (sonar(h, map) == 0)
// 			new_pos.y = h->probe.y;
// 		else
// 			new_pos.y = h->pos.y - cos(atan2(h->dir.y, h->dir.x)) / 100000;
// 	}
// 	h->pos = new_pos;
// }

// void	move_hero(int **map, t_hero *hero)
// {
// 	if (hero->move_forward || hero->move_backward)
// 		move_longitudal(hero, map);
// 	if (hero->move_port || hero->move_starboard)
// 		move_lateral(hero, map);
// 	if (hero->turn_sinistral || hero->turn_dextral)
// 		turn_hero(hero->dir.x, hero->plane.x, hero);
	// int			col;
	// t_vector	tmp_pos;
	// t_vector	new_pos;

	// col = 0;
	// tmp_pos = hero->pos;
	// new_pos = hero->pos;
	// if (hero->turn_sinistral || hero->turn_dextral)
	// 	turn_hero(hero->dir.x, hero->plane.x, hero);

	// hero->probe = hero->pos;
	// if (sonar(hero, map) == 0)
	// {
	// 	if (hero->turn_sinistral || hero->turn_dextral)
	// 		turn_hero(hero->dir.x, hero->plane.x, hero);
	// }
	// if (hero->turn_sinistral || hero->turn_dextral)
	// {
	// 	if (sonar(hero, map) == 0)
	// 		turn_hero(hero->dir.x, hero->plane.x, hero);
	// }
	// if (hero->move_forward || hero->move_backward)
	// 	move_longitudal(hero, map);
	// if (hero->move_port || hero->move_starboard)
	// 	move_lateral(hero, map);
	// if (hero->turn_sinistral || hero->turn_dextral)
	// 	turn_hero(hero->dir.x, hero->plane.x, hero);
	// if (sonar(hero, map) == 0)
	// {
	// 	if (hero->turn_sinistral || hero->turn_dextral)
	// 		turn_hero(hero->dir.x, hero->plane.x, hero);
	// }
	//
	// if (sonar(hero, map) == 0)
	// {
	// 	if (hero->move_forward || hero->move_backward)
	// 		hero->pos = move_longitudal(hero, false);
	// 	if (hero->move_port || hero->move_starboard)
	// 		hero->pos = move_lateral(hero, false);
		// if (hero->turn_sinistral || hero->turn_dextral)
			// turn_hero(hero->dir.x, hero->plane.x, hero);
	// }
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
// }

// t_vector	move_longitudal(t_hero *h, bool probe)
// {
// 	t_vector	new_pos;
// 	t_vector	tmp_pos;
// 	double		speed;
//
// 	tmp_pos = h->pos;
// 	if (probe)
// 	// {
// 		tmp_pos = h->probe;
// 		// speed = h->probe_speed;
// 	// }
// 	speed = h->move_speed;
// 	if (h->axes_of_travel >= 2)
// 		speed /= sqrt(2);
// 	// if (!h->mini)
// 	// {
// 	// // 	printf("\tmini-hero");
// 	// // else
// 	// // 	printf("\t\thero");
// 	// printf("\taxes=%i\t", h->axes_of_travel);
// 	// printf("\tspeed=%f\t\n", speed);
// 	// }
// 	if (h->move_forward)
// 	{
// 		new_pos.x = tmp_pos.x + cos(atan2(h->dir.y, h->dir.x)) * speed;
// 		// printf("\tx\t%f\n", new_pos.x);
// 		new_pos.y = tmp_pos.y + sin(atan2(h->dir.y, h->dir.x)) * speed;
// 		// printf("\ty\t%f\n", new_pos.y);
// 	}
// 	if (h->move_backward)
// 	{
// 		new_pos.x = tmp_pos.x - cos(atan2(h->dir.y, h->dir.x)) * speed;
// 		// printf("\tx\t%f\n", new_pos.x);
// 		new_pos.y = tmp_pos.y - sin(atan2(h->dir.y, h->dir.x)) * speed;
// 		// printf("\ty\t%f\n", new_pos.y);
// 	}
// 	return (new_pos);
// }

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

// t_vector	move_lateral(t_hero *h, bool probe)
// {
// 	t_vector	new_pos;
// 	t_vector	tmp_pos;
// 	double		speed;
//
// 	tmp_pos = h->pos;
// 	if (probe)
// 	// {
// 		tmp_pos = h->probe;
// 		// speed = h->probe_speed;
// 	// }
// 	speed = h->move_speed;
// 		if (h->axes_of_travel >= 2)
// 		speed /= sqrt(2);
// 	// if (!h->mini)
// 	// {
// 	// // 	printf("\tmini-hero");
// 	// // else
// 	// // 	printf("\t\thero");
// 	// printf("\taxes=%i\t", h->axes_of_travel);
// 	// printf("\tspeed=%f\t\n", speed);
// 	// }
// 	if (h->move_port)
// 	{
// 		new_pos.x = tmp_pos.x + sin(atan2(h->dir.y, h->dir.x)) * speed;
// 		// printf("\tx\t%f\n", new_pos.x);
// 		new_pos.y = tmp_pos.y - cos(atan2(h->dir.y, h->dir.x)) * speed;
// 		// printf("\ty\t%f\n", new_pos.y);
// 	}
// 	if (h->move_starboard)
// 	{
// 		new_pos.x = tmp_pos.x - sin(atan2(h->dir.y, h->dir.x)) * speed;
// 		// printf("\tx\t%f\n", new_pos.x);
// 		new_pos.y = tmp_pos.y + cos(atan2(h->dir.y, h->dir.x)) * speed;
// 		// printf("\ty\t%f\n", new_pos.y);
// 	}
// 	return (new_pos);
// }

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

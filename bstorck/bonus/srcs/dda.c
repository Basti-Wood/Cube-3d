/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstorck <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 15:23:38 by bstorck           #+#    #+#             */
/*   Updated: 2025/11/21 15:23:41 by bstorck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/game.h"

double	get_delta_dist(double dir)
{
	double	delta_dist;

	if (fabs(dir) < 1e-10)
		delta_dist = 1e30;
	else
		delta_dist = fabs(1.0 / dir);
	return (delta_dist);
}

void	init_ray(t_hero *hero)
{
	t_ray	*ray;

	ray = &hero->ray;
	ray->map.x = (int)hero->pos.x;
	ray->map.y = (int)hero->pos.y;
	ray->dir.x = hero->dir.x + hero->plane.x * hero->scan_x;
	ray->dir.y = hero->dir.y + hero->plane.y * hero->scan_x;
	ray->delta_dist.x = get_delta_dist(ray->dir.x);
	ray->delta_dist.y = get_delta_dist(ray->dir.y);
	if (ray->dir.x < 0)
		ray->step.x = -1;
	else
		ray->step.x = 1;
	if (ray->dir.y < 0)
		ray->step.y = -1;
	else
		ray->step.y = 1;
	if (ray->step.x == -1)
		ray->side_dist.x = (hero->pos.x - ray->map.x) * ray->delta_dist.x;
	else
		ray->side_dist.x = (ray->map.x + 1.0 - hero->pos.x) * ray->delta_dist.x;
	if (ray->step.y == -1)
		ray->side_dist.y = (hero->pos.y - ray->map.y) * ray->delta_dist.y;
	else
		ray->side_dist.y = (ray->map.y + 1.0 - hero->pos.y) * ray->delta_dist.y;
}

static int	hit(int object, t_game *g)
{
	double	dist;

	if (object == DOOR)
	{
		if (g->hero.ray.side)
		{
			dist = g->hero.ray.side_dist.y - g->hero.ray.delta_dist.y * 0.6;//Doors have 10% thickness
			if (g->hero.ray.side_dist.x < dist)
				return (0);
			g->hero.ray.perp_dist = dist;
			return(get_texture_x(DOOR, g));
				// return (0);
		}
		else
		{
			dist = g->hero.ray.side_dist.x - g->hero.ray.delta_dist.x * 0.6;//0.5 + 0.1
			if (g->hero.ray.side_dist.y < dist)
				return (0);
			g->hero.ray.perp_dist = dist;
			return(get_texture_x(DOOR, g));
				// return (0);
		}
		// return (1);
	}
	else
		return (1);
	return (0);
}

// static int	hit(int object, t_game *g)
// {
// 	double	dist;
//
// 	if (object == DOOR)
// 		return (hit_door(g));
// 	else
// 		return (1);
// 	return (0);
// }

void	dda(t_game *g)
{
	// t_ray	*ray;
	int	object;

	// ray = &game->hero.ray;
	g->hero.ray.side = false;
	while (true)
	{
		if (g->hero.ray.side_dist.x < g->hero.ray.side_dist.y)
		{
			g->hero.ray.map.x += g->hero.ray.step.x;
			g->hero.ray.perp_dist = g->hero.ray.side_dist.x;
			g->hero.ray.side_dist.x += g->hero.ray.delta_dist.x;
			g->hero.ray.side = false;
		}
		else
		{
			g->hero.ray.map.y += g->hero.ray.step.y;
			g->hero.ray.perp_dist = g->hero.ray.side_dist.y;
			g->hero.ray.side_dist.y += g->hero.ray.delta_dist.y;
			g->hero.ray.side = true;
		}
		object = get_texture_id(g->hero.ray.map.x, g->hero.ray.map.y, &g->map);
		if (object != 0)
			if (hit(object, g))
				break ;
	}
}

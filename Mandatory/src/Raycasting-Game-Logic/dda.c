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

#include "../../includes/game.h"

double	get_delta_dist(double dir)
{
	double	delta_dist;

	if (fabs(dir) < 1e-10)
		delta_dist = 1e30;
	else
		delta_dist = fabs(1.0 / dir);
	return (delta_dist);
}

static void	init_ray_step_and_side_dist(t_ray *ray, t_hero *hero)
{
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

void	init_ray(int i, t_hero *hero)
{
	t_ray	*ray;

	(void)i;
	ray = &hero->ray;
	ray->map.x = (int)hero->pos.x;
	ray->map.y = (int)hero->pos.y;
	ray->dir.x = hero->dir.x + hero->plane.x * hero->scan_x;
	ray->dir.y = hero->dir.y + hero->plane.y * hero->scan_x;
	ray->delta_dist.x = get_delta_dist(ray->dir.x);
	ray->delta_dist.y = get_delta_dist(ray->dir.y);
	init_ray_step_and_side_dist(ray, hero);
}

void	dda(t_game *game)
{
	t_ray	*ray;

	ray = &game->hero.ray;
	ray->side = false;
	while (true)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->map.x += ray->step.x;
			ray->perp_dist = ray->side_dist.x;
			ray->side_dist.x += ray->delta_dist.x;
			ray->side = false;
		}
		else
		{
			ray->map.y += ray->step.y;
			ray->perp_dist = ray->side_dist.y;
			ray->side_dist.y += ray->delta_dist.y;
			ray->side = true;
		}
		if (collision(ray->map.x, ray->map.y, &game->map))
			break ;
	}
}

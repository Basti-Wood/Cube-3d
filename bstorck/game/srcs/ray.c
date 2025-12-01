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

// t_ray	init_ray(t_hero *hero)
// {
// 	t_ray	ray;
//
// 	ray.side = false;
// 	ray.dir.x = hero->dir.x + hero->plane.x * hero->scan_x;//-1
// 	ray.dir.y = hero->dir.y + hero->plane.y * hero->scan_x;// 0
// 	ray.map.x = 0;
// 	ray.map.y = 0;
// 	ray.step.x = 0;
// 	ray.step.y = 0;
// 	ray.side_dist.x = 0;
// 	ray.side_dist.y = 0;
// 	ray.delta_dist.x = 0;
// 	ray.delta_dist.y = 0;
// 	ray.perp_dist_wall = 0;
// 	return (ray);
// }

double	get_delta_dist(double dir)
{
	double	delta_dist;

	delta_dist = 1e30;
	if (dir != 0)
		delta_dist = fabs(1 / dir);
	return (delta_dist);
}

double	get_side_dist(char coordinate, t_hero *hero)
{
	double	ray_dir;
	double	hero_pos;
	double	ray_delta_dist;
	int		ray_map;

	if (coordinate == 'x')
	{
		ray_dir = hero->ray.dir.x;
		hero_pos = hero->pos.x;
		ray_delta_dist = hero->ray.delta_dist.x;
		ray_map = hero->ray.map.x;
	}
	else
	{
		ray_dir = hero->ray.dir.y;
		hero_pos = hero->pos.y;
		ray_delta_dist = hero->ray.delta_dist.y;
		ray_map = hero->ray.map.y;
	}
	if (ray_dir < 0)
		return ((hero_pos - ray_map) * ray_delta_dist);
	else
		return ((ray_map + 1 - hero_pos) * ray_delta_dist);
}

void	cast_ray(t_hero *hero)
{
	t_ray	*ray;

	ray = &hero->ray;
	ray->side = false;
	ray->map.x = (int)hero->pos.x;
	ray->map.y = (int)hero->pos.y;
	ray->step.x = 1;
	ray->dir.x = hero->dir.x + hero->plane.x * hero->scan_x;
	if (ray->dir.x < 0)
		ray->step.x = -1;
	ray->step.y = 1;
	ray->dir.y = hero->dir.y + hero->plane.y * hero->scan_x;
	if (ray->dir.y < 0)
		ray->step.y = -1;
	ray->delta_dist.x = get_delta_dist(ray->dir.x);
	ray->delta_dist.y = get_delta_dist(ray->dir.y);
	ray->side_dist.x = get_side_dist('x', hero);
	ray->side_dist.y = get_side_dist('y', hero);
}

void	dda(t_game *game)
{
	bool	hit;

	hit = false;
	while (!hit)
	{
		if (game->hero.ray.side_dist.x < game->hero.ray.side_dist.y)
		{
			game->hero.ray.side_dist.x += game->hero.ray.delta_dist.x;
			game->hero.ray.map.x += game->hero.ray.step.x;
			game->hero.ray.side = true;
		}
		else
		{
			game->hero.ray.side_dist.y += game->hero.ray.delta_dist.y;
			game->hero.ray.map.y += game->hero.ray.step.y;
			game->hero.ray.side = false;
		}
		if (game->map[game->hero.ray.map.y][game->hero.ray.map.x] != 0)
			hit = true;
	}
}

// void	hit(double sideDistX, double sideDistY, double deltaDistX, double deltaDistX, int mapX, int mapY, int stepX, int stepY, int side)
// {
// 	//jump to next map square, either in x-direction, or in y-direction
// 	if (sideDistX < sideDistY)
// 	{
// 		sideDistX += deltaDistX;
// 		mapX += stepX;
// 		side = 0;
// 	}
// 	else
// 	{
// 		sideDistY += deltaDistY;
// 		mapY += stepY;
// 		side = 1;
// 	}
// 	//Check if ray has hit a wall
// 	if (worldMap[mapX][mapY] == 0)
// 		hit(sideDistX, sideDistY, deltaDistX, deltaDistX, mapX, mapY, stepX, stepY, side);
// }

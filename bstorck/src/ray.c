#include "../includes/game.h"

// t_ray	init_ray(t_player *player)
// {
// 	t_ray	ray;
//
// 	ray.side = false;
// 	ray.dir.x = player->dir.x + player->plane.x * player->scan_x;//-1
// 	ray.dir.y = player->dir.y + player->plane.y * player->scan_x;// 0
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

double	get_side_dist(char coordinate, t_player *player)
{
	double	ray_dir;
	double	player_pos;
	double	ray_delta_dist;
	int		ray_map;

	if (coordinate == 'x')
	{
		ray_dir = player->ray.dir.x;
		player_pos = player->pos.x;
		ray_delta_dist = player->ray.delta_dist.x;
		ray_map = player->ray.map.x;
	}
	else
	{
		ray_dir = player->ray.dir.y;
		player_pos = player->pos.y;
		ray_delta_dist = player->ray.delta_dist.y;
		ray_map = player->ray.map.y;
	}
	if (ray_dir < 0)
		return ((player_pos - ray_map) * ray_delta_dist);
	else
		return ((ray_map + 1 - player_pos) * ray_delta_dist);
}

void	cast_ray(t_player *player)
{
	t_ray	*ray;

	ray = &player->ray;
	ray->side = false;
	ray->map.x = (int)player->pos.x;
	ray->map.y = (int)player->pos.y;
	ray->step.x = 1;
	ray->dir.x = player->dir.x + player->plane.x * player->scan_x;
	if (ray->dir.x < 0)
		ray->step.x = -1;
	ray->step.y = 1;
	ray->dir.y = player->dir.y + player->plane.y * player->scan_x;
	if (ray->dir.y < 0)
		ray->step.y = -1;
	ray->delta_dist.x = get_delta_dist(ray->dir.x);
	ray->delta_dist.y = get_delta_dist(ray->dir.y);
	ray->side_dist.x = get_side_dist('x', player);
	ray->side_dist.y = get_side_dist('y', player);
}

void	dda(t_game *game)
{
	bool	hit;

	hit = false;
	while (!hit)
	{
		if (game->player.ray.side_dist.x < game->player.ray.side_dist.y)
		{
			game->player.ray.side_dist.x += game->player.ray.delta_dist.x;
			game->player.ray.map.x += game->player.ray.step.x;
			game->player.ray.side = false;
		}
		else
		{
			game->player.ray.side_dist.y += game->player.ray.delta_dist.y;
			game->player.ray.map.y += game->player.ray.step.y;
			game->player.ray.side = true;
		}
		if (game->map[game->player.ray.map.y][game->player.ray.map.x] != 0)
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

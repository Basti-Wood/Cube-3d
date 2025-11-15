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

	// if (dir == 0)
	delta_dist = 1e30;
	if (dir != 0)
		delta_dist = fabs(1 / dir);
	// printf("\tdelta\t%f\n", delta_dist);
	return (delta_dist);
}

double	get_side_dist(char coordinate, t_player *player)
{
	double	player_pos;
	double	ray_dir;
	double	ray_delta_dist;
	int		ray_map;
	double	ret;

	if (coordinate == 'x')
	{
		player_pos = player->pos.x;
		ray_dir = player->ray.dir.x;
		ray_delta_dist = player->ray.delta_dist.x;
		ray_map = player->ray.map.x;
	}
	else
	{
		player_pos = player->pos.y;
		ray_dir = player->ray.dir.y;
		ray_delta_dist = player->ray.delta_dist.y;
		ray_map = player->ray.map.y;
	}
	if (ray_dir < 0)
		ret = (player_pos - ray_map) * ray_delta_dist;
	else
		ret = (ray_map + 1 - player_pos) * ray_delta_dist;
	// printf("\tside\t%f\n", ret);
	return ret;
}

void	cast_ray(t_player *player)
{
	t_ray	*ray;

	ray = &player->ray;
	ray->side = false;
	ray->map.x = player->pos.x;
	ray->map.y = player->pos.y;
	// printf("\t%i\t%i\n", ray->map.x, ray->map.y);
	ray->step.x = 1;
	ray->dir.x = player->dir.x + player->plane.x * player->scan_x;
	if (ray->dir.x < 0)
		ray->step.x = -1;
	ray->step.y = 1;
	ray->dir.y = player->dir.y + player->plane.y * player->scan_x;
	if (ray->dir.y < 0)
		ray->step.y = -1;
	// printf("\tdirX\t%f\tdirY\t%f\n", ray->dir.x, ray->dir.y);
	// printf("\tplaneX\t%f\tplaneY\t%f\n", player->plane.x, player->plane.y);
	ray->delta_dist.x = get_delta_dist(ray->dir.x);
	ray->delta_dist.y = get_delta_dist(ray->dir.y);
	ray->side_dist.x = get_side_dist('x', player);
	// printf("\tsideX\t%f\tsideY\t%f\n", ray->side_dist.x, ray->side_dist.y);
	ray->side_dist.y = get_side_dist('y', player);
}

//perform DDA as recursive function
void	dda_ray(int **map, t_ray *ray, t_game *game)
{
	// bool hit;
	draw_empty_square(ray->map.x * BLOCK_SIZE + FRM_WIDTH, ray->map.y * BLOCK_SIZE, 7, 0xFF0000, game);
	// hit = false;
	// while (!hit)
	// {
	// put_pixel(ray->map.x, ray->map.y, 0xFF0000, game);
	//jump to next map square, either in x-direction, or in y-direction
	// printf("DING!");
	if (ray->side_dist.x > ray->side_dist.y)
	{
		// printf("\tx > y");
		ray->side_dist.x += ray->delta_dist.x;
		ray->map.x += ray->step.x;
		ray->side = false;
		// ray->side_dist.x -= ray->side_dist.y;
	}
	else
	{
		// printf("\tx < y");
		ray->side_dist.y += ray->delta_dist.y;
		ray->map.y += ray->step.y;
		ray->side = true;
		// ray->side_dist.x -= ray->side_dist.y;
	}
	// printf("\tdeltaX\t%f\tdeltaY\t%f\n", ray->delta_dist.x, ray->delta_dist.y);
	// printf("\tsideX\t%f\tsideY\t%f\n", ray->side_dist.x, ray->side_dist.y);
	// printf("\tmapX\t%i\tmapY\t%i\n\n", ray->map.x, ray->map.y);
	//Check if ray has hit a wall
	if (map[ray->map.y][ray->map.x] == 0)
	{
		// hit = true;
		dda_ray(map, ray, game);
	}
	// }
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

bool	touch(double px, double py, t_game *game)
{
	int	x = px / BLOCK_SIZE;
	// printf("%i\n", x);
	int	y = py / BLOCK_SIZE;
	if(game->map[y][x] > 0)
		return true;
	return false;
}

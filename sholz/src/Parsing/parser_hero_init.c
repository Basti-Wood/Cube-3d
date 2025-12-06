#include "../../includes/cub3d.h"

static void	set_direction_north(t_hero *hero)
{
	hero->dir.x = 0;
	hero->dir.y = -1;
	hero->plane.x = 0.66;
	hero->plane.y = 0;
}

static void	set_direction_south(t_hero *hero)
{
	hero->dir.x = 0;
	hero->dir.y = 1;
	hero->plane.x = -0.66;
	hero->plane.y = 0;
}

static void	set_direction_east(t_hero *hero)
{
	hero->dir.x = 1;
	hero->dir.y = 0;
	hero->plane.x = 0;
	hero->plane.y = 0.66;
}

static void	set_direction_west(t_hero *hero)
{
	hero->dir.x = -1;
	hero->dir.y = 0;
	hero->plane.x = 0;
	hero->plane.y = -0.66;
}

void	init_hero_from_map(t_hero *hero, t_map *map)
{
	hero->pos.x = map->player.x + 0.5;
	hero->pos.y = map->player.y + 0.5;
	if (map->player_dir == 'N')
		set_direction_north(hero);
	else if (map->player_dir == 'S')
		set_direction_south(hero);
	else if (map->player_dir == 'E')
		set_direction_east(hero);
	else if (map->player_dir == 'W')
		set_direction_west(hero);
	hero->move_speed = sqrt(2) * 0.04;
	hero->turn_speed = PI / 75;
	hero->fov = 2 * atan(fabs(hero->plane.x));
	hero->collision_radius = 0.15625 * BLOCK_SIZE;
	hero->move_forward = false;
	hero->move_backward = false;
	hero->move_port = false;
	hero->move_starboard = false;
	hero->turn_sinistral = false;
	hero->turn_dextral = false;
	hero->axes_of_travel = 0;
}

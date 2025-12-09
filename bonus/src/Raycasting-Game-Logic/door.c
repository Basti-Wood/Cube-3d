#include "../../includes/game.h"

void	set_door_counter(t_door *door, t_map *map)
{
	if (door->state == CLOSED)
		door->counter = 0;
	if (get_current_time() > (door->last_check + ANIMATION_STEP))
	{
		if (door->interrupt)
			door->counter = 1 - door->counter;
		else
			// door->counter += 1.0/42000;
			door->counter += ((double)get_current_time() - door->animation_start) / 8400000;
		// printf("\tdoor->counter = %f\n", door->counter);
		door->interrupt = false;
		if (door->counter >= 1)
		{
			door->counter = 0;
			door->state = door->state + 1;
			if (door->state == OPEN)
			{
				door->last_opened = get_current_time();
				map->grid[door->pos.y * map->width + door->pos.x] = 0;
			}
			// else
			// {
			// 	map->grid[door->pos.y * map->width + door->pos.x] = 2;
			// 	if (hero_sonar(hero, map))
			// 	{
			// 		// open_door(door, map);
			// 		map->grid[door->pos.y * map->width + door->pos.x] = 0;
			// 		door->state = OPEN;
			// 	}
			// }
		}
	}
}
// if (door->state == OPENING)
// {
// 	door->counter = ((double)get_current_time() - door->animation_start) / 2000;
// 	// printf("\tdoor->counter = %f\n", door->counter);
// 	if (door->counter >= 1)
// 	{
// 		door->state = OPEN;
// 		door->last_opened = get_current_time();
// 		map->grid[door->pos.y * map->width + door->pos.x] = 0;
// 	}
// }
// if (door->state == CLOSING)
// {
// 	door->counter = ((double)get_current_time() - door->animation_start) / 2000;
// 	// printf("\tdoor->counter = %f\n", door->counter);
// 	if (door->counter >= 1)
// 	{
// 		door->state = CLOSED;
// 		map->grid[door->pos.y * map->width + door->pos.x] = 2;
// 		if (hero_sonar(hero, map))
// 		{
// 			// open_door(door, map);
// 			map->grid[door->pos.y * map->width + door->pos.x] = 0;
// 			door->state = OPEN;
// 		}
// 	}
// }

static void	open_door(t_door *door)
{
	// printf("\t%li\topening door%i at %i, %i\n", get_current_time(), door->id, door->pos.x, door->pos.y);
	door->state = OPENING;
	// if (!door->interrupt)
		// door->counter = 0;
	door->animation_start = get_current_time();
	// door->interrupt = false;
	// door->counter = 1;
	// if (door->counter)
	// {
	// 	map->grid[door->pos.y * map->width + door->pos.x] = 0;
	// 	door->state = OPEN;
	// 	door->last_opened = get_current_time();
	// }
}

static void	close_door(t_hero *hero, t_door *door, t_map *map)
{
	// printf("\t%li\tclosing door%i at %i, %i\n", get_current_time(), door->id, door->pos.x, door->pos.y);
	map->grid[door->pos.y * map->width + door->pos.x] = 2;
	if (hero_sonar(hero, map))
	{
		// open_door(door, map);
		map->grid[door->pos.y * map->width + door->pos.x] = 0;
		door->state = OPEN;
	}
	else
	{
		door->state = CLOSING;
		// if (!door->interrupt)
			// door->counter = 0;
		door->animation_start = get_current_time();
		// door->interrupt = false;
	}
	// door->counter = 0;
	// if (!door->counter)
	// {
	// 	map->grid[door->pos.y * map->width + door->pos.x] = 2;
	// 	door->state = CLOSED;
	// 	// printf("\tprobe.x = %f\tprobe.y = %f\n", hero->probe.x, hero->probe.y);
	// 	if (hero_sonar(hero, map))
	// 		open_door(door, map);
	// }
}

void	handle_door(t_hero *hero, t_map *map)
{
	t_door	*door;
	// int		i;
	int		x;
	int		y;

	hero->probe = hero->pos;
	x = (int)hero->pos.x + round(hero->dir.x);
	y = (int)hero->pos.y + round(hero->dir.y);
	// printf("\n\t-------------------------------------------\n");
	// printf("\n\tpos.x = %i", (int)hero->pos.x);
	// printf("\tpos.y = %i\n", (int)hero->pos.y);
	// printf("\n\tround\n");
	// printf("\tx\t%f -> %f\n", hero->dir.x, round(hero->dir.x));
	// printf("\ty\t%f -> %f\n", hero->dir.y, round(hero->dir.y));
	// printf("\n\tx = %i", x);
	// printf("\ty = %i\n", y);
	// printf("\n\t-------------------------------------------\n");
	// printf("\n\tlf\tdoor\tat x=%i y=%i\n", x, y);
	// // i = -1;
	// // while (++i < map->number_of_doors)
	// // {
	// // 	if (map->door[i].pos.x == x && map->door[i].pos.y == y)
	// // 	{
	// // 		printf("\tfound\tdoor%i\tat x=%i y=%i\n", i, x, y);
	// // 		// if (map->grid[y * map->width + x])
	// // 		if (is_open(&map->door[i]))
	// // 			close_door(hero, &map->door[i], map);
	// // 		else
	// // 			open_door(&map->door[i], map);
	// // 		break ;
	// // 	}
	// // }
	door = get_door(x, y, map);
	if (door != NULL)
	{
		if (door->state == OPENING || door->state == CLOSING)
			door->interrupt = true;
		// printf("\tfound\tdoor%i\tat x=%i y=%i\n", door->id, x, y);
		if (door->state == OPEN || door->state == OPENING)
			close_door(hero, door, map);
		else
			open_door(door);
	}
}

void	reset_doors(t_hero *hero, t_map *map)
{
	// int		x;
	// int		y;
	int		i;

	i = -1;
	while (++i < map->number_of_doors)
	{
		if (map->door[i].state == OPEN)
		{
			// printf("\tDING!\n");
			// x = map->door[i].pos.x;
			// y = map->door[i].pos.y;
			// printf("\tlast opened:\t%li\n", map->door[i].last_opened);
			// printf("\tcurrent_time:\t%li\n", get_current_time());
			if (get_current_time() > (map->door[i].last_opened + CLOSE_AFTER))
			{
				// printf("\tDONG!\n");
				close_door(hero, &map->door[i], map);
			}
		}
	}
}

// printf("\n\t-------------------------------------------\n");
// printf("\tfloor\n");
// printf("\tx\t%f -> %f\n", hero->dir.x, floor(hero->dir.x));
// printf("\ty\t%f -> %f\n", hero->dir.y, floor(hero->dir.y));
// printf("\n\trint\n");
// printf("\tx\t%f -> %f\n", hero->dir.x, rint(hero->dir.x));
// printf("\ty\t%f -> %f\n", hero->dir.y, rint(hero->dir.y));
// printf("\n\tceil\n");
// printf("\tx\t%f -> %f\n", hero->dir.x, ceil(hero->dir.x));
// printf("\ty\t%f -> %f\n", hero->dir.y, ceil(hero->dir.y));

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstorck <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 15:25:38 by bstorck           #+#    #+#             */
/*   Updated: 2025/11/21 15:25:41 by bstorck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"

// t_wind_rose	init_wind_rose(void)
// {
// 	t_wind_rose	c;
//
// 	c.wind_rose[0].x = -1;
// 	c.wind_rose[0].y = 0;
// 	c.wind_rose[1].x = 0;
// 	c.wind_rose[1].y = -1;
// 	c.wind_rose[2].x = 1;
// 	c.wind_rose[2].y = 0;
// 	c.wind_rose[3].x = 0;
// 	c.wind_rose[3].y = 1;
// 	return (c);
// }

void	init_game(t_game *g)
{
	// game->time = 0;
	// game->prev_time = 0;
	g->skip_intro = false;
	g->map_width = 30;
	g->map_height = 30;
	g->map = init_map(g->map_width, g->map_width);
	// g->c = init_wind_rose();
	g->walker = init_walker(g);
	if (get_start(g))
	{
		printf("Error\nUnknown error.\n");
		close_game(g);
	}
	if (get_direction(g))
	{
		printf("Error\nUnknown error.\n");
		close_game(g);
	}
	g->walker.first = g->walker.wind_rose[g->walker.prev];
	g->hero = init_hero(false, g);
	g->mini_hero = init_hero(true, g);
	// game->hero.ray = init_ray(&game->hero);
	// game->ray = game->hero.ray;
	g->mlx = mlx_init();
}

void	draw_pulse(double dir, t_game *game)
{
	t_vector	pulse;
	t_vector	start;
	// double	pulse_x;
	// double	pulse_y;
	// double	start_x;
	// double	start_y;

	pulse.x = game->mini_hero.pos.x * BLOCK_SIZE;
	pulse.y = game->mini_hero.pos.y * BLOCK_SIZE;
	start.x = pulse.x;
	start.y = pulse.y;
	while (/*!collision(pulse.x / BLOCK_SIZE, pulse.y / BLOCK_SIZE, game->map) && */(sqrt(pow((pulse.x - start.x), 2) +  pow((pulse.y - start.y), 2)) < 7))
	{
		// printf("\tpulse=%f\n", sqrt(powf((pulse.x - start.x), 2) +  powf((pulse.y - start.y), 2)));
		put_pixel(pulse.x + FRM_WIDTH, pulse.y, 0x00FF00, game);
		pulse.x += cos(dir);
		pulse.y += sin(dir);
	}
	// put_pixel(pulse.x + FRM_WIDTH, pulse.y, 0x00FF00, game);
	// printf("\tpulse.len=%f", sqrt(powf((pulse.x - start.x), 2) +  powf((pulse.y - start.y), 2)));
	// printf("\tpulse.x=%i\tpulse.y=%i\n", (int)(pulse.x / BLOCK_SIZE), (int)(pulse.y / BLOCK_SIZE));
}

void	draw_sonar(t_game *game)
{
	t_hero		*hero;
	double		dir;
	double		delta_dir;
	int			i;

	hero = &game->mini_hero;
	dir = atan2(hero->dir.y, hero->dir.x);
	delta_dir = PI / 16;//hero->fov / FRM_WIDTH;
	i = -1;
	while (++i < 2 * PI / (PI / 16))
	{
		draw_pulse(dir, game);
		dir += delta_dir;
	}
}

int	game_loop(t_game *game)
{
	// printf("\tspeed=%f\t", game->hero.move_speed);
	// printf("\tspeed=%f\n", game->mini_hero.move_speed);
	move_hero(game->map, &game->hero);
	move_hero(game->map, &game->mini_hero);
	clear_image(game);
	draw_map(game);
	draw_hero(game->mini_hero.pos.x, game->mini_hero.pos.y, 5, game);
	draw_radar(game);
	// draw_sonar(game);
	draw_floor_and_ceiling(game);
	draw_walls(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}

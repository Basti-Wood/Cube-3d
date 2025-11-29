/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstorck <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 15:25:38 by bstorck           #+#    #+#             */
/*   Updated: 2025/11/21 15:25:41 by bstorck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/game.h"

void	go_slower(t_game *game)
{
	// game->hero.plane.x -= 0.01;
	// game->mini_hero.plane.x -= 0.01;
	// printf("\tFOV = %i%%\n", (int)(fabs(game->hero.plane.x/game->hero.dir.y)*100));
	game->hero.move_speed /= 1.1;
	game->hero.turn_speed /= 1.04;
	game->mini_hero.move_speed /= 1.1;
	game->mini_hero.turn_speed /= 1.04;
	// printf("\thero\t");
	// printf("\t\tmove_speed = %f\t", game->hero.move_speed);
	// printf("\tturn_speed = %f\n", game->hero.turn_speed);
	// printf("\tmini_hero");
	// printf("\tmove_speed = %f\t", game->mini_hero.move_speed);
	// printf("\tturn_speed = %f\n", game->mini_hero.turn_speed);
}

void	go_faster(t_game *game)
{
	// game->hero.plane.x += 0.01;
	// game->mini_hero.plane.x += 0.01;
	// printf("\tFOV = %i%%\n", (int)(fabs(game->hero.plane.x/game->hero.dir.y)*100));
	game->hero.move_speed *= 1.1;
	game->hero.turn_speed *= 1.04;
	game->mini_hero.move_speed *= 1.1;
	game->mini_hero.turn_speed *= 1.04;
	// printf("\thero\t");
	// printf("\t\tmove_speed = %f\t", game->hero.move_speed);
	// printf("\tturn_speed = %f\n", game->hero.turn_speed);
	// printf("\tmini_hero");
	// printf("\tmove_speed = %f\t", game->mini_hero.move_speed);
	// printf("\tturn_speed = %f\n", game->mini_hero.turn_speed);
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
	// while (/*!collision(pulse.x / BLOCK_SIZE, pulse.y / BLOCK_SIZE, game->map) && */ (sqrt(pow((pulse.x - start.x), 2) + pow((pulse.y - start.y), 2)) < 7))
	while (sqrt(pow((pulse.x - start.x), 2) + pow((pulse.y - start.y), 2)) <= game->hero.collision_radius)
	{
		// printf("\tpulse=%f\n", sqrt(powf((pulse.x - start.x), 2) +  powf((pulse.y - start.y), 2)));
		// put_pixel(pulse.x + game->w_width / 2, pulse.y, 0x00FF00, game);
		pulse.x += cos(dir);
		pulse.y += sin(dir);
	}
	put_pixel(pulse.x + (double)game->w_width / 2, pulse.y, 0x00FF00, game);
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

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
	while (/*!collision(pulse.x / BLOCK_SIZE, pulse.y / BLOCK_SIZE, game->map) && */ (sqrt(pow((pulse.x - start.x), 2) + pow((pulse.y - start.y), 2)) < 7))
	{
		// printf("\tpulse=%f\n", sqrt(powf((pulse.x - start.x), 2) +  powf((pulse.y - start.y), 2)));
		// put_pixel(pulse.x + FRM_WIDTH, pulse.y, 0x00FF00, game);
		pulse.x += cos(dir);
		pulse.y += sin(dir);
	}
	put_pixel(pulse.x + FRM_WIDTH, pulse.y, 0x00FF00, game);
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

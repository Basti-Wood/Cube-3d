/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ambulatory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstorck <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 15:24:06 by bstorck           #+#    #+#             */
/*   Updated: 2025/11/21 15:24:08 by bstorck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"

void	draw_line(int screen_x, t_game *game)
{
	int	line_height;
	int	start_y;
	int	end_y;
	int	color;

	line_height = (int)(SCRN_HEIGHT / game->hero.ray.perp_dist_wall) / 2;
	start_y = (SCRN_HEIGHT / 2) - (line_height / 2);
	if (start_y < 0)
		start_y = 0;
	end_y = (SCRN_HEIGHT / 2) + (line_height / 2);
	if (end_y < 0)
		end_y = 0;
	while (start_y <= end_y)
	{
		color = 0x0000FF;
		if (game->hero.ray.side)
			color /= 2;
		put_pixel(screen_x, start_y, color, game);
		start_y++;
	}
}

void	draw_walls(t_game *game)
{
	int			i;
	t_ray		*ray;
	t_hero		*hero;

	hero = &game->hero;
	ray = &hero->ray;
	i = -1;
	while (++i < FRM_WIDTH)
	{
		hero->scan_x = 2 * i / (double)FRM_WIDTH - 1;
		cast_ray(hero);
		dda(game);
		if (ray->side)
			ray->perp_dist_wall = ray->side_dist.y - ray->delta_dist.y;
		else
			ray->perp_dist_wall = ray->side_dist.x - ray->delta_dist.x;
		draw_line(i, game);
	}
}

void	draw_beam(double dir, t_game *game)
{
	t_vector	beam;

	beam.x = game->mini_hero.pos.x * BLOCK_SIZE;
	beam.y = game->mini_hero.pos.y * BLOCK_SIZE;
	while (!collision(beam.x / BLOCK_SIZE, beam.y / BLOCK_SIZE, game->map))
	{
		put_pixel(beam.x + FRM_WIDTH, beam.y, 0xFF0000, game);
		beam.x += cos(dir);
		beam.y += sin(dir);
	}
}

void	draw_radar(t_game *game)
{
	t_hero		*hero;
	double		dir;
	double		delta_dir;
	int			i;

	hero = &game->mini_hero;
	dir = atan2(hero->dir.y, hero->dir.x) - (hero->fov / 2);
	delta_dir = hero->fov / FRM_WIDTH;
	i = -1;
	while (++i < FRM_WIDTH)
	{
		draw_beam(dir, game);
		dir += delta_dir;
	}
}

void	draw_hero(double x, double y, int size, t_game *game)
{
	t_square	square;

	square.x = x * BLOCK_SIZE + FRM_WIDTH;
	square.y = y * BLOCK_SIZE;
	draw_filled_square(square, size, 0x00FF00, game);
	square.x = x * BLOCK_SIZE + FRM_WIDTH - size;
	draw_filled_square(square, size, 0x00FF00, game);
	square.x = x * BLOCK_SIZE + FRM_WIDTH;
	square.y = y * BLOCK_SIZE - size;
	draw_filled_square(square, size, 0x00FF00, game);
	square.x = x * BLOCK_SIZE + FRM_WIDTH - size;
	draw_filled_square(square, size, 0x00FF00, game);
}

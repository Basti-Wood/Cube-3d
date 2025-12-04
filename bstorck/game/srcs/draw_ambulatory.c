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

#include "../incs/game.h"

void	draw_line(int screen_x, t_game *game)
{
	int		color;
	// int		end_y;
	// int		start_y;
	int		line_height;
	t_line	line;

	line_height = (int)(game->w_height / game->hero.ray.perp_dist_wall) / 2;
	line.start = (game->w_height / 2) - (line_height / 2);
	if (line.start < 0)
		line.start = 0;
	line.end = (game->w_height / 2) + (line_height / 2);
	if (line.end < 0)
		line.end = 0;
	draw_line_loop(screen_x, line, line_height, game);
	// while (start_y <= end_y)
	// {
	// 	color = 0x0000FF;
	// 	if (game->hero.ray.side)
	// 		color /= 2;
	// 	put_pixel(screen_x, start_y, color, game);
	// 	start_y++;
	// }
}

void	draw_walls(t_game *game)
{
	int			i;
	t_ray		*ray;
	t_hero		*hero;

	hero = &game->hero;
	ray = &hero->ray;
	i = -1;
	while (++i < game->w_width / 2)
	{
		hero->scan_x = 2 * i / ((double)game->w_width / 2) - 1;
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
		put_pixel(beam.x + (double)game->w_width / 2, beam.y, 0xFF0000, game);
		beam.x += cos(dir);
		beam.y += sin(dir);
	}
}

void	draw_radar(t_game *game)
{
	t_hero		*hero;
	double		dir;
	double		delta_dir;
	// double		fov;
	int			i;

	hero = &game->mini_hero;
	// fov = 2 * atan(fabs(hero->plane.x + hero->plane.y) / fabs(hero->dir.x + hero->dir.y));
	dir = atan2(hero->dir.y, hero->dir.x) - (hero->fov / 2);
	delta_dir = hero->fov / ((double)game->w_width / 2);
	i = -1;
	while (++i < game->w_width / 2)
	{
		draw_beam(dir, game);
		dir += delta_dir;
	}
}

void	draw_hero(bool intro, t_vector pos, int size, t_game *game)
{
	t_square	square;
	int			offset;

	offset = 0;
	if (!intro)
		offset = game->w_width / 2;
	square.x = pos.x * BLOCK_SIZE + offset;
	square.y = pos.y * BLOCK_SIZE;
	draw_filled_square(square, size, 0x00FF00, game);
	square.x = pos.x * BLOCK_SIZE + offset - size;
	draw_filled_square(square, size, 0x00FF00, game);
	square.x = pos.x * BLOCK_SIZE + offset;
	square.y = pos.y * BLOCK_SIZE - size;
	draw_filled_square(square, size, 0x00FF00, game);
	square.x = pos.x * BLOCK_SIZE + offset - size;
	draw_filled_square(square, size, 0x00FF00, game);
}

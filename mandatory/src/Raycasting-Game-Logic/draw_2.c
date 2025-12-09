/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstorck <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 15:24:06 by bstorck           #+#    #+#             */
/*   Updated: 2025/12/04 00:14:28 by bstorck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/game.h"

void	draw_line(int screen_x, t_game *game)
{
	double	half_height;
	t_line	line;
	t_hero	*h;

	h = &game->hero;
	line.height = WIN_HEIGHT * h->ray.inv_perp_dist;
	half_height = line.height / 2;
	line.start = game->half_screen - half_height;
	if (line.start < 0)
		line.start = 0;
	line.end = game->half_screen + half_height;
	if (line.end >= WIN_HEIGHT)
		line.end = WIN_HEIGHT - 1;
	draw_line_loop(screen_x, half_height, line, game);
}

void	draw_walls(t_game *game)
{
	int		i;

	i = -1;
	while (++i < WIN_WIDTH)
	{
		game->hero.scan_x = (2.0 * i) / (double)WIN_WIDTH - 1.0;
		init_ray(&game->hero);
		dda(game);
		if (game->hero.ray.perp_dist < 1e-10)
			game->hero.ray.perp_dist = 1e-10;
		game->hero.ray.inv_perp_dist = 1.0 / game->hero.ray.perp_dist;
		draw_line(i, game);
	}
}

void	draw_beam(double dir, t_game *game)
{
	t_vector	beam;
	t_square	offset;
	double		tile_size;

	tile_size = game->map.tile_size;
	offset = get_offset(false, game);
	beam.x = game->mini_hero.pos.x * tile_size;
	beam.y = game->mini_hero.pos.y * tile_size;
	while (!collision(beam.x / tile_size, beam.y / tile_size, &game->map))
	{
		put_pixel(beam.x + offset.x, beam.y + offset.y, BEAM_CLR, game);
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
	delta_dir = (hero->fov / (double)WIN_WIDTH);
	i = -1;
	while (++i < WIN_WIDTH)
	{
		draw_beam(dir, game);
		dir += delta_dir;
	}
}

void	draw_hero(bool intro, t_vector pos, int size, t_game *game)
{
	int			color;
	t_square	square;
	t_square	offset;

	color = HERO_CLR;
	if (intro)
		color = WALKER_CLR;
	offset = get_offset(intro, game);
	square.x = pos.x * game->map.tile_size + offset.x;
	square.y = pos.y * game->map.tile_size + offset.y;
	draw_filled_square(square, size, color, game);
	square.x = pos.x * game->map.tile_size + offset.x - size;
	draw_filled_square(square, size, color, game);
	square.x = pos.x * game->map.tile_size + offset.x;
	square.y = pos.y * game->map.tile_size + offset.y - size;
	draw_filled_square(square, size, color, game);
	square.x = pos.x * game->map.tile_size + offset.x - size;
	draw_filled_square(square, size, color, game);
}

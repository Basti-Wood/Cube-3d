/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstorck <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 15:23:57 by bstorck           #+#    #+#             */
/*   Updated: 2025/12/09 07:32:48 by bstorck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/game.h"

void	draw_beam(double dir, t_game *game)
{
	t_vector	beam;
	t_square	offset;
	double		tile_size;

	tile_size = game->map.tile_size;
	offset = get_offset(false, game);
	beam.x = game->mini_hero.pos.x;
	beam.y = game->mini_hero.pos.y;
	while (!wall_collision(beam.x, beam.y, &game->map))
	{
		beam.x *= tile_size;
		beam.y *= tile_size;
		put_pixel(beam.x + offset.x, beam.y + offset.y, BEAM_COLOR, game);
		beam.x += cos(dir);
		beam.y += sin(dir);
		beam.x /= tile_size;
		beam.y /= tile_size;
	}
}

void	draw_radar(t_game *game)
{
	int			i;
	double		dir;
	double		delta_dir;
	t_hero		*hero;

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

	color = HERO_COLOR;
	if (intro)
		color = WALKER_COLOR;
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

static int	get_color(int object)
{
	if (object == 1)
		return (TILE_COLOR);
	if (object == 2)
		return (DOOR_COLOR);
	return (WHITE);
}

void	draw_map(bool intro, t_game *game)
{
	int			color;
	int			object;
	t_square	map;
	t_square	square;
	t_square	offset;

	offset = get_offset(intro, game);
	map.y = -1;
	while (++map.y < game->map.height)
	{
		map.x = -1;
		while (++map.x < game->map.width)
		{
			object = get_texture_id(map.x, map.y, &game->map);
			color = get_color(object);
			if (object)
			{
				square.x = map.x * game->map.tile_size + offset.x;
				square.y = map.y * game->map.tile_size + offset.y;
				draw_filled_square(square, game->map.tile_size, color, game);
				draw_empty_square(square, game->map.tile_size, WHITE, game);
			}
		}
	}
}

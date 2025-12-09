/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstorck <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 15:23:57 by bstorck           #+#    #+#             */
/*   Updated: 2025/12/04 00:14:21 by bstorck          ###   ########.fr       */
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
	int			i;
	double		dir;
	double		delta_dir;
	t_hero		*hero;

	hero = &game->mini_hero;
	delta_dir = (hero->fov / (double)WIN_WIDTH);
	dir = atan2(hero->dir.y, hero->dir.x) - (hero->fov / 2);
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

void	draw_map(bool intro, t_game *game)
{
	int			c;
	int			object;
	t_square	square;
	t_square	map;
	t_square	offset;

	offset = get_offset(intro, game);
	map.y = -1;
	while (++map.y < game->map.height)
	{
		map.x = -1;
		while (++map.x < game->map.width)
		{
			object = get_texture_id(map.x, map.y, &game->map);
			// if (collision(map.x, map.y, &game->map))
			if (object)
			{
				square.x = map.x * game->map.tile_size + offset.x;
				square.y = map.y * game->map.tile_size + offset.y;
				c = TILE_CLR;
				if (object == 2)
					c = DOOR_CLR;
				draw_filled_square(square, game->map.tile_size, c, game);
				draw_empty_square(square, game->map.tile_size, WHITE, game);
			}
		}
	}
}

void	draw_walker(int x, int y, t_game *game)
{
	t_vector	pos;

	pos.x = x + 0.5;
	pos.y = y + 0.5;
	clear_image(game);
	draw_map(true, game);
	draw_hero(true, pos, (TILE_SIZE / 2) - 1, game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.ptr, 0, 0);
	ft_usleep(10000);
}

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

#include "../../includes/cub3d.h"

void	draw_line(int screen_x, t_game *game)
{
	// int		color;
	// int		end_y;
	// int		start_y;
	// int		line_height;
	t_line	line;
	double	ratio;

	ratio = 1.0 * WIN_WIDTH / WIN_HEIGHT;
	line.height = (int)(WIN_HEIGHT / game->hero.ray.perp_dist_wall) / ratio;
	line.start = (WIN_HEIGHT / 2) - (line.height / 2);
	if (line.start < 0)
		line.start = 0;
	line.end = (WIN_HEIGHT / 2) + (line.height / 2);
	if (line.end < 0)
		line.end = 0;
	draw_line_loop(screen_x, line, game);
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
	while (++i < WIN_WIDTH/* / 2*/)
	{
		hero->scan_x = 2 * i / ((double)WIN_WIDTH/* / 2*/) - 1;
		cast_ray(hero);
		dda(game);
		if (ray->side)
			ray->perp_dist_wall = ray->side_dist.x - ray->delta_dist.x;
		else
			ray->perp_dist_wall = ray->side_dist.y - ray->delta_dist.y;
		draw_line(i, game);
	}
}

void	draw_beam(double dir, t_game *game)
{
	t_vector	beam;
	t_square	offset;

	// offset = (double)game->w_width / 2;
	// if (game->display_map)
		// offset = 0;
	// offset.x = 384;
	// offset.y = 60;
	offset = get_offset(false);
	beam.x = game->mini_hero.pos.x * TILE_SIZE;
	beam.y = game->mini_hero.pos.y * TILE_SIZE;
	while (!collision(beam.x / TILE_SIZE, beam.y / TILE_SIZE, &game->map))
	{
		put_pixel(beam.x + offset.x, beam.y + offset.y, 0xFFFF00, game);
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
	// draw_beam(dir, game);
	// dir = atan2(hero->dir.y, hero->dir.x) - (hero->fov / 4);
	// draw_beam(dir, game);
	// dir = atan2(hero->dir.y, hero->dir.x);
	// draw_beam(dir, game);
	// dir = atan2(hero->dir.y, hero->dir.x) + (hero->fov / 4);
	// draw_beam(dir, game);
	// dir = atan2(hero->dir.y, hero->dir.x) + (hero->fov / 2);
	// draw_beam(dir, game);
	delta_dir = (hero->fov / (double)WIN_WIDTH);
	i = -1;
	while (++i < WIN_WIDTH/* / 2*/)
	{
		draw_beam(dir, game);
		dir += delta_dir;
	}
}

void	draw_hero(bool intro, t_vector pos, int size, t_game *game)
{
	t_square	square;
	t_square	offset;

	offset = get_offset(intro);
	// 	offset = game->w_width / 2;
	// if (game->display_map)
	// 	offset = 0;
	square.x = pos.x * TILE_SIZE + offset.x;
	square.y = pos.y * TILE_SIZE + offset.y;
	draw_filled_square(square, size, 0x00FF00, game);
	square.x = pos.x * TILE_SIZE + offset.x - size;
	draw_filled_square(square, size, 0x00FF00, game);
	square.x = pos.x * TILE_SIZE + offset.x;
	square.y = pos.y * TILE_SIZE + offset.y - size;
	draw_filled_square(square, size, 0x00FF00, game);
	square.x = pos.x * TILE_SIZE + offset.x - size;
	draw_filled_square(square, size, 0x00FF00, game);
}

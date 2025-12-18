/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstorck <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 08:00:11 by bstorck           #+#    #+#             */
/*   Updated: 2025/12/09 08:03:18 by bstorck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/game.h"

void	draw_empty_square(t_square square, int size, int color, t_game *game)
{
	int	i;

	i = -1;
	while (++i <= size)
		put_pixel(square.x + i, square.y, color, game);
	i = -1;
	while (++i <= size)
		put_pixel(square.x + size, square.y + i, color, game);
	i = size;
	while (i--)
		put_pixel(square.x + i, square.y + size, color, game);
	i = size;
	while (i--)
		put_pixel(square.x, square.y + i, color, game);
}

void	draw_filled_square(t_square square, int size, int color, t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (++i <= size)
	{
		j = -1;
		while (++j <= size)
			put_pixel(square.x + i, square.y + j, color, game);
	}
}

double	get_distance(t_vector hero, t_vector sprite)
{
	double	dx;
	double	dy;

	dx = hero.x - sprite.x;
	dy = hero.y - sprite.y;
	return ((dx * dx) + (dy * dy));
}

t_vector	get_projection(t_sprite *sprite, t_hero *hero)
{
	t_vector	trans;
	t_vector	dist;
	double		inv_det;

	inv_det = 1.0 / (hero->plane.x * hero->dir.y - hero->dir.x * hero->plane.y);
	dist.x = sprite->pos.x - hero->pos.x;
	dist.y = sprite->pos.y - hero->pos.y;
	trans.x = inv_det * (hero->dir.y * dist.x - hero->dir.x * dist.y);
	trans.y = inv_det * (-hero->plane.y * dist.x + hero->plane.x * dist.y);
	return (trans);
}

t_shape	get_dimensions(int screen_x, t_vector transform, t_game *game)
{
	t_shape	shape;

	shape.height = abs((int)((double)WIN_HEIGHT / transform.y));
	shape.start_y = game->half_screen_height - (shape.height / 2);
	if (shape.start_y < 0)
		shape.start_y = 0;
	shape.end_y = game->half_screen_height + (shape.height / 2);
	if (shape.end_y >= WIN_HEIGHT)
		shape.end_y = WIN_HEIGHT - 1;
	shape.width = abs((int)((double)WIN_HEIGHT / (transform.y)));
	shape.start_x = screen_x - (shape.width / 2);
	if (shape.start_x < 0)
		shape.start_x = 0;
	shape.end_x = screen_x + (shape.width / 2);
	if (shape.end_x >= WIN_WIDTH)
		shape.end_x = WIN_WIDTH - 1;
	return (shape);
}

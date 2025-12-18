/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor_and_ceiling.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstorck <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 07:21:25 by bstorck           #+#    #+#             */
/*   Updated: 2025/12/05 07:31:54 by bstorck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/game.h"

static int	get_color(int x, int y, int tex_id, t_game *game)
{
	int			color;
	t_horizon	*h;

	h = &game->horizon;
	h->tex.x = (int)(game->texture[tex_id].width * h->pos.x)
		& (game->texture[tex_id].width - 1);
	h->tex.y = (int)(game->texture[tex_id].height * h->pos.y)
		& (game->texture[tex_id].height - 1);
	color = game->texture[tex_id].pixel_map[h->tex.y
		* game->texture[tex_id].width + h->tex.x];
	if ((tex_id == CEILING)
		&& ((game->img.width - game->map.node_size.x - 20) <= x)
		&& (x <= (game->img.width - 20))
		&& (game->img.height - game->map.node_size.y - 21) <= y
		&& (y <= (game->img.height - 21)))
		color = (color >> 1) & 0x7F7F7F;
	return (color);
}

static void	set_horizon(int y, t_game *game)
{
	t_horizon	*h;

	h = &game->horizon;
	h->p = y - game->half_screen_height;
	h->z_pos = game->half_screen_height;
	h->dist_row = h->z_pos / h->p;
	h->step.x = (h->dist_row * (h->ray_dir_end.x - h->ray_dir_start.x)
			/ game->img.width);
	h->step.y = (h->dist_row * (h->ray_dir_end.y - h->ray_dir_start.y)
			/ game->img.width);
	h->pos.x = (game->hero.pos.x + h->dist_row * h->ray_dir_start.x);
	h->pos.y = (game->hero.pos.y + h->dist_row * h->ray_dir_start.y);
}

void	draw_floor_and_ceiling(t_game *game)
{
	int			x;
	int			y;
	int			color;
	t_horizon	*h;

	h = &game->horizon;
	h->ray_dir_start.x = game->hero.dir.x - game->hero.plane.x;
	h->ray_dir_start.y = game->hero.dir.y - game->hero.plane.y;
	h->ray_dir_end.x = game->hero.dir.x + game->hero.plane.x;
	h->ray_dir_end.y = game->hero.dir.y + game->hero.plane.y;
	y = game->half_screen_height;
	while (++y < game->img.height)
	{
		set_horizon(y, game);
		x = -1;
		while (++x < game->img.width)
		{
			color = get_color(x, y, FLOOR, game);
			put_pixel(x, y, color, game);
			color = get_color(x, y, CEILING, game);
			put_pixel(x, game->img.height - y - 1, color, game);
			h->pos.x += h->step.x;
			h->pos.y += h->step.y;
		}
	}
}

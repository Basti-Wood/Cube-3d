/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstorck <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 00:14:37 by bstorck           #+#    #+#             */
/*   Updated: 2025/12/04 00:14:44 by bstorck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/game.h"

int	get_orientation(t_ray *ray)
{
	if (ray->side)
	{
		if (ray->dir.y > 0)
			return (0);
		else
			return (2);
	}
	else
	{
		if (ray->dir.x < 0)
			return (1);
		else
			return (3);
	}
	return (0);
}

static int	get_color(int o, t_square tx, t_game *g)
{
	return (g->texture[o].pixel_map[tx.y * g->texture[o].width + tx.x]);
}

int	get_texture_x(int o, t_game *g)
{
	int		tex_x;
	double	wall_x;

	if (g->hero.ray.side)
		wall_x = g->hero.pos.x + g->hero.ray.perp_dist * g->hero.ray.dir.x;
	else
		wall_x = g->hero.pos.y + g->hero.ray.perp_dist * g->hero.ray.dir.y;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)g->texture[o].width);
	if ((!g->hero.ray.side && g->hero.ray.dir.x < 0)
		|| (g->hero.ray.side && g->hero.ray.dir.y > 0))
		tex_x = g->texture[o].width - tex_x - 1;
	return (tex_x);
}

void	draw_line_loop(int screen_x, double h2, t_line line, t_game *game)
{
	int			orientation;
	int			color;
	t_square	tex;
	double		tx_pos;
	double		step;

	orientation = get_orientation(&game->hero.ray);
	tex.x = get_texture_x(orientation, game);
	step = (double)game->texture[orientation].height / (double)line.height;
	tx_pos = (line.start - (1.0 * WIN_HEIGHT) / 2 + h2) * step;
	while (line.start < line.end)
	{
		tex.y = (int)tx_pos & (game->texture->height - 1);
		color = get_color(orientation, tex, game);
		if (game->display_map)
			color = (color >> 1) & 0x7F7F7F;
		if (game->hero.ray.side)
			color = (color >> 1) & 0x7F7F7F;
		put_pixel(screen_x, line.start, color, game);
		tx_pos += step;
		line.start++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstorck <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 15:24:06 by bstorck           #+#    #+#             */
/*   Updated: 2025/12/09 08:01:03 by bstorck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/game.h"

static int	adjust_color(int color, int screen_x, t_line line, t_game *game)
{
	if (game->hero.ray.side)
		color = (color >> 1) & 0x7F7F7F;
	if (((game->img.width - game->map.node_size.x - 20) <= screen_x)
		&& (screen_x <= (game->img.width - 20))
		&& (20 <= (int)line.start)
		&& ((int)line.start <= (game->map.node_size.y + 20))
		&& game->dev_mode.render_map)
		color = (color >> 1) & 0x7F7F7F;
	return (color);
}

static void	draw_line(int screen_x, double h2, t_line line, t_game *game)
{
	int			id;
	int			color;
	t_square	tex;
	double		tx_pos;
	double		step;

	id = get_texture_id(game->hero.ray.map.x, game->hero.ray.map.y, &game->map);
	tex.x = get_texture_x(id, game);
	step = (double)game->texture[id].height / (double)line.length;
	tx_pos = (line.start - (1.0 * WIN_HEIGHT) / 2 + h2) * step;
	while (line.start < line.end)
	{
		tex.y = (int)tx_pos & (game->texture->height - 1);
		color = get_texel_color(tex, &game->texture[id]);
		color = adjust_color(color, screen_x, line, game);
		if (!(id == DOOR && color == 0x000000))
			put_pixel(screen_x, line.start, color, game);
		tx_pos += step;
		line.start++;
	}
}

void	draw_walls(t_game *game)
{
	double	half_height;
	t_line	line;
	int		screen_x;

	screen_x = -1;
	while (++screen_x < WIN_WIDTH)
	{
		game->hero.scan_x = (2.0 * screen_x) / (double)WIN_WIDTH - 1.0;
		init_ray(&game->hero);
		dda(game);
		if (game->hero.ray.perp_dist < 1e-10)
			game->hero.ray.perp_dist = 1e-10;
		game->hero.z_buffer[screen_x] = game->hero.ray.perp_dist;
		game->hero.ray.inv_perp_dist = 1.0 / game->hero.ray.perp_dist;
		line.length = WIN_HEIGHT * game->hero.ray.inv_perp_dist;
		half_height = line.length / 2;
		line.start = game->half_screen_height - half_height;
		if (line.start < 0)
			line.start = 0;
		line.end = game->half_screen_height + half_height;
		if (line.end >= WIN_HEIGHT)
			line.end = WIN_HEIGHT - 1;
		draw_line(screen_x, half_height, line, game);
	}
}

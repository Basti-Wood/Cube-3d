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

// void	draw_line(int screen_x, t_game *game)
// {
// 	double	half_height;
// 	t_line	line;
//
// 	line.height = WIN_HEIGHT * game->hero.ray.inv_perp_dist;
// 	half_height = line.height / 2;
// 	line.start = game->half_screen - half_height;
// 	if (line.start < 0)
// 		line.start = 0;
// 	line.end = game->half_screen + half_height;
// 	if (line.end >= WIN_HEIGHT)
// 		line.end = WIN_HEIGHT - 1;
// 	draw_line_loop(screen_x, half_height, line, game);
// }

void	draw_line(int screen_x, double h2, t_line line, t_game *game)
{
	int			id;
	int			color;
	t_square	tex;
	double		tx_pos;
	double		step;

	id = get_texture_id(game->hero.ray.map.x, game->hero.ray.map.y, &game->map);
	tex.x = get_texture_x(id, game);
	step = (double)game->texture[id].height / (double)line.height;
	tx_pos = (line.start - (1.0 * WIN_HEIGHT) / 2 + h2) * step;
	while (line.start < line.end)
	{
		tex.y = (int)tx_pos & (game->texture->height - 1);
		color = get_texel_color(tex, &game->texture[id]);
		if (game->hero.ray.side/* && id != DOOR*/)
			color = (color >> 1) & 0x7F7F7F;
		if (((game->img.width - game->map.node_size.x - 20) <= screen_x)
			&& (screen_x <= (game->img.width - 20))
			&& (20 <= (int)line.start)
			&& ((int)line.start <= (game->map.node_size.y + 20))
			&& game->dev_mode.render_map)
			color = (color >> 1) & 0x7F7F7F;
		if (!(id == DOOR && color == 0))
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
		// {
		// 	printf("Error: Unknown object\n");
		// 	close_game(game);
		// }
		if (game->hero.ray.perp_dist < 1e-10)
			game->hero.ray.perp_dist = 1e-10;
		game->hero.z_buffer[screen_x] = game->hero.ray.perp_dist;
		game->hero.ray.inv_perp_dist = 1.0 / game->hero.ray.perp_dist;
		// draw_line(screen_x, game);
		line.height = WIN_HEIGHT * game->hero.ray.inv_perp_dist;
		half_height = line.height / 2;
		line.start = game->half_screen - half_height;
		if (line.start < 0)
			line.start = 0;
		line.end = game->half_screen + half_height;
		if (line.end >= WIN_HEIGHT)
			line.end = WIN_HEIGHT - 1;
		draw_line(screen_x, half_height, line, game);
	}
}

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

int	door_closing(int tex_x, int tex_width, t_door *door, t_map *map)
{
	set_door_counter(door, map);
	tex_x += tex_width - door->counter * tex_width;
	if (tex_x < 0 || tex_width <= tex_x)
		return (0);
	return (tex_x);
}

int	door_opening(int tex_x, int tex_width, t_door *door, t_map *map)
{
	set_door_counter(door, map);
	tex_x += door->counter * tex_width;
	if (tex_x < 0 || tex_width <= tex_x)
		return (0);
	return (tex_x);
}

// void	legacy_floor_and_ceiling(t_game *game)
// {
// 	int	x;
// 	int	y;
// 	int	color;
//
// 	y = -1;
// 	while (++y <= WIN_HEIGHT)
// 	{
// 		x = -1;
// 		while (++x < WIN_WIDTH)
// 		{
// 			color = 0x303030;
// 			if (((game->img.width - game->map.node_size.x - 20) <= x)
// 				&& (x <= (game->img.width - 20)) && (20 <= y)
// 				&& (y <= (game->map.node_size.y + 20))
// 				&& game->dev_mode.render_map)
// 				color = (0x303030 >> 1) & 0x7F7F7F;
// 			if (y >= WIN_HEIGHT / 2)
// 				color = 0x707070;
// 			put_pixel(x, y, color, game);
// 		}
// 	}
// }

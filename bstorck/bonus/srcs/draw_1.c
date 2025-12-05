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

#include "../incs/game.h"

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

void	draw_map(bool intro, t_game *game)
{
	t_square	offset;
	t_square	square;
	t_square	map;

	offset = get_offset(intro, game);
	map.y = -1;
	while (++map.y < game->map.height)
	{
		map.x = -1;
		while (++map.x < game->map.width)
		{
			if (collision(map.x, map.y, &game->map))
			{
				square.x = map.x * game->map.tile_size + offset.x;
				square.y = map.y * game->map.tile_size + offset.y;
				draw_filled_square(square, game->map.tile_size, 0x007FAA, game);
				draw_empty_square(square, game->map.tile_size, 0xFFFFFF, game);
			}
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_static.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstorck <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 15:23:57 by bstorck           #+#    #+#             */
/*   Updated: 2025/11/21 15:23:58 by bstorck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/game.h"

void	draw_floor_and_ceiling(t_game *game)
{
	int	x;
	int	y;
	int	color;

	color = 0x303030;//0xdcdcdc;
	if (game->display_map)
		color = (color >> 1) & 8355711;
	y = -1;
	while (++y <= WIN_HEIGHT)
	{
		if (y >= WIN_HEIGHT / 2)
			color = 0x707070;//0x836953;
		if (game->display_map)
			color = (color >> 1) & 8355711;
		x = -1;
		while (++x < WIN_WIDTH/* / 2*/)
			put_pixel(x, y, color, game);
	}
}

void	draw_walker(int x, int y, t_game *game)
{
	t_vector	pos;

	pos.x = x + 0.5;
	pos.y = y + 0.5;
	clear_image(game);
	draw_map(true, game);
	draw_hero(true, pos, (TILE_SIZE / 2), game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	ft_usleep(10000);
}

void	draw_empty_square(t_square square, int size, int color, t_game *game)
{
	int	i;

	i = -1;
	while (++i < size)
		put_pixel(square.x + i, square.y, color, game);
	i = -1;
	while (++i < size)
		put_pixel(square.x + size - 1, square.y + i, color, game);
	i = size;
	while (--i)
		put_pixel(square.x + i, square.y + size - 1, color, game);
	i = size;
	while (--i)
		put_pixel(square.x, square.y + i, color, game);
}

void	draw_filled_square(t_square square, int size, int color, t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < size)
			put_pixel(square.x + i, square.y + j, color, game);
	}
}

t_square	get_offset(bool intro)
{
	t_square	offset;

	offset.x = 0;
	offset.y = 0;
	if (!intro)
	{
		offset.x = 384;
		offset.y = 60;
	}
	return (offset);
}

void	draw_map(bool intro, t_game *game)
{
	t_square	square;
	t_square	offset;
	int			x;
	int			y;
	// int			**map;
	// int			offset;

	// if (!intro)
		// offset = game->w_width / 2;
	// if (game->display_map)
		// offset = 0;
	// map = game->map;
	offset = get_offset(intro);
	y = -1;
	while (++y < game->map_height)
	{
		x = -1;
		while (++x < game->map_width)
		{
			if (game->map[y][x] > 0)
			{
				square.x = x * TILE_SIZE + offset.x;
				square.y = y * TILE_SIZE + offset.y;
				if (intro)
					draw_filled_square(square, TILE_SIZE, 0x0000FF, game);
				draw_empty_square(square, TILE_SIZE, 0xFFFFFF, game);
			}
		}
	}
}

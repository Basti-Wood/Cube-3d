/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   presenter_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstorck <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 00:31:29 by bstorck           #+#    #+#             */
/*   Updated: 2025/12/04 00:31:37 by bstorck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/game.h"

void	init_presenter_window(t_game *g)
{
	t_img	*i;

	i = &g->img;
	i->width = g->texture->width * TEXEL_SIZE;
	i->height = g->texture->height * TEXEL_SIZE;
	g->win = mlx_new_window(g->mlx, i->width, i->height, "XPM Viewer");
	i->ptr = mlx_new_image(g->mlx, i->width, i->height);
	i->data = mlx_get_data_addr(i->ptr, &i->bpp, &i->size_line, &i->endian);
	mlx_hook(g->win, 2, 1L << 0, key_press, g);
	mlx_hook(g->win, WIN_X_BTN, 0, close_game, g);
}

void	draw_texture(t_game *g)
{
	t_square	m;
	t_square	p;
	int			size;
	t_texture	*t;

	t = &g->texture[g->present_num];
	size = TEXEL_SIZE;
	p.x = 0;
	p.y = 0;
	m.y = -1;
	while (++m.y < t->height)
	{
		m.x = -1;
		while (++m.x < t->width)
		{
			p.x = m.x * size;
			p.y = m.y * size;
			draw_filled_square(p, size, t->pixel_map[m.y * t->width + m.x], g);
		}
	}
}

int	presenter_loop(t_game *game)
{
	clear_image(game);
	draw_texture(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.ptr, 0, 0);
	if (game->skip_intro)
	{
		game->skip_intro = false;
		mlx_destroy_image(game->mlx, game->img.ptr);
		mlx_destroy_window(game->mlx, game->win);
	}
	return (0);
}

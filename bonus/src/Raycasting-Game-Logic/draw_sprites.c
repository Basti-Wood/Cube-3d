/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstorck <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 08:30:42 by bstorck           #+#    #+#             */
/*   Updated: 2025/12/09 08:03:18 by bstorck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/game.h"

static void	sort_sprites_by_distance(t_map *map)
{
	int	i;
	int	j;
	int	tmp;

	i = 1;
	while (i < map->num_sprites)
	{
		tmp = map->render_order[i];
		j = i - 1;
		while (map->sprite[map->render_order[j]].dist < map->sprite[tmp].dist)
		{
			map->render_order[j + 1] = map->render_order[j];
			j--;
			if (j < 0)
				break ;
		}
		map->render_order[j + 1] = tmp;
		i++;
	}
}

static void	shift_cells(t_sprite *sprite)
{
	int	i;
	int	tmp;

	if (sprite->tex_id[1] == 0)
		return ;
	tmp = sprite->tex_id[0];
	i = -1;
	while (++i < MAX_CELLS - 1)
		sprite->tex_id[i] = sprite->tex_id[i + 1];
	sprite->tex_id[i] = tmp;
	sprite->last_shift = get_current_time();
}

static void	draw_line(t_sprite *sprite, t_shape shape, t_square t, t_game *game)
{
	int	color;
	int	tex_pos;
	int	tex_height;

	tex_height = game->texture[sprite->tex_id[0]].height;
	shape.y = shape.start_y - 1;
	while (++shape.y < shape.end_y)
	{
		tex_pos = 256 * shape.y + shape.height * 128 - WIN_HEIGHT * 128;
		t.y = (tex_pos * tex_height) / (shape.height * 256);
		if (sprite->animated)
			if (get_current_time() > (sprite->last_shift + rand()))
				shift_cells(sprite);
		color = get_texel_color(t, &game->texture[sprite->tex_id[0]]);
		if (((game->img.width - game->map.node_size.x - 20) <= shape.x)
			&& (shape.x <= (game->img.width - 20))
			&& (20 <= shape.y)
			&& (shape.y <= (game->map.node_size.y + 20)))
			color = (color >> 1) & 0x7F7F7F;
		if (color != 0x000000)
			put_pixel(shape.x, shape.y, color, game);
	}
}

static void	draw_sprite(int sprite_id, t_game *game)
{
	int			screen_x;
	t_square	tex;
	t_shape		shape;
	t_vector	trans;
	t_sprite	*sprite;

	sprite = &game->map.sprite[sprite_id];
	trans = get_projection(sprite, &game->hero);
	screen_x = (int)(game->half_screen_width * (1 + trans.x / trans.y));
	shape = get_dimensions(screen_x, trans, game);
	shape.x = shape.start_x - 1;
	while (++shape.x < shape.end_x)
	{
		tex.x = (int)((shape.x - (screen_x - (shape.width / 2)))
				* (game->texture[sprite->tex_id[0]].width / shape.width));
		if ((0 < trans.y) && (trans.y < game->hero.z_buffer[shape.x])
			&& (0 < shape.x) && (shape.x < WIN_WIDTH))
			draw_line(sprite, shape, tex, game);
	}
}

void	draw_sprites(t_game *g)
{
	int			i;
	t_sprite	*sprite;

	sprite = g->map.sprite;
	if (g->hero.axes_of_travel > 0)
	{
		i = -1;
		while (++i < g->map.num_sprites)
			sprite[i].dist = get_distance(g->hero.pos, sprite[i].pos);
		sort_sprites_by_distance(&g->map);
	}
	i = -1;
	while (++i < g->map.num_sprites)
		draw_sprite(g->map.render_order[i], g);
}

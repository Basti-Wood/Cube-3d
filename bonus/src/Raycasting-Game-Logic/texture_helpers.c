/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstorck <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 01:08:35 by bstorck           #+#    #+#             */
/*   Updated: 2025/12/18 01:08:41 by bstorck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/game.h"

int	get_texture_id(int x, int y, t_map *map)
{
	return (map->grid[y * map->width + x]);
}

int	get_texel_color(t_square tex, t_texture *texture)
{
	return (texture->pixel_map[tex.y * texture->width + tex.x]);
}

static int	door_closing(int tex_x, int tex_width, t_door *door, t_map *map)
{
	set_door_counter(door, map);
	tex_x += tex_width - door->counter * tex_width;
	if (tex_x < 0 || tex_width <= tex_x)
		return (0);
	return (tex_x);
}

static int	door_opening(int tex_x, int tex_width, t_door *door, t_map *map)
{
	set_door_counter(door, map);
	tex_x += door->counter * tex_width;
	if (tex_x < 0 || tex_width <= tex_x)
		return (0);
	return (tex_x);
}

int	get_texture_x(int id, t_game *g)
{
	t_door	*door;
	int		tex_x;
	double	wall_x;

	if (g->hero.ray.side)
		wall_x = g->hero.pos.x + g->hero.ray.perp_dist * g->hero.ray.dir.x;
	else
		wall_x = g->hero.pos.y + g->hero.ray.perp_dist * g->hero.ray.dir.y;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)g->texture[id].width);
	if (id == DOOR)
	{
		door = get_door(g->hero.ray.map.x, g->hero.ray.map.y, &g->map);
		if (door->state == OPENING)
			return (door_opening(tex_x, g->texture[DOOR].width, door, &g->map));
		else if (door->state == CLOSING)
			return (door_closing(tex_x, g->texture[DOOR].width, door, &g->map));
		else
			return (tex_x);
	}
	else if ((!g->hero.ray.side && g->hero.ray.dir.x < 0)
		|| (g->hero.ray.side && g->hero.ray.dir.y > 0))
		tex_x = g->texture[id].width - tex_x - 1;
	return (tex_x);
}

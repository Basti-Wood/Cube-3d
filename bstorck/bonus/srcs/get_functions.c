/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstorck <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 00:15:04 by bstorck           #+#    #+#             */
/*   Updated: 2025/12/04 00:15:05 by bstorck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/game.h"

int	get_fd(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("Error");
		return (-1);
	}
	return (fd);
}

t_square	get_offset(bool intro, t_game *game)
{
	t_square	offset;

	offset.x = 0;
	offset.y = 0;
	if (!intro)
	{
		offset.x = (game->img.width - game->map.node_size.x - 20);
		if (offset.x < 0 || game->img.width < offset.x)
			offset.x = 0;
		offset.y = 20;
	}
	return (offset);
}

int	get_texel_color(t_square tex, t_texture *texture)
{
	if (tex.x > 63)
		printf("\tDING!\t%i\n", tex.x);
	return (texture->pixel_map[tex.y * texture->width + tex.x]);
}

t_door	*get_door(int x, int y, t_map *map)
{
	int	i;

	i = -1;
	while (++i < map->number_of_doors)
	{
		if (map->door[i].pos.x == x && map->door[i].pos.y == y)
			return (&map->door[i]);
	}
	return (NULL);
}

static int	door_closing(int tex_x, int tex_width, t_door *door, t_map *map)
{
	set_door_counter(door, map);
	// int old_tex_x = tex_x;
	tex_x += tex_width - door->counter * tex_width;
	// printf("\t%i = %i + %i - %f * %i\n", tex_x, old_tex_x, tex_width, door->counter, tex_width);
	if (tex_x < 0 || tex_width <= tex_x)
		return (0);
	return (tex_x);
}

static int	door_opening(int tex_x, int tex_width, t_door *door, t_map *map)
{
	// printf("\ttex_x = %i\n", tex_x);
	// door = get_door(g->hero.ray.map.x, g->hero.ray.map.y, &g->map);
	// printf("\ttexture width = %i\n", g->texture[DOOR].width);
	// if (door->state == OPENING || door->state == CLOSING)
	// set_door_counter(door, map);
	// else
		// door->counter = 0;
	set_door_counter(door, map);
	// int old_tex_x = tex_x;
	tex_x += door->counter * tex_width;
	// printf("\t%i = %i + %f * %i\n", tex_x, old_tex_x, door->counter, tex_width);
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
	if ((!g->hero.ray.side && g->hero.ray.dir.x < 0)
		|| (g->hero.ray.side && g->hero.ray.dir.y > 0))
		tex_x = g->texture[id].width - tex_x - 1;
	return (tex_x);
}

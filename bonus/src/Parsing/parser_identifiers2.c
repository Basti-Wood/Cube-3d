/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_identifiers2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstorck <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 00:14:56 by bstorck           #+#    #+#             */
/*   Updated: 2025/12/04 00:14:57 by bstorck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

double	ft_atod(const char *str);

static int	get_sprite_type(char *type_str)
{
	if (ft_strncmp(type_str, "BARREL", 7) == 0)
		return (BARREL);
	else if (ft_strncmp(type_str, "PILLAR", 7) == 0)
		return (PILLAR);
	else if (ft_strncmp(type_str, "LIGHT", 6) == 0)
		return (LIGHT);
	else if (ft_strncmp(type_str, "TREE", 5) == 0)
		return (TREE_0);
	return (-1);
}

// static int	add_tree_sprite(t_game *game, double x, double y)
// {
// 	int	idx;
//
// 	idx = game->sprites.tree_count;
// 	if (idx >= MAX_SPRITES)
// 	{
// 		printf("Error: Maximum number of trees exceeded\n");
// 		return (0);
// 	}
// 	game->sprites.trees[idx].pos.x = x;
// 	game->sprites.trees[idx].pos.y = y;
// 	game->sprites.trees[idx].current_frame = 0;
// 	game->sprites.trees[idx].last_frame_time = 0;
// 	game->sprites.trees[idx].animation_speed = ANIMATION_STEP;
// 	game->sprites.tree_count++;
// 	return (1);
// }

static void	handle_tree_sprite(int sprite_id, t_game *game)
{
	game->map.sprite[sprite_id].animated = true;
	game->map.sprite[sprite_id].tex_id[1] = TREE_1;
	game->map.sprite[sprite_id].tex_id[2] = TREE_2;
	game->map.sprite[sprite_id].tex_id[3] = TREE_3;
	game->map.sprite[sprite_id].tex_id[4] = TREE_4;
}

static int	add_sprite(t_game *game, double x, double y, int type)
{
	int	i;
	int	sprite_id;

	// idx = game->sprites.count;
	// if (idx >= MAX_SPRITES)
	// {
	// 	printf("Error: Maximum number of sprites exceeded\n");
	// 	return (0);
	// }
	// game->sprites.sprites[idx].pos.x = x;
	// game->sprites.sprites[idx].pos.y = y;
	// game->sprites.sprites[idx].type = type;
	// game->sprites.sprites[idx].distance = 0;
	// game->sprites.sprites[idx].visible = true;
	// game->sprites.count++;
	sprite_id = game->map.num_sprites;
	if (sprite_id >= MAX_SPRITES)
	{
		printf("Error: Maximum number of sprites exceeded\n");
		return (0);
	}
	game->map.sprite[sprite_id].pos.x = x;
	game->map.sprite[sprite_id].pos.y = y;
	game->map.sprite[sprite_id].dist = 0;
	game->map.sprite[sprite_id].impermeable = true;
	if (type == LIGHT)
		game->map.sprite[sprite_id].impermeable = false;
	game->map.sprite[sprite_id].animated = false;
	game->map.sprite[sprite_id].last_shift = 0;
	i = -1;
	while (++i < MAX_CELLS)
		game->map.sprite[sprite_id].tex_id[i] = 0;
	game->map.sprite[sprite_id].tex_id[0] = type;
	if (type == TREE_0)
		handle_tree_sprite(sprite_id, game);
	return (1);
}

t_vector	pos;
double		dist;
bool		impermeable;
bool		animated;
time_t		last_shift;
int			tex_id[MAX_CELLS];

int	parse_sprite_identifier(char *value, t_game *game)
{
	char	**parts;
	double	x;
	double	y;
	int		type;
	int		result;

	parts = ft_split(value, ' ');
	if (!parts || !parts[0] || !parts[1] || !parts[2])
	{
		printf("Error: Invalid sprite format (expected: SP X Y TYPE)\n");
		free_tokens((void **)parts);
		return (0);
	}
	x = ft_atod(parts[0]);
	y = ft_atod(parts[1]);
	type = get_sprite_type(parts[2]);
	if (type == -1)
	{
		printf("Error: Unknown sprite type: %s\n", parts[2]);
		free_tokens((void **)parts);
		return (0);
	}
	// if (type == -2)
	// 	result = add_tree_sprite(game, x, y);
	// else
	// 	result = add_regular_sprite(game, x, y, type);
	result = add_sprite(game, x, y, type);
	free_tokens((void **)parts);
	return (result);
}

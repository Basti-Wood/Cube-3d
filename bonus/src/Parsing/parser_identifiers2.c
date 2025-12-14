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
		return (-2);
	return (-1);
}

static int	add_tree_sprite(t_game *game, double x, double y)
{
	int	idx;

	idx = game->sprites.tree_count;
	if (idx >= MAX_SPRITES)
	{
		printf("Error: Maximum number of trees exceeded\n");
		return (0);
	}
	game->sprites.trees[idx].pos.x = x;
	game->sprites.trees[idx].pos.y = y;
	game->sprites.trees[idx].current_frame = 0;
	game->sprites.trees[idx].last_frame_time = 0;
	game->sprites.trees[idx].animation_speed = ANIMATION_STEP;
	game->sprites.tree_count++;
	return (1);
}

static int	add_regular_sprite(t_game *game, double x, double y, int type)
{
	int	idx;

	idx = game->sprites.count;
	if (idx >= MAX_SPRITES)
	{
		printf("Error: Maximum number of sprites exceeded\n");
		return (0);
	}
	game->sprites.sprites[idx].pos.x = x;
	game->sprites.sprites[idx].pos.y = y;
	game->sprites.sprites[idx].type = type;
	game->sprites.sprites[idx].distance = 0;
	game->sprites.sprites[idx].visible = true;
	game->sprites.count++;
	return (1);
}

int	parse_sprite_identifier(char *value, t_game *game)
{
	char			**parts;
	double			x;
	double			y;
	int				type;
	int				result;

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
	if (type == -2)
		result = add_tree_sprite(game, x, y);
	else
		result = add_regular_sprite(game, x, y, type);
	free_tokens((void **)parts);
	return (result);
}

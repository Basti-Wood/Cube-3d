/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_identifiers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstorck <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 00:14:56 by bstorck           #+#    #+#             */
/*   Updated: 2025/12/04 00:14:57 by bstorck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	handle_texture(int tex_id, char *name, char *value, t_game *game)
{
	if (game->texture_path[tex_id])
	{
		printf("Error: Duplicate %s identifier\n", name);
		return (0);
	}
	return (parse_texture(value, &game->texture_path[tex_id]));
}

static int	handle_asprite_texture(int tex_id, char *name, char *value,
	t_game *game)
{
	if (game->asprite_path[tex_id])
	{
		printf("Error: Duplicate %s identifier\n", name);
		return (0);
	}
	return (parse_texture(value, &game->asprite_path[tex_id]));
}

static int	parse_basic_textures(char *id, char *value, t_game *game)
{
	if (ft_strncmp(id, "FLOOR", 6) == 0)
		return (handle_texture(FLOOR, "FLOOR", value, game));
	else if (ft_strncmp(id, "CEILING", 8) == 0)
		return (handle_texture(CEILING, "CEILING", value, game));
	else if (ft_strncmp(id, "WALL", 5) == 0)
		return (handle_texture(WALL, "WALL", value, game));
	else if (ft_strncmp(id, "DOOR", 5) == 0)
		return (handle_texture(DOOR, "DOOR", value, game));
	return (-1);
}

static int	parse_sprite_textures(char *id, char *value, t_game *game)
{
	if (ft_strncmp(id, "BARREL", 7) == 0)
		return (handle_texture(BARREL, "BARREL", value, game));
	else if (ft_strncmp(id, "PILLAR", 7) == 0)
		return (handle_texture(PILLAR, "PILLAR", value, game));
	else if (ft_strncmp(id, "LIGHT", 6) == 0)
		return (handle_texture(LIGHT, "LIGHT", value, game));
	return (-1);
}

static int	parse_tree_textures(char *id, char *value, t_game *game)
{
	if (ft_strncmp(id, "TREE1", 6) == 0)
		return (handle_asprite_texture(TREE1, "TREE1", value, game));
	else if (ft_strncmp(id, "TREE2", 6) == 0)
		return (handle_asprite_texture(TREE2, "TREE2", value, game));
	else if (ft_strncmp(id, "TREE3", 6) == 0)
		return (handle_asprite_texture(TREE3, "TREE3", value, game));
	else if (ft_strncmp(id, "TREE4", 6) == 0)
		return (handle_asprite_texture(TREE4, "TREE4", value, game));
	else if (ft_strncmp(id, "TREE5", 6) == 0)
		return (handle_asprite_texture(TREE5, "TREE5", value, game));
	return (-1);
}

int	parse_texture_identifier(char *id, char *value, t_game *game)
{
	int	result;

	result = parse_basic_textures(id, value, game);
	if (result != -1)
		return (result);
	result = parse_sprite_textures(id, value, game);
	if (result != -1)
		return (result);
	return (parse_tree_textures(id, value, game));
}

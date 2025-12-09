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

static int	handle_north_texture(char *value, t_game *game)
{
	if (game->texture_path[NORTH])
	{
		printf("Error: Duplicate NO identifier\n");
		return (0);
	}
	return (parse_texture(value, &game->texture_path[NORTH]));
}

static int	handle_south_texture(char *value, t_game *game)
{
	if (game->texture_path[SOUTH])
	{
		printf("Error: Duplicate SO identifier\n");
		return (0);
	}
	return (parse_texture(value, &game->texture_path[SOUTH]));
}

static int	handle_west_texture(char *value, t_game *game)
{
	if (game->texture_path[WEST])
	{
		printf("Error: Duplicate WE identifier\n");
		return (0);
	}
	return (parse_texture(value, &game->texture_path[WEST]));
}

static int	handle_east_texture(char *value, t_game *game)
{
	if (game->texture_path[EAST])
	{
		printf("Error: Duplicate EA identifier\n");
		return (0);
	}
	return (parse_texture(value, &game->texture_path[EAST]));
}

int	parse_texture_identifier(char *id, char *value, t_game *game)
{
	if (ft_strncmp(id, "NO", 3) == 0)
		return (handle_north_texture(value, game));
	else if (ft_strncmp(id, "SO", 3) == 0)
		return (handle_south_texture(value, game));
	else if (ft_strncmp(id, "WE", 3) == 0)
		return (handle_west_texture(value, game));
	else if (ft_strncmp(id, "EA", 3) == 0)
		return (handle_east_texture(value, game));
	return (-1);
}

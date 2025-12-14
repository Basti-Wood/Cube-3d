/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_config_init.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstorck <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 00:14:56 by bstorck           #+#    #+#             */
/*   Updated: 2025/12/04 00:14:57 by bstorck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	init_config(t_game *game)
{
	int	i;

	i = 0;
	while (i < NUM_TEXTURES)
	{
		game->texture[i].pixel_map = NULL;
		game->texture_path[i] = NULL;
		i++;
	}
	i = 0;
	while (i < NUM_ASPRITE_FRAMES)
	{
		game->asprite_texture[i].pixel_map = NULL;
		game->asprite_path[i] = NULL;
		i++;
	}
	game->sprites.count = 0;
	game->sprites.tree_count = 0;
}

void	init_game_for_parsing(t_game *game)
{
	init_config(game);
	game->map.grid = NULL;
	game->map.width = 0;
	game->map.height = 0;
	game->map.player.x = -1;
	game->map.player.y = -1;
	game->map.player_dir = '\0';
}

int	config_complete(t_game *game)
{
	int	i;

	i = 0;
	while (i < NUM_TEXTURES)
	{
		if (!game->texture_path[i])
			return (0);
		i++;
	}
	i = 0;
	while (i < NUM_ASPRITE_FRAMES)
	{
		if (!game->asprite_path[i])
			return (0);
		i++;
	}
	return (1);
}

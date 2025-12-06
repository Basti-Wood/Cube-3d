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
		game->texture_paths[i] = NULL;
		i++;
	}
	game->floor_color = -1;
	game->ceiling_color = -1;
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
		if (!game->texture_paths[i])
			return (0);
		i++;
	}
	if (game->floor_color < 0 || game->ceiling_color < 0)
		return (0);
	return (1);
}

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
	int			i;
	int			j;
	t_sprite	*sprite;

	sprite = game->map.sprite;
	i = 0;
	while (i < MAX_TEXTURES)
	{
		game->texture[i].pixel_map = NULL;
		game->texture_path[i] = NULL;
		i++;
	}
	i = -1;
	while (++i < MAX_SPRITES)
	{
		game->map.render_order[i] = i;
		sprite[i].pos.x = 0;
		sprite[i].pos.y = 0;
		sprite[i].dist = 0;
		sprite[i].impermeable = true;
		sprite[i].animated = false;
		sprite[i].last_shift = 0;
		j = -1;
		while (++j < MAX_CELLS)
			sprite[i].tex_id[j] = 0;
	}
	// i = 0;
	// while (i < NUM_ASPRITE_FRAMES)
	// {
	// 	game->asprite_texture[i].pixel_map = NULL;
	// 	game->asprite_path[i] = NULL;
	// 	i++;
	// }
	// game->sprites.count = 0;
	// game->sprites.tree_count = 0;
}

void	init_game_for_parsing(t_game *game)
{
	init_config(game);
	game->map.grid = NULL;
	game->map.width = 0;
	game->map.height = 0;
	game->map.tile_size = 0;
	game->map.node_size.x = 0;
	game->map.node_size.y = 0;
	game->map.player.x = -1;
	game->map.player.y = -1;
	game->map.player_dir = '\0';
	game->map.num_doors = 0;
	game->map.num_sprites = 0;
}

int	config_complete(t_game *game)
{
	int	i;

	i = 0;
	while (i < MAX_TEXTURES)
	{
		if (!game->texture_path[i])
			return (0);
		i++;
	}
	// i = 0;
	// while (i < NUM_ASPRITE_FRAMES)
	// {
	// 	if (!game->asprite_path[i])
	// 		return (0);
	// 	i++;
	// }
	return (1);
}

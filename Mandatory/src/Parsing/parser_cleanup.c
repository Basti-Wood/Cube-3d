/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cleanup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstorck <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 00:14:56 by bstorck           #+#    #+#             */
/*   Updated: 2025/12/04 00:14:57 by bstorck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	free_texture_path_internal(char **texture)
{
	if (*texture)
	{
		free(*texture);
		*texture = NULL;
	}
}

void	free_texture_paths(t_game *game)
{
	int	i;

	if (!game)
		return ;
	i = 0;
	while (i < NUM_TEXTURES)
	{
		free_texture_path_internal(&game->texture_paths[i]);
		i++;
	}
}

void	free_map(t_map *map)
{
	if (!map || !map->grid)
		return ;
	free(map->grid);
	map->grid = NULL;
}

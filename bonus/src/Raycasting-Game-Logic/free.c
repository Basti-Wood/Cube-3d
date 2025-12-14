/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstorck <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 00:13:31 by bstorck           #+#    #+#             */
/*   Updated: 2025/12/09 07:33:17 by bstorck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/game.h"

void	free_tokens(void **token)
{
	int	i;

	i = -1;
	while (token[++i])
	{
		free(token[i]);
		token[i] = NULL;
	}
	free(token);
	token = NULL;
}

void	free_texture(t_texture *texture)
{
	if (texture->pixel_map)
	{
		free(texture->pixel_map);
		texture->pixel_map = NULL;
	}
}

void	free_all_textures(t_game *game)
{
	int	i;

	i = -1;
	while (++i < NUM_TEXTURES)
		free_texture(&game->texture[i]);
	i = -1;
	while (++i < NUM_ASPRITE_FRAMES)
		free_texture(&game->asprite_texture[i]);
}

void	free_game_map(t_game *game)
{
	if (game->map.grid)
	{
		free(game->map.grid);
		game->map.grid = NULL;
	}
}

void	free_game_resources(t_game *game)
{
	if (game->img.ptr)
	{
		mlx_destroy_image(game->mlx, game->img.ptr);
		game->img.ptr = NULL;
	}
	if (game->win)
	{
		mlx_destroy_window(game->mlx, game->win);
		game->win = NULL;
	}
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}
	free_texture_paths(game);
	free_all_textures(game);
	free_game_map(game);
}

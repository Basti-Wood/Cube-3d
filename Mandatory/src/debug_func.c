/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_xpm_file2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstorck <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 00:31:19 by bstorck           #+#    #+#             */
/*   Updated: 2025/12/04 00:31:20 by bstorck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	print_map_row(const int *row, int width)
{
	int	x;

	x = 0;
	while (x < width)
	{
		if (row[x] == 1)
			printf("█");
		else if (row[x] == 0)
			printf("·");
		else if (row[x] == 'N' || row[x] == 'S'
			|| row[x] == 'E' || row[x] == 'W')
			printf("\033[1;32m%c\033[0m", (char)row[x]);
		else if (row[x] == ' ')
			printf(" ");
		else
			printf("?");
		x++;
	}
}

void	display_text(t_game *game)
{
	printf("📁 Textures:\n");
	printf("   North: %s\n", game->texture_paths[0]);
	printf("   South: %s\n", game->texture_paths[1]);
	printf("   West:  %s\n", game->texture_paths[2]);
	printf("   East:  %s\n", game->texture_paths[3]);
	printf("\n🎨 Colors:\n");
	printf("   Floor:   0x%06X\n", game->floor_color);
	printf("   Ceiling: 0x%06X\n", game->ceiling_color);
	printf("\n🗺️  Map: %dx%d\n", game->map.width, game->map.height);
	printf("Player at (%d, %d) facing '%c'\n",
		game->map.player.x, game->map.player.y, game->map.player_dir);
	printf("\n Legend: █ = Wall  · = Floor  N/S/E/W = Player\n\n");
}

void	display_map(t_game *game)
{
	int	y;

	printf("\n");
	printf("╔══════════════════════════════════════════════════════╗\n");
	printf("║                  CUB3D MAP DISPLAY                   ║\n");
	printf("╚══════════════════════════════════════════════════════╝\n\n");
	display_text(game);
	y = 0;
	while (y < game->map.height)
	{
		printf("   ");
		print_map_row(&game->map.grid[y * game->map.width], game->map.width);
		printf("\n");
		y++;
	}
	printf("\n");
}

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
		else if (row[x] == 2)
			printf("*");
		else
			printf("?");
		x++;
	}
}

void	display_text(t_game *game)
{
	printf("📁 Textures:\n");
	printf("   Floor:   %s\n", game->texture_path[FLOOR]);
	printf("   Ceiling: %s\n", game->texture_path[CEILING]);
	printf("   Wall:    %s\n", game->texture_path[WALL]);
	printf("   Door:    %s\n", game->texture_path[DOOR]);
	printf("   Barrel:  %s\n", game->texture_path[BARREL]);
	printf("   Pillar:  %s\n", game->texture_path[PILLAR]);
	printf("   Light:   %s\n", game->texture_path[LIGHT]);
	printf("\n🎬 Animated Sprites:\n");
	printf("   Tree1:   %s\n", game->texture_path[TREE_0]);
	printf("   Tree2:   %s\n", game->texture_path[TREE_1]);
	printf("   Tree3:   %s\n", game->texture_path[TREE_2]);
	printf("   Tree4:   %s\n", game->texture_path[TREE_3]);
	printf("   Tree5:   %s\n", game->texture_path[TREE_4]);
	printf("\n🎮 Sprites: %d\n",
		game->map.num_sprites);
	printf("\n🗺️  Map: %dx%d\n", game->map.width, game->map.height);
	printf("Player at (%d, %d) facing '%c'\n",
		game->map.player.x, game->map.player.y, game->map.player_dir);
	printf("\n Legend: █ = Wall  · = Floor  * = Door  N/S/E/W = Player\n\n");
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

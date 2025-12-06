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
		else if (row[x] == 'N' || row[x] == 'S' || row[x] == 'E' || row[x] == 'W')
			printf("\033[1;32m%c\033[0m", (char)row[x]);
		else if (row[x] == ' ')
			printf(" ");
		else
			printf("?");
		x++;
	}
}

void	display_map(t_game *game)
{
	int	y;

	printf("\n");
	printf("╔════════════════════════════════════════════════════════════╗\n");
	printf("║                    CUB3D MAP DISPLAY                       ║\n");
	printf("╚════════════════════════════════════════════════════════════╝\n\n");
	
	printf("📁 Textures:\n");
	printf("   North: %s\n", game->texture_paths[0]);
	printf("   South: %s\n", game->texture_paths[1]);
	printf("   West:  %s\n", game->texture_paths[2]);
	printf("   East:  %s\n", game->texture_paths[3]);
	
	printf("\n🎨 Colors:\n");
	printf("   Floor:   0x%06X\n", game->floor_color);
	printf("   Ceiling: 0x%06X\n", game->ceiling_color);
	
	printf("\n🗺️  Map: %dx%d\n", game->map.width, game->map.height);
	printf("   Player at (%d, %d) facing '%c'\n", game->map.player.x, game->map.player.y, game->map.player_dir);
	
	printf("\n   Legend: █ = Wall  · = Floor  \033[1;32mN/S/E/W\033[0m = Player\n\n");
	
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

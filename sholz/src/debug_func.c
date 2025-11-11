#include "../includes/cub3d.h"

void	print_map_row(const char *row)
{
	int	x;

	x = 0;
	while (row[x])
	{
		if (row[x] == '1')
			printf("█");
		else if (row[x] == '0')
			printf("·");
		else if (row[x] == 'N' || row[x] == 'S' || row[x] == 'E' || row[x] == 'W')
			printf("\033[1;32m%c\033[0m", row[x]);
		else if (row[x] == ' ')
			printf(" ");
		else
			printf("%c", row[x]);
		x++;
	}
}

void	display_map(t_map *map, t_config *config)
{
	int	y;

	printf("\n");
	printf("╔════════════════════════════════════════════════════════════╗\n");
	printf("║                    CUB3D MAP DISPLAY                       ║\n");
	printf("╚════════════════════════════════════════════════════════════╝\n\n");
	
	printf("📁 Textures:\n");
	printf("   North: %s\n", config->north_tex);
	printf("   South: %s\n", config->south_tex);
	printf("   East:  %s\n", config->east_tex);
	printf("   West:  %s\n", config->west_tex);
	
	printf("\n🎨 Colors:\n");
	printf("   Floor:   RGB(%d, %d, %d)\n", config->floor_r, config->floor_g, config->floor_b);
	printf("   Ceiling: RGB(%d, %d, %d)\n", config->ceiling_r, config->ceiling_g, config->ceiling_b);
	
	printf("\n🗺️  Map: %dx%d\n", map->width, map->height);
	printf("   Player at (%d, %d) facing '%c'\n", map->player.x, map->player.y, map->player_dir);
	
	printf("\n   Legend: █ = Wall  · = Floor  \033[1;32mN/S/E/W\033[0m = Player\n\n");
	
	y = 0;
	while (y < map->height)
	{
		printf("   ");
		if (map->grid[y])
			print_map_row(map->grid[y]);
		printf("\n");
		y++;
	}
	printf("\n");
}

#include "../includes/cub3d.h"

int main(int argc, char **argv)
{
	t_config config;
	t_map map;

	if (argc < 2) {
		printf("./cube3d <map.cub>\n");
		return 1;
	}
	if (!parse_cub_file(argv[1], &config, &map)) {
		printf("Error: Failed to parse map\n");
		return 1;
	}
	free_config(&config);
	free_map(&map);
	return 0;
}
#include "../../includes/cub3d.h"

static void	free_texture(char **texture)
{
	if (*texture)
	{
		free(*texture);
		*texture = NULL;
	}
}

void	free_config(t_config *config)
{
	if (!config)
		return ;
	free_texture(&config->north_tex);
	free_texture(&config->south_tex);
	free_texture(&config->east_tex);
	free_texture(&config->west_tex);
}

static void	free_grid_row(char **row)
{
	if (*row)
	{
		free(*row);
		*row = NULL;
	}
}

static void	free_grid_rows(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->height && map->grid[i])
	{
		free_grid_row(&map->grid[i]);
		i++;
	}
}

void	free_map(t_map *map)
{
	if (!map || !map->grid)
		return ;
	free_grid_rows(map);
	free(map->grid);
	map->grid = NULL;
}

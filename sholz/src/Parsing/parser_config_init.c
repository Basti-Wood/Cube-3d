#include "../../includes/cub3d.h"

void	init_config(t_config *config)
{
	config->north_tex = NULL;
	config->south_tex = NULL;
	config->east_tex = NULL;
	config->west_tex = NULL;
	config->floor_color = -1;
	config->ceiling_color = -1;
}

int	config_complete(t_config *config)
{
	if (!config->north_tex || !config->south_tex)
		return (0);
	if (!config->east_tex || !config->west_tex)
		return (0);
	if (config->floor_color < 0 || config->ceiling_color < 0)
		return (0);
	return (1);
}

#include "../../includes/cub3d.h"

static int	handle_floor_color(char *value, t_config *config)
{
	if (config->floor_color != -1)
	{
		printf("Error: Duplicate F identifier\n");
		return (0);
	}
	if (!parse_color(value, &config->floor_r,
			&config->floor_g, &config->floor_b))
		return (0);
	config->floor_color = rgb_to_int(config->floor_r,
			config->floor_g, config->floor_b);
	return (1);
}

static int	handle_ceiling_color(char *value, t_config *config)
{
	if (config->ceiling_color != -1)
	{
		printf("Error: Duplicate C identifier\n");
		return (0);
	}
	if (!parse_color(value, &config->ceiling_r,
			&config->ceiling_g, &config->ceiling_b))
		return (0);
	config->ceiling_color = rgb_to_int(config->ceiling_r,
			config->ceiling_g, config->ceiling_b);
	return (1);
}

int	parse_color_identifier(char *id, char *value, t_config *config)
{
	if (strcmp(id, "F") == 0)
		return (handle_floor_color(value, config));
	else if (strcmp(id, "C") == 0)
		return (handle_ceiling_color(value, config));
	return (-1);
}

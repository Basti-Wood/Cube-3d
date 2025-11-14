#include "../../includes/cub3d.h"

static int	handle_north_texture(char *value, t_config *config)
{
	if (config->north_tex)
	{
		printf("Error: Duplicate NO identifier\n");
		return (0);
	}
	return (parse_texture(value, &config->north_tex));
}

static int	handle_south_texture(char *value, t_config *config)
{
	if (config->south_tex)
	{
		printf("Error: Duplicate SO identifier\n");
		return (0);
	}
	return (parse_texture(value, &config->south_tex));
}

static int	handle_west_texture(char *value, t_config *config)
{
	if (config->west_tex)
	{
		printf("Error: Duplicate WE identifier\n");
		return (0);
	}
	return (parse_texture(value, &config->west_tex));
}

static int	handle_east_texture(char *value, t_config *config)
{
	if (config->east_tex)
	{
		printf("Error: Duplicate EA identifier\n");
		return (0);
	}
	return (parse_texture(value, &config->east_tex));
}

int	parse_texture_identifier(char *id, char *value, t_config *config)
{
	if (ft_strncmp(id, "NO", 3) == 0)
		return (handle_north_texture(value, config));
	else if (ft_strncmp(id, "SO", 3) == 0)
		return (handle_south_texture(value, config));
	else if (ft_strncmp(id, "WE", 3) == 0)
		return (handle_west_texture(value, config));
	else if (ft_strncmp(id, "EA", 3) == 0)
		return (handle_east_texture(value, config));
	return (-1);
}

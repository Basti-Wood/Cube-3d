#include "../../includes/cub3d.h"

static int	handle_config_line(char *line, t_config *config)
{
	char	*trimmed;

	trimmed = trim_whitespace(line);
	if (is_empty_line(trimmed))
		return (1);
	if (is_map_line(trimmed))
		return (-1);
	if (!parse_identifier(trimmed, config))
	{
		printf("Error: Failed to parse configuration line\n");
		return (0);
	}
	return (1);
}

static int	process_config_line(char *line, t_config *config, int *found_map,
	char **first_map_line)
{
	int	result;

	result = handle_config_line(line, config);
	if (result == -1)
	{
		*found_map = 1;
		*first_map_line = line;
		return (-1);
	}
	if (result == 0)
	{
		free(line);
		return (-2);
	}
	free(line);
	return (1);
}

int	parse_config_section(int fd, t_config *config, char **first_map_line)
{
	char	*line;
	int		result;
	int		found_map;

	found_map = 0;
	*first_map_line = NULL;
	line = get_next_line(fd);
	while (line != NULL)
	{
		result = process_config_line(line, config, &found_map, first_map_line);
		if (result == -1 || result == -2)
			break ;
		line = get_next_line(fd);
	}
	if (found_map)
		return (1);
	if (result == -2)
		return (-2);
	return (-1);
}

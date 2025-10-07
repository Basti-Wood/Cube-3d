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

long	parse_config_section(FILE *file, t_config *config)
{
	char	*line;
	int		result;
	long	map_pos;

	map_pos = -1;
	line = read_line(file);
	while (line != NULL)
	{
		result = handle_config_line(line, config);
		if (result == -1)
		{
			map_pos = ftell(file) - strlen(line);
			free(line);
			break ;
		}
		if (result == 0)
		{
			free(line);
			return (-2);
		}
		free(line);
		line = read_line(file);
	}
	return (map_pos);
}

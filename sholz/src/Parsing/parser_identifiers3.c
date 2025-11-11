#include "../../includes/cub3d.h"

static char	*get_identifier(char *line)
{
	char	*id;

	id = strtok(line, " \t");
	return (id);
}

static char	*get_value(void)
{
	char	*value;

	value = strtok(NULL, "\n");
	if (!value)
		return (NULL);
	value = trim_whitespace(value);
	return (value);
}

static int	process_identifier_value(char *id, char *value, t_config *config)
{
	int	result;

	result = parse_texture_identifier(id, value, config);
	if (result == -1)
		result = parse_color_identifier(id, value, config);
	if (result == -1)
	{
		printf("Error: Unknown identifier: %s\n", id);
		return (0);
	}
	return (result);
}

int	parse_identifier(char *line, t_config *config)
{
	char	*line_copy;
	char	*id;
	char	*value;
	int		result;

	line_copy = ft_strdup_custom(line);
	if (!line_copy)
		return (0);
	id = get_identifier(line_copy);
	if (!id)
	{
		free(line_copy);
		return (0);
	}
	value = get_value();
	if (!value)
	{
		free(line_copy);
		printf("Error: Missing value for identifier: %s\n", id);
		return (0);
	}
	result = process_identifier_value(id, value, config);
	free(line_copy);
	return (result);
}

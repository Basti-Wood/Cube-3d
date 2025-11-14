#include "../../includes/cub3d.h"

int	parse_identifier(char *line, t_config *config)
{
	char	*line_copy;
	char	*id;
	char	*value;
	char	*rest;
	int		result;

	line_copy = ft_strdup_custom(line);
	if (!line_copy)
		return (0);
	id = get_identifier(line_copy, &rest);
	if (!id)
	{
		free(line_copy);
		return (0);
	}
	value = get_value(rest);
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

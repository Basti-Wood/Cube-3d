#include "../../includes/cub3d.h"

int	process_identifier_value(char *id, char *value, t_game *game);

int	parse_identifier(char *line, t_game *game)
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
	result = process_identifier_value(id, value, game);
	free(line_copy);
	return (result);
}

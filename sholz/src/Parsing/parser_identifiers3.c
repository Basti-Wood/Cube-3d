#include "../../includes/cub3d.h"

char	*skip_spaces(char *str)
{
	while (*str && (*str == ' ' || *str == '\t'))
		str++;
	return (str);
}

char	*find_end_of_word(char *str)
{
	while (*str && *str != ' ' && *str != '\t' && *str != '\n')
		str++;
	return (str);
}

char	*get_identifier(char *line, char **rest)
{
	char	*start;
	char	*end;

	start = skip_spaces(line);
	if (!*start)
		return (NULL);
	end = find_end_of_word(start);
	if (end > start)
		*end = '\0';
	*rest = end + 1;
	return (start);
}

char	*get_value(char *rest)
{
	char	*start;
	char	*end;

	start = skip_spaces(rest);
	if (!*start)
		return (NULL);
	end = start;
	while (*end && *end != '\n')
		end++;
	*end = '\0';
	return (trim_whitespace(start));
}

int	process_identifier_value(char *id, char *value, t_game *game)
{
	int	result;

	result = parse_texture_identifier(id, value, game);
	if (result == -1)
		result = parse_color_identifier(id, value, game);
	if (result == -1)
	{
		printf("Error: Unknown identifier: %s\n", id);
		return (0);
	}
	return (result);
}

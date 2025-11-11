#include "../../includes/cub3d.h"

int	is_map_char(char c)
{
	if (c == '0' || c == '1' || c == 'N' || c == 'S')
		return (1);
	if (c == 'E' || c == 'W' || c == ' ' || c == '\t')
		return (1);
	return (0);
}

static int	check_line_chars(const char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\n' || line[i] == '\r')
			break ;
		if (!is_map_char(line[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	has_map_content(const char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\n' || line[i] == '\r')
			break ;
		if (line[i] != ' ' && line[i] != '\t')
			return (1);
		i++;
	}
	return (0);
}

int	is_map_line(const char *line)
{
	if (!line || !*line)
		return (0);
	if (!check_line_chars(line))
		return (0);
	if (!has_map_content(line))
		return (0);
	return (1);
}

char	*read_line(FILE *file)
{
	char	buffer[4096];
	char	*line;

	if (!fgets(buffer, sizeof(buffer), file))
		return (NULL);
	line = ft_strdup_custom(buffer);
	return (line);
}

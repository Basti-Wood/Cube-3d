#include "../../includes/cub3d.h"

static void	remove_newline(char *line, int len)
{
	while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r'))
	{
		line[len - 1] = '\0';
		len--;
	}
}

char	*clean_map_line(char *line)
{
	int		len;
	char	*cleaned;

	if (!line)
		return (NULL);
	len = ft_strlen(line);
	remove_newline(line, len);
	cleaned = ft_strdup_custom(line);
	return (cleaned);
}

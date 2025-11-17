#include "../../includes/cub3d.h"

void	copy_line_to_grid(char *cleaned, int *grid_row)
{
	int	j;

	j = 0;
	while (cleaned[j])
	{
		grid_row[j] = (int)cleaned[j];
		j++;
	}
}

int	process_map_line(char *line, char **temp, int *height, int *max_width)
{
	char	*cleaned;
	int		len;

	cleaned = clean_map_line(line);
	if (!cleaned)
		return (0);
	len = ft_strlen(cleaned);
	if (len > *max_width)
		*max_width = len;
	temp[(*height)++] = cleaned;
	return (1);
}

char	**read_temp_lines(int fd, char *first_line, int *height,
	int *max_width)
{
	char	**temp;
	char	*line;

	temp = malloc(sizeof(char *) * 1001);
	if (!temp)
		return (NULL);
	*height = 0;
	*max_width = 0;
	line = first_line;
	while (line && *height < 1000)
	{
		if (is_map_line(line))
		{
			if (!process_map_line(line, temp, height, max_width))
				return (free(line), NULL);
		}
		free(line);
		line = get_next_line(fd);
	}
	temp[*height] = NULL;
	return (temp);
}

void	free_temp_lines(char **temp, int count)
{
	int	i;

	i = 0;
	while (i < count)
		free(temp[i++]);
	free(temp);
}

#include "../../includes/cub3d.h"

static void	init_map_array(int **map, int height, int width)
{
	int	i;
	int	j;

	i = 0;
	while (i < height)
	{
		map[i] = malloc(sizeof(int) * (width + 1));
		if (!map[i])
		{
			while (--i >= 0)
				free(map[i]);
			return ;
		}
		j = 0;
		while (j < width)
		{
			map[i][j] = (int)' ';
			j++;
		}
		map[i][width] = (int) '\0';
		i++;
	}
	map[i] = NULL;
}

int	**allocate_map(int height, int width)
{
	int	**map;

	if (height <= 0 || width <= 0)
		return (NULL);
	map = malloc(sizeof(int *) * (height + 1));
	if (!map)
		return (NULL);
	init_map_array(map, height, width);
	if (!map[0])
	{
		free(map);
		return (NULL);
	}
	return (map);
}

int	count_map_lines(int fd)
{
	char	*line;
	int		count;

	count = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (is_map_line(line))
			count++;
		free(line);
		line = get_next_line(fd);
	}
	return (count);
}

static void	process_dimension_line(char *line, int *height, int *max_width)
{
	char	*cleaned;
	int		line_len;

	if (is_map_line(line))
	{
		cleaned = clean_map_line(line);
		if (cleaned)
		{
			line_len = ft_strlen(cleaned);
			if (line_len > *max_width)
				*max_width = line_len;
			free(cleaned);
		}
		(*height)++;
	}
}

void	count_map_dimensions(int fd, t_map *map)
{
	char	*line;
	int		height;
	int		max_width;

	height = 0;
	max_width = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		process_dimension_line(line, &height, &max_width);
		free(line);
		line = get_next_line(fd);
	}
	map->height = height;
	map->width = max_width;
}

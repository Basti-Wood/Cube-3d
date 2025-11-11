#include "../../includes/cub3d.h"

static void	init_map_array(char **map, int height)
{
	int	i;

	i = 0;
	while (i <= height)
	{
		map[i] = NULL;
		i++;
	}
}

char	**allocate_map(int height)
{
	char	**map;

	if (height <= 0)
		return (NULL);
	map = malloc(sizeof(char *) * (height + 1));
	if (!map)
		return (NULL);
	init_map_array(map, height);
	return (map);
}

static int	count_line(FILE *file)
{
	char	*line;
	int		count;

	count = 0;
	line = read_line(file);
	while (line != NULL)
	{
		if (is_map_line(line))
			count++;
		free(line);
		line = read_line(file);
	}
	return (count);
}

int	count_map_lines(FILE *file, long start_pos)
{
	int	count;

	fseek(file, start_pos, SEEK_SET);
	count = count_line(file);
	return (count);
}

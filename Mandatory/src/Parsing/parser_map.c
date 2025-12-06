/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstorck <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 00:14:56 by bstorck           #+#    #+#             */
/*   Updated: 2025/12/04 00:14:57 by bstorck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	update_max_width(int *max_width, int current_len)
{
	if (current_len > *max_width)
		*max_width = current_len;
}

static int	process_map_line(t_map *map, char *line, int *i, int *max_width)
{
	char	*cleaned;
	int		current_len;
	int		j;

	cleaned = clean_map_line(line);
	free(line);
	if (!cleaned)
		return (0);
	current_len = ft_strlen(cleaned);
	j = 0;
	while (cleaned[j])
	{
		map->grid[(*i) * map->width + j] = (int)cleaned[j];
		j++;
	}
	free(cleaned);
	update_max_width(max_width, current_len);
	(*i)++;
	return (1);
}

static int	read_map_lines(int fd, t_map *map, int *max_width)
{
	char	*line;
	int		i;

	i = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (!is_map_line(line))
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (!process_map_line(map, line, &i, max_width))
			return (0);
		line = get_next_line(fd);
	}
	return (i);
}

static int	validate_map(t_map *map)
{
	if (map->height == 0)
	{
		printf("Error: No map found\n");
		return (0);
	}
	find_player(map);
	if (map->player.x == -1 || map->player.y == -1)
	{
		printf("Error: No player position found in map\n");
		return (0);
	}
	return (1);
}

int	parse_map_section(int fd, t_map *map)
{
	int	max_width;
	int	height;

	max_width = 0;
	height = read_map_lines(fd, map, &max_width);
	if (height == 0)
		return (0);
	map->height = height;
	map->width = max_width;
	if (!validate_map(map))
		return (0);
	return (1);
}

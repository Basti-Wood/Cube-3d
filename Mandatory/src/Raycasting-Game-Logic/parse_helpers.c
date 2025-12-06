/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstorck <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 00:31:05 by bstorck           #+#    #+#             */
/*   Updated: 2025/12/04 00:31:06 by bstorck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/game.h"

int	init_xpm_pixel_map(t_texture *texture)
{
	texture->pixel_map = malloc(texture->width * texture->height * sizeof(int));
	if (!texture->pixel_map)
		return (1);
	return (0);
}

char	*skip_lines(int xpm_fd)
{
	char	*line;

	line = get_next_line(xpm_fd);
	while (line != NULL)
	{
		if (line[0] == '/' || line[0] == '#')
			free(line);
		else if (ft_strncmp(line, "static", 6) == 0)
			free(line);
		else
			break ;
		line = get_next_line(xpm_fd);
	}
	return (line);
}

int	parse_color_table_line(char *line, t_texture *texture)
{
	int	color;
	int	i;
	int	index;

	if (!line[1])
		return (1);
	index = (int)(line[1]) - 32;
	i = 2;
	while (line[i] && line[i] != '#')
		i++;
	if (!line[i])
		return (1);
	color = parse_hex_color(&line[i]);
	free(line);
	line = NULL;
	if (color == -1)
		return (1);
	texture->color_table[index] = color;
	return (0);
}

int	parse_pixel_map_line(char *line, int y, t_texture *tx)
{
	int	x;
	int	index;

	x = -1;
	while (++x < tx->width)
	{
		if (!line[x])
			return (1);
		index = (int)(line[x + 1]) - 32;
		if (index < 0 || index >= 94)
			return (1);
		tx->pixel_map[y * tx->width + x] = tx->color_table[index];
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstorck <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 00:14:56 by bstorck           #+#    #+#             */
/*   Updated: 2025/12/04 00:14:57 by bstorck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_map_char(char c)
{
	if (c == '0' || c == '1' || c == 'N' || c == 'S')
		return (1);
	if (c == 'E' || c == 'W' || c == ' ' || c == '\t')
		return (1);
	if (c == '2')
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

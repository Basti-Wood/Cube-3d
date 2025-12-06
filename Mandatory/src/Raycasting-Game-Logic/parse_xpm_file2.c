/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_xpm_file2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstorck <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 00:31:19 by bstorck           #+#    #+#             */
/*   Updated: 2025/12/04 00:31:20 by bstorck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/game.h"

static char	**parse_header_line(char *line)
{
	int		i;
	char	*header;
	char	**token;

	i = 0;
	while (line[i] && !ft_isdigit(line[i]))
		i++;
	header = ft_strdup(&line[i]);
	free(line);
	if (!header)
		return (NULL);
	token = ft_split(header, ' ');
	free(header);
	return (token);
}

int	parse_xpm_header(int xpm_fd, t_texture *texture)
{
	char	*line;
	char	**token;

	line = skip_lines(xpm_fd);
	if (!line)
		return (1);
	token = parse_header_line(line);
	if (!token || !token[0] || !token[1] || !token[2])
	{
		free_tokens((void **)token);
		return (1);
	}
	texture->width = ft_atoi(token[0]);
	texture->height = ft_atoi(token[1]);
	texture->color_count = ft_atoi(token[2]);
	free_tokens((void **)token);
	return (0);
}

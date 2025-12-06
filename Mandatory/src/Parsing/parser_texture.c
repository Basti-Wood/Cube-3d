/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstorck <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 00:14:56 by bstorck           #+#    #+#             */
/*   Updated: 2025/12/04 00:14:57 by bstorck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	check_texture_exists(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		printf("Error: Cannot open texture file: %s\n", path);
		return (0);
	}
	close(fd);
	return (1);
}

int	parse_texture(char *line, char **texture_path)
{
	char	*path;

	path = trim_whitespace(line);
	if (!path || !*path)
	{
		printf("Error: Empty texture path\n");
		return (0);
	}
	if (!check_texture_exists(path))
		return (0);
	*texture_path = ft_strdup_custom(path);
	if (!*texture_path)
	{
		printf("Error: Memory allocation failed\n");
		return (0);
	}
	return (1);
}

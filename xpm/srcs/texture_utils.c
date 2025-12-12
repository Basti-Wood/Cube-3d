/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstorck <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 04:51:53 by bstorck           #+#    #+#             */
/*   Updated: 2025/11/28 04:51:54 by bstorck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/game.h"

int	init_xpm_pixel_map(t_texture *texture)
{
	int		i;

	texture->image_data = (int**)malloc(sizeof(int*) * texture->height);
	if (!texture->image_data)
		return (1);
	i = -1;
	while (++i < texture->height)
	{
		texture->image_data[i] = (int*)malloc(sizeof(int) * texture->width);
		if (!texture->image_data[i])
			return (1);
	}
	return (0);
}

char	*skip_lines(int xpm_fd)
{
	char	*line;

	while ((line = get_next_line(xpm_fd)) != NULL)
	{
		if (line[0] == '/' || line[0] == '#')
			free(line);
		else if (ft_strncmp(line, "static const char", 17) == 0)
			free(line);
		else
			break ;
	}
	return (line);
}

int	ft_isxdigit(int c)
{
	return (('0' <= c && c <= '9')
		|| ('A' <= c && c <= 'Z')
		|| ('a' <= c && c <= 'z'));
}

int	hex_char_to_int(char c)
{
	if ('0' <= c && c <= '9')
		return (c - '0');
	if ('a' <= c && c <= 'z')
		return (c - 'a' + 10);
	if ('A' <= c && c <= 'Z')
		return (c - 'A' + 10);
	return (-1);
}

int	hex_pair_to_int(char c1, char c2)
{
	int	high;
	int	low;

	high = hex_char_to_int(c1);
	low = hex_char_to_int(c2);
	if (high == -1 || low == -1)
		return (-1);
	return (high << 4 | low);
}

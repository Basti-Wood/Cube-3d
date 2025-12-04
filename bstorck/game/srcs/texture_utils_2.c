/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstorck <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 09:02:21 by bstorck           #+#    #+#             */
/*   Updated: 2025/11/25 09:02:26 by bstorck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/game.h"

char	*skip_lines(int xpm_fd)
{
	char	*line;

	line = get_next_line(xpm_fd);
	while (line != NULL)
	{
		if (line[0] == '/' || line[0] == '#')
			free(line);
		else if (ft_strncmp(line, "static const char", 17) == 0)
			free(line);
		else
			break ;
		line = get_next_line(xpm_fd);
	}
	return (line);
}

int	ft_isxdigit(int c)
{
	return (('0' <= c && c <= '9') || ('A' <= c && c <= 'Z') || ('a' <= c
			&& c <= 'z'));
}

int	parse_xpm_pixel_map(int xpm_fd, t_texture *tex)
{
	int		x;
	int		y;
	char	*line;

	if (init_xpm_pixel_map(tex))
		return (1);
	line = skip_lines(xpm_fd);
	y = -1;
	while (++y < tex->height)
	{
		if (line == NULL)
			break ;
		x = -1;
		while (++x < tex->width)
			tex->pixel_map[y][x] = tex->color_table[(int)line[x + 1] - 32];
		free(line);
		line = get_next_line(xpm_fd);
	}
	free(line);
	if (y < tex->height)
		return (1);
	return (0);
}

void	parse_xpm_file(const char *filename, t_game *game)
{
	int	xpm_fd;

	xpm_fd = get_fd(filename);
	if (xpm_fd == -1)
	{
		printf("Error\nFailed to open XPM file\n");
		close_game(game);
	}
	if (parse_xpm_header(xpm_fd, &game->texture))
	{
		printf("Error\nFailed to parse XPM file header\n");
		close_game(game);
	}
	if (parse_xpm_color_table(xpm_fd, &game->texture))
	{
		printf("Error\nFailed to parse XPM color table\n");
		close_game(game);
	}
	if (parse_xpm_pixel_map(xpm_fd, &game->texture))
	{
		printf("Error\nFailed to parse XPM pixel map\n");
		close_game(game);
	}
}

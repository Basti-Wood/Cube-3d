/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_xpm_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstorck <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 00:31:19 by bstorck           #+#    #+#             */
/*   Updated: 2025/12/04 00:31:20 by bstorck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/game.h"

// static char	**parse_header_line(char *line)
// {
// 	int		i;
// 	char	*header;
// 	char	**token;
//
// 	i = 0;
// 	while (line[i] && !ft_isdigit(line[i]))
// 		i++;
// 	header = ft_strdup(&line[i]);
// 	free(line);
// 	if (!header)
// 		return (NULL);
// 	token = ft_split(header, ' ');
// 	free(header);
// 	return (token);
// }

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

// int	parse_xpm_header(int xpm_fd, t_texture *texture)
// {
// 	int		i;
// 	char	*line;
// 	char	*header;
// 	char	**token;
//
// 	line = skip_lines(xpm_fd);
// 	i = 0;
// 	while (!ft_isdigit(line[i]))
// 		i++;
// 	header = ft_strdup(&line[i]);
// 	free(line);
// 	if (!header)
// 		return (1);
// 	token = ft_split(header, ' ');
// 	free(header);
// 	if (!token || !token[0] || !token[1] || !token[2])
// 	{
// 		free_tokens((void **)token);
// 		return (1);
// 	}
// 	texture->width = ft_atoi(token[0]);
// 	texture->height = ft_atoi(token[1]);
// 	texture->color_count = ft_atoi(token[2]);
// 	free_tokens((void **)token);
// 	return (0);
// }

int	parse_xpm_color_table(int xpm_fd, t_texture *texture)
{
	char	*line;
	int		line_count;

	line_count = 0;
	while (line_count < texture->color_count)
	{
		line = skip_lines(xpm_fd);
		if (line == NULL)
			return (1);
		if (parse_color_table_line(line, texture))
		{
			free(line);
			line = NULL;
			return (1);
		}
		line_count++;
	}
	return (0);
}

int	parse_xpm_pixel_map(int xpm_fd, t_texture *tx)
{
	int		y;
	char	*line;

	line = skip_lines(xpm_fd);
	if (init_xpm_pixel_map(tx))
		return (1);
	if (!line)
		return (1);
	y = -1;
	while (++y < tx->height)
	{
		if (!line || parse_pixel_map_line(line, y, tx))
		{
			free_texture(tx);
			free(line);
			return (1);
		}
		free(line);
		line = get_next_line(xpm_fd);
	}
	free(line);
	if (y < tx->height)
		return (1);
	return (0);
}

static void	handle_xpm_error(int xpm_fd, const char *message, t_game *game)
{
	printf("Error\n%s\n", message);
	if (xpm_fd != -1)
		close(xpm_fd);
	free_game_resources(game);
	exit(1);
}

t_texture	parse_xpm_file(const char *filename, t_game *game)
{
	t_texture	texture;
	int			xpm_fd;

	xpm_fd = get_fd(filename);
	if (xpm_fd == -1)
		handle_xpm_error(-1, "Failed to open XPM file", game);
	if (parse_xpm_header(xpm_fd, &texture))
		handle_xpm_error(xpm_fd, "Failed to parse XPM file header", game);
	if (parse_xpm_color_table(xpm_fd, &texture))
		handle_xpm_error(xpm_fd, "Failed to parse XPM color table", game);
	if (parse_xpm_pixel_map(xpm_fd, &texture))
		handle_xpm_error(xpm_fd, "Failed to parse XPM pixel map", game);
	close(xpm_fd);
	return (texture);
}

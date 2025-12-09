/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map_setup_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstorck <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 00:14:56 by bstorck           #+#    #+#             */
/*   Updated: 2025/12/04 00:14:57 by bstorck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	copy_line_to_grid(char *cleaned, int *grid_row)
{
	int	j;

	j = 0;
	while (cleaned[j])
	{
		if (cleaned[j] == '0')
			grid_row[j] = 0;
		else if (cleaned[j] == '1')
			grid_row[j] = 1;
		else if (cleaned[j] == '2')
			grid_row[j] = 2;
		else
			grid_row[j] = (int)cleaned[j];
		j++;
	}
}

int	process_map_line(char *line, char **temp, int *height, int *max_width)
{
	char	*cleaned;
	int		len;

	cleaned = clean_map_line(line);
	if (!cleaned)
		return (0);
	len = ft_strlen(cleaned);
	if (len > *max_width)
		*max_width = len;
	temp[(*height)++] = cleaned;
	return (1);
}

static int	process_line(char *line, char **temp, int *height, int *max_width)
{
	if (is_empty_line(line))
	{
		if (*height > 0)
		{
			free(line);
			return (0);
		}
	}
	else if (is_map_line(line))
	{
		if (!process_map_line(line, temp, height, max_width))
		{
			free(line);
			return (-1);
		}
	}
	else if (*height > 0)
	{
		free(line);
		free_temp_lines(temp, *height);
		return (-1);
	}
	return (1);
}

char	**read_temp_lines(int fd, char *first_line, int *height,
	int *max_width)
{
	char	**temp;
	char	*line;
	int		result;

	temp = malloc(sizeof(char *) * 1001);
	if (!temp)
		return (NULL);
	*height = 0;
	*max_width = 0;
	line = first_line;
	while (line && *height < 1000)
	{
		result = process_line(line, temp, height, max_width);
		if (result == 0)
			break ;
		if (result == -1)
			return (NULL);
		free(line);
		line = get_next_line(fd);
	}
	temp[*height] = NULL;
	return (temp);
}

void	free_temp_lines(char **temp, int count)
{
	int	i;

	i = 0;
	while (i < count)
		free(temp[i++]);
	free(temp);
}

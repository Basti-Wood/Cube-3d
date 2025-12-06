/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sholz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 13:25:41 by sholz             #+#    #+#             */
/*   Updated: 2025/01/11 13:25:46 by sholz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
 * Function to save the remaining string after extracting a line.
 */
static char	*save_rest(char *str, int start)
{
	char	*ret;
	int		len;

	len = ft_strlen(str) - start;
	if (len <= 0)
	{
		free(str);
		return (NULL);
	}
	ret = ft_substr(str, start, len);
	free(str);
	return (ret);
}

/*
 * Function to extract the next line from the given string up to the newline.
 */
static char	*pull_next_line(char *str, int *next)
{
	char	*line;
	int		i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		*next = i + 1;
	else
		*next = i;
	line = ft_substr(str, 0, *next);
	return (line);
}

/*
 * Function to read from the file descriptor until a newline or EOF.
 */
static char	*new_line(int fd, char *buffer, char **str)
{
	int		red;
	char	*new_str;

	while (!ft_strchr(*str, '\n'))
	{
		red = read(fd, buffer, BUFFER_SIZE);
		if (red < 0 || (red == 0 && (*str)[0] == '\0'))
		{
			free(*str);
			*str = NULL;
			return (NULL);
		}
		if (red == 0)
			return (*str);
		buffer[red] = '\0';
		new_str = ft_strjoin(*str, buffer);
		free(*str);
		*str = new_str;
	}
	return (*str);
}
/*
 * Function to initialize the buffer and check validity.
 */

static int	ini_buffer(char **buffer, char **next_line)
{
	*buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!*buffer)
	{
		if (*next_line)
		{
			free(*next_line);
			*next_line = NULL;
		}
		return (0);
	}
	if (!*next_line)
		*next_line = ft_strdup("\0");
	return (*next_line != NULL);
}

/*
 * Main function to get the next line from the file.
 */
char	*get_next_line(int fd)
{
	static char	*next_line;
	char		*buffer;
	char		*line;
	int			start_next;

	if (!ini_buffer(&buffer, &next_line))
		return (NULL);
	next_line = new_line(fd, buffer, &next_line);
	free(buffer);
	if (!next_line)
		return (NULL);
	line = pull_next_line(next_line, &start_next);
	next_line = save_rest(next_line, start_next);
	return (line);
}

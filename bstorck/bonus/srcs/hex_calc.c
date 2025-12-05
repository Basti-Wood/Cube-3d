/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_calc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstorck <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 00:15:25 by bstorck           #+#    #+#             */
/*   Updated: 2025/12/04 00:15:26 by bstorck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/game.h"

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

int	parse_hex_color(const char *line)
{
	int	i;
	int	r;
	int	g;
	int	b;

	if (line[0] != '#')
		return (-1);
	i = 0;
	while (++i < 7)
		if (!ft_isxdigit(line[i]))
			return (-1);
	r = hex_pair_to_int(line[1], line[2]);
	g = hex_pair_to_int(line[3], line[4]);
	b = hex_pair_to_int(line[5], line[6]);
	if (r == -1 || g == -1 || b == -1)
		return (-1);
	return ((r << 16) | (g << 8) | b);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstorck <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 10:28:48 by bstorck           #+#    #+#             */
/*   Updated: 2025/03/26 13:01:09 by bstorck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"

static size_t	ft_ante_mantissa(char const *str, int *sig, double *ret)
{
	size_t	i;

	i = -1;
	while (++i, str[i] == ' ' || str[i] == '\f' || str[i] == '\n'
		|| str[i] == '\r' || str[i] == '\t' || str[i] == '\v' || str[i] == '+');
	*sig = 1;
	if (str[i] == '-')
	{
		*sig *= -1;
		i++;
	}
	i--;
	*ret = 0;
	while (++i, '0' <= str[i] && str[i] <= '9')
		*ret = *ret * 10 + (str[i] - '0');
	return (i);
}

double	ft_atod(char const *str)
{
	size_t	i;
	int		sig;
	double	fra;
	double	ret;

	i = 0;
	sig = 0;
	fra = 0;
	ret = 0;
	i = ft_ante_mantissa(str, &sig, &ret);
	fra = 1;
	if (str[i] == '.')
	{
		fra /= 10;
		i++;
	}
	i--;
	while (++i, '0' <= str[i] && str[i] <= '9')
	{
		ret = ret + fra * (str[i] - '0');
		fra /= 10;
	}
	return (ret * sig);
}

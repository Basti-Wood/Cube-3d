/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sholz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 14:21:02 by sholz             #+#    #+#             */
/*   Updated: 2024/11/30 14:21:04 by sholz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*s3;

	i = 0;
	j = 0;
	s3 = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!s1 || !s2 || !s3)
	{
		return (NULL);
	}
	while (s1[i])
	{
		s3[i] = s1[i];
		i += 1;
	}
	while (s2[j])
	{
		s3[i] = s2[j];
		i += 1;
		j += 1;
	}
	s3[i] = '\0';
	return (s3);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	c = (unsigned char) c;
	while (s[i] != c)
	{
		if (s[i] == '\0')
		{
			return (NULL);
		}
		i++;
	}
	return ((char *)&s[i]);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	size_t	i;

	if (!s)
		return (NULL);
	if (ft_strlen(s) <= start || len == 0)
	{
		ret = (char *)malloc(1);
		ret[0] = '\0';
		return (ret);
	}
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (i < len)
	{
		ret[i] = s[i + start];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

char	*ft_strdup(const char *str)
{
	char	*dup;
	size_t	i;
	size_t	len;

	if (!str)
		return (NULL);
	len = 0;
	while (str[len])
	{
		len += 1;
	}
	i = 0;
	dup = (char *)malloc(sizeof(char) * (len + 1));
	if (!dup)
	{
		return (NULL);
	}
	while (str[i])
	{
		dup[i] = str[i];
		i += 1;
	}
	dup[i] = '\0';
	return (dup);
}

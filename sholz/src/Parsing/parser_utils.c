#include "../../includes/cub3d.h"

char	*ft_strdup_custom(const char *s)
{
	char	*dup;
	size_t	len;
	size_t	i;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	dup = malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*trim_leading(char *str)
{
	while (*str == ' ' || *str == '\t')
		str++;
	return (str);
}

char	*trim_trailing(char *str)
{
	char	*end;

	end = str + ft_strlen(str) - 1;
	while (end > str && (*end == ' ' || *end == '\t'
			|| *end == '\n' || *end == '\r'))
		end--;
	*(end + 1) = '\0';
	return (str);
}

char	*trim_whitespace(char *str)
{
	if (!str)
		return (NULL);
	str = trim_leading(str);
	if (*str == 0)
		return (str);
	str = trim_trailing(str);
	return (str);
}

int	is_empty_line(const char *line)
{
	if (!line)
		return (1);
	while (*line)
	{
		if (*line != ' ' && *line != '\t'
			&& *line != '\n' && *line != '\r')
			return (0);
		line++;
	}
	return (1);
}

#include "../../includes/cub3d.h"

static int	validate_color_value(int value)
{
	if (value < 0 || value > 255)
	{
		printf("Error: Color value out of range [0-255]: %d\n", value);
		return (0);
	}
	return (1);
}

static int	parse_color_token(char *token, int *value)
{
	char	*trimmed;

	if (!token)
	{
		printf("Error: Invalid color format (expected R,G,B)\n");
		return (0);
	}
	trimmed = trim_whitespace(token);
	*value = ft_atoi(trimmed);
	if (!validate_color_value(*value))
		return (0);
	return (1);
}

static char	*find_next_token(char *str, char **next)
{
	char	*start;
	char	*end;

	start = str;
	end = start;
	while (*end && *end != ',')
		end++;
	if (*end == ',')
	{
		*end = '\0';
		*next = end + 1;
	}
	else
		*next = end;
	return (start);
}

int	parse_color(char *line, int *r, int *g, int *b)
{
	char	*token;
	char	*rest;
	int		values[3];
	int		i;

	rest = line;
	i = 0;
	while (i < 3)
	{
		token = find_next_token(rest, &rest);
		if (!parse_color_token(token, &values[i]))
			return (0);
		i++;
	}
	*r = values[0];
	*g = values[1];
	*b = values[2];
	return (1);
}

int	rgb_to_int(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

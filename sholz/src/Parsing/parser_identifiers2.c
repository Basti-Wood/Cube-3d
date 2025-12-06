#include "../../includes/cub3d.h"

static int	handle_floor_color(char *value, t_game *game)
{
	int	r;
	int	g;
	int	b;

	if (game->floor_color != -1)
	{
		printf("Error: Duplicate F identifier\n");
		return (0);
	}
	if (!parse_color(value, &r, &g, &b))
		return (0);
	game->floor_color = rgb_to_int(r, g, b);
	return (1);
}

static int	handle_ceiling_color(char *value, t_game *game)
{
	int	r;
	int	g;
	int	b;

	if (game->ceiling_color != -1)
	{
		printf("Error: Duplicate C identifier\n");
		return (0);
	}
	if (!parse_color(value, &r, &g, &b))
		return (0);
	game->ceiling_color = rgb_to_int(r, g, b);
	return (1);
}

int	parse_color_identifier(char *id, char *value, t_game *game)
{
	if (ft_strncmp(id, "F", 2) == 0)
		return (handle_floor_color(value, game));
	else if (ft_strncmp(id, "C", 2) == 0)
		return (handle_ceiling_color(value, game));
	return (-1);
}

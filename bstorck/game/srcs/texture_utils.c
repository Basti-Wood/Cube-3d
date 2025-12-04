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

int	get_texture_y(int tex_pos, t_game *game)
{
	int	tex_y;

	tex_y = (int)tex_pos & (game->texture.height - 1);
	// tex_y *= game->texture.height;
	return (tex_y);
}

int	get_texture_x(t_game *g)
{
	int		tex_x;
	double	wall_x;

	if (g->hero.ray.side == 0)
		wall_x = g->hero.pos.y + g->hero.ray.perp_dist_wall * g->hero.ray.dir.y;
	else
		wall_x = g->hero.pos.x + g->hero.ray.perp_dist_wall * g->hero.ray.dir.x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)g->texture.width);
	if (g->hero.ray.side && g->hero.ray.dir.y < 0)
		tex_x = g->texture.width - tex_x - 1;
	if (!g->hero.ray.side && g->hero.ray.dir.x > 0)
		tex_x = g->texture.width - tex_x - 1;
	return (tex_x);
}

void	draw_line_loop(int screen_x, t_line line, int line_height, t_game *game)
{
	int			color;
	t_square	tex;
	double		tex_pos;
	double		step;

	tex.x = get_texture_x(game);
	step = (double)game->texture.height / line_height;
	tex_pos = line.start - 1.0 * game->w_height / 2 + 1.0 * line_height / 2;
	tex_pos *= step;
	while (line.start <= line.end)
	{
		tex.y = get_texture_y(tex_pos, game);
		tex_pos += step;
		color = game->texture.pixel_map[tex.y][tex.x];
		if (game->hero.ray.side)
			color = (color >> 1) & 8355711;
		put_pixel(screen_x, line.start, color, game);
		line.start++;
	}
}

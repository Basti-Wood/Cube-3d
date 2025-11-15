#include "../includes/game.h"

void	put_pixel(int x, int y, int color, t_game *game)
{
	if(x >= SCRN_WIDTH || y >= SCRN_HEIGHT || x < 0 || y < 0)
		return;

	int	index = y * game->size_line + x * game->bpp / 8;
	game->data[index] = color & 0xFF;
	game->data[index + 1] = (color >> 8) & 0xFF;
	game->data[index + 2] = (color >> 16) & 0xFF;
}

void	clear_image(t_game *game)
{
	for(int y = 0; y < SCRN_HEIGHT; y++)
		for(int x = 0; x < SCRN_WIDTH; x++)
			put_pixel(x, y, 0, game);
}

double	distance(double x, double y)
{
	return sqrt(x * x + y * y);
}

double	fixed_dist(double x1, double y1, double x2, double y2, t_game *game)
{
	double	delta_x = x2 - x1;
	double	delta_y = y2 - y1;
	double	angle = atan2(delta_y, delta_x) - game->player.angle;
	double	fix_dist = distance(delta_x, delta_y) * cos(angle);
	return fix_dist;
}


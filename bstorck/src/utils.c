#include "../includes/game.h"

void	clear_image(t_game *game)
{
	for(int y = 0; y < SCRN_HEIGHT; y++)
		for(int x = 0; x < SCRN_WIDTH; x++)
			put_pixel(x, y, 0, game);
}

void	put_pixel(int x, int y, int color, t_game *game)
{
	if(x >= SCRN_WIDTH || y >= SCRN_HEIGHT || x < 0 || y < 0)
		return;

	int	index = y * game->size_line + x * game->bpp / 8;
	game->data[index] = color & 0xFF;
	game->data[index + 1] = (color >> 8) & 0xFF;
	game->data[index + 2] = (color >> 16) & 0xFF;
}

bool	collision(int x, int y, int **map)
{
	// int	x = rx / BLOCK_SIZE;
	// printf("\tX = %i", x);
	// int	y = ry / BLOCK_SIZE;
	// printf("\tY = %i\n", y);
	if(map[y][x] > 0)
		return (true);
	return (false);
}

// double	distance(double x, double y)
// {
	// return (sqrt(x * x + y * y));
// }

// double	fixed_dist(double x1, double y1, double x2, double y2, t_game *game)
// {
// 	double	dir_angle = atan2(game->player.dir.y, game->player.dir.x);
// 	double	delta_x = x2 - x1;
// 	double	delta_y = y2 - y1;
// 	double	angle = atan2(delta_y, delta_x) - dir_angle;
// 	double	fix_dist = distance(delta_x, delta_y) * cos(angle);
// 	return (fix_dist);
// }

// if(player->mini == false)
// {
// 	double	dist = fixed_dist(player->pos.x, player->pos.y, ray_x, ray_y, game);
// 	double	height = (BLOCK_SIZE / dist) * (((double)FRM_WIDTH) / 2);
// 	int	start_y = (SCRN_HEIGHT - height) / 2;
// 	int	end = start_y + height;
// 	while(start_y < end)
// 	{
// 		put_pixel(i, start_y, 255, game);
// 		start_y++;
// 	}
// }

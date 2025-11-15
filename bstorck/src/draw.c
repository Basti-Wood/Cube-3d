#include "../includes/game.h"

void	draw_empty_square(int x, int y, int size, int color, t_game *game)
{
	int	i;

	i = -1;
	while (++i < size)
		put_pixel(x + i, y, color, game);
	i = -1;
	while (++i < size)
		put_pixel(x + size, y + i, color, game);
	i = size;
	while (--i)
		put_pixel(x + i, y + size, color, game);
	i = size;
	while (--i)
		put_pixel(x, y + i, color, game);
	// for(int i = 0; i < size; i++)
}

void	draw_filled_square(int x, int y, int size, int color, t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < size)
			put_pixel(x + i, y + j, color, game);
	}
	// for(int i = 0; i < size; i++)
		// for(int j = 0; j < size; j++)
}

void	draw_floor_or_ceiling(bool floor, int color, t_game *game)// 0xdcdcdc	0x836953
{
	int	x;
	int	y;
	int	z;

	z = SCRN_HEIGHT;
	y = -1;
	if (floor)
		y += SCRN_HEIGHT / 2;
	else
		z /= 2;
	while (++y <= z)
	{
		x = -1;
		while (++x < FRM_WIDTH)
			put_pixel(x, y, color, game);
	}
}

void	draw_mini_map(t_game *game)
{
	int	x;
	int	y;
	int	z;
	int **map;
	int	color;

	z = BLOCK_SIZE;
	map = game->map;
	color = 0x0000FF;
	y = -1;
	while (++y < game->map_height)
	{
		x = -1;
		while (++x < game->map_width)
			if(map[y][x] > 0)
				draw_filled_square(FRM_WIDTH + x * z, y * z, z, color, game);
	}
	// for(int y = 0; y < 15; y++)
		// for(int	x = 0; x < 15; x++)
}

void	draw_mini_player(t_game *game)
{
	int		size = 5;
	double	x = game->mini_player.playerPos.x;
	double	y = game->mini_player.playerPos.y;
	draw_filled_square(x, y, size, 0x00FF00, game);
	draw_filled_square(x - size, y, size, 0x00FF00, game);
	draw_filled_square(x, y - size, size, 0x00FF00, game);
	draw_filled_square(x - size, y - size, size, 0x00FF00, game);
}

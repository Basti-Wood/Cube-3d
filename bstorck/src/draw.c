#include "../includes/game.h"

void	draw_floor_and_ceiling(t_game *game)
{
	int	x;
	int	y;
	// int	z;
	int	color;

	// z = SCRN_HEIGHT;
	// y = -1;
	// if (floor)
	// y += SCRN_HEIGHT / 2;
	// else
	// z /= 2;
	// while (++y <= z)
	// {
	// 	x = -1;
	// 	while (++x < FRM_WIDTH)
	// 		put_pixel(x, y, color, game);
	// }
	color = 0xdcdcdc;
	y = -1;
	while (++y <= SCRN_HEIGHT)
	{
		if (y >= SCRN_HEIGHT / 2)
			color = 0x836953;
		x = -1;
		while (++x < FRM_WIDTH)
			put_pixel(x, y, color, game);
	}
}

void	draw_empty_square(int x, int y, int size, int color, t_game *game)
{
	int	i;

	i = -1;
	while (++i < size)
		put_pixel(x + i, y, color, game);// north
	i = -1;
	while (++i < size)
		put_pixel(x + size - 1, y + i, color, game);// east
	i = size;
	while (--i)
		put_pixel(x + i, y + size - 1, color, game);// south
	i = size;
	while (--i)
		put_pixel(x, y + i, color, game);// west
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

void	draw_map(t_game *game)
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
		{
			if(map[y][x] > 0)
			{
				draw_filled_square(FRM_WIDTH + x * z, y * z, z, color, game);
				draw_empty_square(FRM_WIDTH + x * z, y * z, z, 16777215, game);
			}
		}
	}
	// for(int y = 0; y < 15; y++)
	// for(int	x = 0; x < 15; x++)
}

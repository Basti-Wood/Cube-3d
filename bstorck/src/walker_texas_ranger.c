#include "../includes/game.h"
#include <unistd.h>

void	draw_blimp(int x, int y, t_game *game)
{
	game->mini_player.pos.x = x + 0.5;
	game->mini_player.pos.y = y + 0.5;
	printf("\t%f\t%f\n", game->mini_player.pos.x, game->mini_player.pos.y);
	clear_image(game);
	draw_map(game);
	draw_player(game);
	// draw_radar(game);
	draw_floor_and_ceiling(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

char	get_direction(int *x, int *y, int flag, char prev, t_game *game)
{
	if (flag > 1)
	{
		if (*x && prev != 'W' && game->map[*y][*x - 1] == 1)//E->W
		{
			prev = 'E';
			(*x)--;
		}
		else if (*y && prev != 'N' && game->map[*y - 1][*x] == 1)//S-N
		{
			prev = 'S';
			(*y)--;
		}
		else if (*x < (game->map_width - 1) && prev != 'E' && game->map[*y][*x + 1] == 1)//W->E
		{
			prev = 'W';
			(*x)++;
		}
		else if (*y < (game->map_height - 1) && prev != 'S' && game->map[*y + 1][*x] == 1)//N->S
		{
			prev = 'N';
			(*y)++;
		}
		else
			prev = 0;
	}
	else
	{
		if (*x < (game->map_width - 1) && prev != 'E' && game->map[*y][*x + 1] == 1)//W->E
		{
			prev = 'W';
			(*x)++;
		}
		else if (*y < (game->map_height - 1) && prev != 'S' && game->map[*y + 1][*x] == 1)//N->S
		{
			prev = 'N';
			(*y)++;
		}
		else if (*x && prev != 'W' && game->map[*y][*x - 1] == 1)//E->W
		{
			prev = 'E';
			(*x)--;
		}
		else if (*y && prev != 'N' && game->map[*y - 1][*x] == 1)//S-N
		{
			prev = 'S';
			(*y)--;
		}
		else
			prev = 0;
	}
	return (prev);
}

int	get_start(int *x, int *y, t_game *game)
{
	// int		flag;
	// void	*start;

	// flag = 0;
	*y = -1;
	while (++*y < game->map_height/* && !flag*/)
	{
		*x = -1;
		while (++*x < game->map_width)
		{
			if (game->map[*y][*x] == 1)
			{
				return (0);
				// flag = 1;
				// break;
			}
		}
	}
	// start = &map[y][x];
	return (1);
}

int	i_walk_the_line(t_game *game)
{
	int		x;
	int		y;
	int		start_x;
	int		start_y;
	int		flag;
	char	prev;

	flag = get_start(&x, &y, game);
	if (flag == 1)
		return (1);
	flag = 0;
	start_x = x;
	start_y = y;
	prev = 0;
	prev = get_direction(&x, &y, flag, prev, game);
	if (!prev)
		return (1);
	draw_blimp(x, y, game);
	while (true)
	{
		if (x == start_x && y == start_y)
			break;
		if (prev == 'W')//W->E
		{
			prev = get_direction(&x, &y, flag, prev, game);
			draw_blimp(x, y, game);
			// if (!prev || prev == 'E')
				// return (1);
		}
		else if (prev == 'N')//N->S
		{
			flag = 1;
			prev = get_direction(&x, &y, flag, prev, game);
			draw_blimp(x, y, game);
			// if (!prev || prev == 'S')
				// return (1);
		}
		else if (prev == 'E')//E->W
		{
			flag = 2;
			prev = get_direction(&x, &y, flag, prev, game);
			draw_blimp(x, y, game);
			// if (!prev || prev == 'W')
				// return (1);
		}
		else if (prev == 'S')//S->N
		{
			prev = get_direction(&x, &y, flag, prev, game);
			draw_blimp(x, y, game);
			// if (!prev || prev == 'E')
				// return (1);
		}
		usleep(25000);
	}
	game->mini_player.pos.x = 11;
	game->mini_player.pos.y = 28;
	return (0);
	// while (++y < game->map_height && !flag)
	// {
	// 	while (++x < game->map_width)
	// 	{
	// 		if (game->map[y][x] == 1)
	// 		{
	// 			flag = 1;
	// 			break;
	// 		}
	// 	}
	// 	x = -1;
	// }
}

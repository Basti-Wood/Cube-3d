#include "../includes/game.h"
#include <unistd.h>

void	draw_blip(int x, int y, t_game *game)
{
	game->mini_player.pos.x = x + 0.5;
	game->mini_player.pos.y = y + 0.5;
	// printf("\t%f\t%f\n", game->mini_player.pos.x, game->mini_player.pos.y);
	clear_image(game);
	draw_map(game);
	draw_player(game);
	// draw_radar(game);
	// draw_floor_and_ceiling(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

int		probe_direction(int x, int y, t_game *game)
{
	if (!(x >= 0 && x < game->map_width && y >=0 && y < game->map_height))
		return (0);
	return (game->map[y][x]);
}

t_square	get_direction(char prev, char *tmp, int i)
{
	t_square	dir;
	int			d;

	if (prev == 'W')
		d = 0;
	else if (prev == 'N')
		d = 1;
	else if (prev == 'E')
		d = 2;
	else if (prev == 'S')
		d = 3;
	d = (d + i) % 4 + 1;
	dir.x = 0;
	dir.y = 0;
	if (d == 1)
	{
		*tmp = 'E';
		dir.x = -1;//go WEST
	}
	else if (d == 2)
	{
		*tmp = 'S';
		dir.y = -1;//go NORTH
	}
	else if (d == 3)
	{
		*tmp = 'W';
		dir.x = 1;//go EAST
	}
	else
	{
		*tmp = 'N';
		dir.y = 1;//go SOUTH
	}
	return (dir);
}

char	walk_to_next_tile(int *x, int *y, char prev, t_game *game)
{
	t_square	dir;
	// char		c_dir;
	char 		tmp;
	int			i;
	int			s;

	s = 0;
	i = 0;
	while (++i < 5)
	{
		dir = get_direction(prev, &tmp, i);
		if (probe_direction(*x + dir.x, *y + dir.y, game))
		{
			// printf("\tdir_x\t%i\tdir_y\t%i\t%c", v_dir.x, v_dir.y, prev);
			prev = tmp;
			*x += dir.x;
			*y += dir.y;
			return (prev);
		}
	}
	return (0);
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
	char	prev;
	char	first;
	char	last;
	int		i;
	int		x;
	int		y;
	int		start_x;
	int		start_y;

	if (get_start(&x, &y, game))
		return (1);
	start_x = x;
	start_y = y;
	i = 0;
	prev = 'W';
	while (true)
	{
		prev = walk_to_next_tile(&x, &y, prev, game);
		if (!prev)
			return (1);
		if (i == 0)
			first = prev;
		if (x == start_x && y == start_y)
			break;
		draw_blip(x, y, game);
		usleep(5000);
		i++;
	}
	last = prev;
	if ((first == 'W' && last == 'E') || (first == 'N' && last == 'S') || (first == 'E' && last == 'W') || (first == 'S' && last == 'N'))
		return (1);
	game->mini_player.pos.x = 11;
	game->mini_player.pos.y = 28;
	return (0);
}

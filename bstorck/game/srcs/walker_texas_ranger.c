/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walker_texas_ranger.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstorck <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 15:23:02 by bstorck           #+#    #+#             */
/*   Updated: 2025/11/21 15:23:04 by bstorck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/game.h"

int	probe_direction(t_game *game)
{
	t_walker	*w;
	int			x;
	int			y;

	w = &game->walker;
	x = w->pos.x + w->dir.x;
	y = w->pos.y + w->dir.y;
	if (x >= 0 && x < game->map_width && y >= 0 && y < game->map_height)
		return (game->map[y][x]);
	return (0);
}

int	get_direction(t_game *game)
{
	t_walker	*walker;
	int			i;

	walker = &game->walker;
	i = 0;
	while (++i < 5)
	{
		walker->dir = walker->wind_rose[(walker->prev + i) % 4];
		if (probe_direction(game))
		{
			walker->prev = (walker->prev + i + 2) % 4;
			walker->pos.x += walker->dir.x;
			walker->pos.y += walker->dir.y;
			return (0);
		}
	}
	return (1);
}

int	get_start(t_game *game)
{
	t_walker	*walker;

	walker = &game->walker;
	walker->pos.y = -1;
	while (++walker->pos.y < game->map_height)
	{
		walker->pos.x = -1;
		while (++walker->pos.x < game->map_width)
		{
			if (game->map[walker->pos.y][walker->pos.x] == 1)
			{
				walker->start.x = walker->pos.x;
				walker->start.y = walker->pos.y;
				return (0);
			}
		}
	}
	return (1);
}

int	intro_loop(t_game *game)
{
	t_walker	*w;

	w = &game->walker;
	if (get_direction(game))
	{
		printf("Error\nInvalid map.\n");
		close_game(game);
	}
	w->last = w->wind_rose[w->prev];
	if (!game->skip_intro)
		draw_walker(w->pos.x, w->pos.y, game);
	if (w->pos.x == w->start.x && w->pos.y == w->start.y)
	{
		if ((w->first.x + w->last.x == 0) && (w->first.y + w->last.y == 0))
		{
			printf("Error\nThe map must be closed/surrounded by walls.\n");
			close_game(game);
		}
		mlx_destroy_image(game->mlx, game->img);
		mlx_destroy_window(game->mlx, game->win);
	}
	return (0);
}

// printf("\tfirst\t%i\t%i\n", g->walker.first.x, g->walker.first.y);
// printf("\tlast\t%i\t%i\n\n", g->walker.last.x, g->walker.last.y);
// printf("\tstart\t%i\t%i\n", g->walker.start.x, g->walker.start.y);
// printf("\tpos\t%i\t%i\n\n", g->walker.pos.x, g->walker.pos.y);

// void	i_walk_the_line(t_game *game)
// {
// 	t_walker	w;
// 	int			i;
//
// 	init_walker(&w);
// 	if (get_start(&w, game))
// 		throw_error(0, game);
// 	i = 0;
// 	while (true)
// 	{
// 		w.prev = get_direction(&w, game);
// 		if (w.prev == -1)
// 			throw_error(1, game);
// 		if (!i)
// 			w.first = w.wind_rose[w.prev];
// 		i++;
// 		w.last = w.wind_rose[w.prev];
// 		if (w.pos.x == w.start.x && w.pos.y == w.start.y)
// 			break ;
// 		if (!game->skip_intro)
// 			draw_blip(w.pos.x, w.pos.y, game);
// 	}
// 	if ((w.first.x + w.last.x == 0) && (w.first.y + w.last.y == 0))
// 		throw_error(99, game);
// }

	// printf("\tfirst\t%i\t%i\n", w.first.x, w.first.y);
	// printf("\tlast\t%i\t%i\n", w.last.x, w.last.y);
	// printf("\n\t\t%i + %i = %i\n\t\t%i + %i = %i\n", w.first.x, w.last.x, w.first.x + w.last.x, w.first.y, w.last.y, w.first.y + w.last.y);
// t_square	get_direction(char prev, char *tmp, int i)
// {
// 	t_square	dir;
// 	int			d;
//
// 	// d = 0;
// 	// while (windrose[d] != prev)
// 	// 	d++;
// 	if (prev == 'W')
// 		d = 0;
// 	else if (prev == 'N')
// 		d = 1;
// 	else if (prev == 'E')
// 		d = 2;
// 	else if (prev == 'S')
// 		d = 3;
// 	d = (d + i) % 4 + 1;
// 	if (d == 1)
// 	{
// 		*tmp = 'E';
// 		dir.x = -1;//go WEST
// 		dir.y = 0;
// 	}
// 	else if (d == 2)
// 	{
// 		*tmp = 'S';
// 		dir.x = 0;
// 		dir.y = -1;//go NORTH
// 	}
// 	else if (d == 3)
// 	{
// 		*tmp = 'W';
// 		dir.x = 1;//go EAST
// 		dir.y = 0;
// 	}
// 	else
// 	{
// 		*tmp = 'N';
// 		dir.x = 0;
// 		dir.y = 1;//go SOUTH
// 	}
// 	return (dir);
// }

// char	i_walk_the_line(int *x, int *y, char prev, t_game *game)
// {
// 	t_square	dir;
// 	char 		tmp;
// 	int			i;
//
// 	i = 0;
// 	while (++i < 5)
// 	{
// 		dir = get_direction(prev, &tmp, i);
// 		if (probe_direction(*x + dir.x, *y + dir.y, game))
// 		{
// 			// printf("\tdir_x\t%i\tdir_y\t%i\t%c", v_dir.x, v_dir.y, prev);
// 			prev = tmp;
// 			*x += dir.x;
// 			*y += dir.y;
// 			return (prev);
// 		}
// 	}
// 	return (0);
// }

// if (flag > 1)
// {
// 	if (*x && prev != 'W' && game->map[*y][*x - 1] == 1)//E->W
// 	{
// 		prev = 'E';
// 		(*x)--;
// 	}
// 	else if (*y && prev != 'N' && game->map[*y - 1][*x] == 1)//S-N
// 	{
// 		prev = 'S';
// 		(*y)--;
// 	}
// 	else if (*x < (game->map_width - 1) && prev != 'E' && game->map[*y][*x + 1] == 1)//W->E
// 	{
// 		prev = 'W';
// 		(*x)++;
// 	}
// 	else if (*y < (game->map_height - 1) && prev != 'S' && game->map[*y + 1][*x] == 1)//N->S
// 	{
// 		prev = 'N';
// 		(*y)++;
// 	}
// 	else
// 		prev = 0;
// }

// if (prev == 'W')//W->E
// {
// 	prev = get_direction(&x, &y, prev, game);
// 	draw_blimp(x, y, game);
// 	// if (!prev || prev == 'E')
// 	// return (1);
// }
// else if (prev == 'N')//N->S
// {
// 	prev = get_direction(&x, &y, prev, game);
// 	draw_blimp(x, y, game);
// 	// if (!prev || prev == 'S')
// 	// return (1);
// }
// else if (prev == 'E')//E->W
// {
// 	prev = get_direction(&x, &y, prev, game);
// 	draw_blimp(x, y, game);
// 	// if (!prev || prev == 'W')
// 	// return (1);
// }
// else if (prev == 'S')//S->N
// {
// 	prev = get_direction(&x, &y, prev, game);
// 	draw_blimp(x, y, game);
// 	// if (!prev || prev == 'N')
// 	// return (1);
// }

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

// char	get_c_direction(char prev, int i)
// {
// 	int	d;
//
// 	if (prev == 'W')
// 		d = 0;
// 	else if (prev == 'N')
// 		d = 1;
// 	else if (prev == 'E')
// 		d = 2;
// 	else if (prev == 'S')
// 		d = 3;
// 	d = (d + i) % 4 + 1;
// 	if (d == 1)
// 		return ('W');
// 	else if (d == 2)
// 		return ('N');
// 	else if (d == 3)
// 		return ('E');
// 	else
// 		return ('S');
// }

// char	i_walk_the_line(int *x, int *y, char prev, t_game *game)
// {
// 	char		c_dir;
// 	char 		tmp;
// 	int			i;
//
// 	i = 0;
// 	while (++i < 5)
// 		get_c_direction(&prev, &dir, i);
// 		c_dir = get_direction(prev, i);
// 	if (c_dir == 'W')
// 	{
// 		if (*x && game->map[*y][*x - 1] == 1)//go WEST
// 		{
// 			printf("\t%c\t%c\n", prev, c_dir);
// 			prev = 'E';
// 			(*x)--;
// 			return (prev);
// 		}
// 	}
// 	else if (c_dir == 'S')
// 	{
// 		if (*y < (game->map_height - 1) && game->map[*y + 1][*x] == 1)//go SOUTH
// 		{
// 			printf("\t%c\t%c\n", prev, c_dir);
// 			prev = 'N';
// 			(*y)++;
// 			return (prev);
// 		}
// 	}
// 	else if (c_dir == 'E')
// 	{
// 		if (*x < (game->map_width - 1) && game->map[*y][*x + 1] == 1)//go EAST
// 		{
// 			printf("\t%c\t%c\n", prev, c_dir);
// 			prev = 'W';
// 			(*x)++;
// 			return (prev);
// 		}
// 	}
// 	else if (c_dir == 'N')
// 	{
// 		if (*y && game->map[*y - 1][*x] == 1)//go NORTH
// 		{
// 			printf("\t%c\t%c\n", prev, c_dir);
// 			prev = 'S';
// 			(*y)--;
// 			return (prev);
// 		}
// 	}
// 	return (0);
// }

// char	get_direction(int *x, int *y, char prev, t_game *game)
// {
// 	if (prev == 'N')
// 	{
// 		// printf("prev N->");
// 		if (*x && game->map[*y][*x - 1] == 1)//N->W
// 		{
// 			prev = 'E';
// 			(*x)--;
// 			// printf("W\n");
// 		}
// 		else if (*y < (game->map_height - 1) && game->map[*y + 1][*x] == 1)//N->S
// 		{
// 			prev = 'N';
// 			(*y)++;
// 			// printf("S\n");
// 		}
// 		else if (*x < (game->map_width - 1) && game->map[*y][*x + 1] == 1)//N->E
// 		{
// 			prev = 'W';
// 			(*x)++;
// 			// printf("E\n");
// 		}
// 		else if (*y && game->map[*y - 1][*x] == 1)//S->N
// 		{
// 			prev = 'S';
// 			(*y)--;
// 			// printf("N\n");
// 		}
// 		else
// 			prev = 0;
// 	}
// 	else if (prev == 'W')
// 	{
// 		// printf("prev W->");
// 		if (*y < (game->map_height - 1) && game->map[*y + 1][*x] == 1)//W->S
// 		{
// 			prev = 'N';
// 			(*y)++;
// 			// printf("S\n");
// 		}
// 		else if (*x < (game->map_width - 1) && game->map[*y][*x + 1] == 1)//W->E
// 		{
// 			prev = 'W';
// 			(*x)++;
// 			// printf("E\n");
// 		}
// 		else if (*y && game->map[*y - 1][*x] == 1)//W->N
// 		{
// 			prev = 'S';
// 			(*y)--;
// 			// printf("N\n");
// 		}
// 		else// if (*x && game->map[*y][*x - 1] == 1)//E->W
// 		{
// 			prev = 'E';
// 			(*x)--;
// 			// printf("W\n");
// 		}
// 	}
// 	else if (prev == 'S')
// 	{
// 		// printf("prev S->");
// 		if (*x < (game->map_width - 1) && game->map[*y][*x + 1] == 1)//S->E
// 		{
// 			prev = 'W';
// 			(*x)++;
// 			// printf("E\n");
// 		}
// 		else if (*y && game->map[*y - 1][*x] == 1)//S->N
// 		{
// 			prev = 'S';
// 			(*y)--;
// 			// printf("N\n");
// 		}
// 		else if (*x && game->map[*y][*x - 1] == 1)//S->W
// 		{
// 			prev = 'E';
// 			(*x)--;
// 			// printf("W\n");
// 		}
// 		else// if (*y < (game->map_height - 1) && game->map[*y + 1][*x] == 1)//N->S
// 		{
// 			prev = 'N';//'N';
// 			(*y)++;
// 			// printf("S\n");
// 		}
// 	}
// 	else if (prev == 'E')
// 	{
// 		// printf("prev E->");
// 		if (*y && game->map[*y - 1][*x] == 1)//E->N//go NORTH
// 		{
// 			prev = 'S';
// 			(*y)--;
// 			// printf("N\n");
// 		}
// 		else if (*x && game->map[*y][*x - 1] == 1)//E->W//go WEST
// 		{
// 			prev = 'E';
// 			(*x)--;
// 			// printf("W\n");
// 		}
// 		else if (*y < (game->map_height - 1) && game->map[*y + 1][*x] == 1)//E->S//go SOUTH
// 		{
// 			prev = 'N';
// 			(*y)++;
// 			// printf("S\n");
// 		}
// 		else// if (*x < (game->map_width - 1) && game->map[*y][*x + 1] == 1)//W->E//go back
// 		{
// 			prev = 'W';
// 			(*x)++;
// 			// printf("E\n");
// 		}
// 	}
// 	return (prev);
// }

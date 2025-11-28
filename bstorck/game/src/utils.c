/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstorck <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 15:24:18 by bstorck           #+#    #+#             */
/*   Updated: 2025/11/21 15:24:19 by bstorck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"

void	clear_image(t_game *game)
{
	int	x;
	int	y;

	y = -1;
	while (++y <= SCRN_HEIGHT)
	{
		x = -1;
		while (++x <= SCRN_WIDTH)
			put_pixel(x, y, 0, game);
	}
	// for(int y = 0; y < SCRN_HEIGHT; y++)
	// 	for(int x = 0; x < SCRN_WIDTH; x++)
	// 		put_pixel(x, y, 0, game);
}

void	put_pixel(int x, int y, int color, t_game *game)
{
	int	index;

	if (x >= SCRN_WIDTH || y >= SCRN_HEIGHT || x < 0 || y < 0)
		return ;
	index = y * game->size_line + x * game->bpp / 8;
	game->data[index] = color & 0xFF;
	game->data[index + 1] = (color >> 8) & 0xFF;
	game->data[index + 2] = (color >> 16) & 0xFF;
}

time_t	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(int usec)
{
	time_t	time_to_sleep;
	time_t	time_to_awake;

	time_to_sleep = usec / 1000;
	time_to_awake = get_current_time() + time_to_sleep;
	while (get_current_time() < time_to_awake)
		continue ;
}

// int	ft_strcmp(char const *s1, char const *s2)
// {
// 	while ((*s1 && *s2) && (*s1 == *s2))
// 	{
// 		s1++;
// 		s2++;
// 	}
// 	return ((unsigned char)*s1 - (unsigned char)*s2);
// }

// double	distance(double x, double y)
// {
	// return (sqrt(x * x + y * y));
// }

// double	fixed_dist(double x1, double y1, double x2, double y2, t_game *game)
// {
// 	double	dir_angle = atan2(game->hero.dir.y, game->hero.dir.x);
// 	double	delta_x = x2 - x1;
// 	double	delta_y = y2 - y1;
// 	double	angle = atan2(delta_y, delta_x) - dir_angle;
// 	double	fix_dist = distance(delta_x, delta_y) * cos(angle);
// 	return (fix_dist);
// }

// if(hero->mini == false)
// {
// 	double	dist = fixed_dist(hero->pos.x, hero->pos.y, ray_x, ray_y, game);
// 	double	height = (BLOCK_SIZE / dist) * (((double)FRM_WIDTH) / 2);
// 	int	start_y = (SCRN_HEIGHT - height) / 2;
// 	int	end = start_y + height;
// 	while(start_y < end)
// 	{
// 		put_pixel(i, start_y, 255, game);
// 		start_y++;
// 	}
// }

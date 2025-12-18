/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstorck <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 15:24:18 by bstorck           #+#    #+#             */
/*   Updated: 2025/12/09 07:35:13 by bstorck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/game.h"

void	set_dev_mode(t_dev_mode *dev_mode)
{
	dev_mode->render_ceiling = true;
	dev_mode->render_floor = true;
	dev_mode->render_walls = true;
	dev_mode->render_map = true;
	dev_mode->render_sprites = true;
}

void	put_pixel(int x, int y, int color, t_game *game)
{
	int	index;

	if (x >= game->img.width || y >= game->img.height || x < 0 || y < 0)
		return ;
	index = y * game->img.size_line + x * game->img.bpp / 8;
	game->img.data[index] = color & 0xFF;
	game->img.data[index + 1] = (color >> 8) & 0xFF;
	game->img.data[index + 2] = (color >> 16) & 0xFF;
}

void	clear_image(t_game *game)
{
	int	x;
	int	y;

	y = -1;
	while (++y <= game->img.height)
	{
		x = -1;
		while (++x <= game->img.width)
			put_pixel(x, y, 0, game);
	}
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor+ceiling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstorck <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 07:21:25 by bstorck           #+#    #+#             */
/*   Updated: 2025/12/05 07:31:54 by bstorck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/game.h"

// void	draw_floor_and_ceiling(t_game *game)
// {
// 	int	x;
// 	int	y;
// 	int	color;
//
// 	color = 0x303030;
// 	y = -1;
// 	while (++y <= WIN_HEIGHT)
// 	{
// 		x = -1;
// 		while (++x < WIN_WIDTH)
// 		{
// 			if (((game->img.width - game->map.node_size.x - 20) <= x)
// 				&& (x <= (game->img.width - 20))
// 				&& (20 <= y && y < game->map.node_size.y + 20))
// 				color = 0x181818;
// 			else
// 				color = 0x303030;
// 			if (y >= WIN_HEIGHT / 2)
// 				color = 0x707070;
// 			put_pixel(x, y, color, game);
// 		}
// 	}
// }

static int	get_color(int x, int y, int tex_num, t_game *game)
{
	int		color;
	t_floor	*f;

	f = &game->floor;
	f->tex.x = (int)(game->texture[tex_num].width * (f->pos.x - (int)f->pos.x))
		& (game->texture[tex_num].width - 1);
	f->tex.y = (int)(game->texture[tex_num].width * (f->pos.y - (int)f->pos.y))
		& (game->texture[tex_num].height - 1);
	color = game->texture[tex_num].pixel_map[f->tex.y
		* game->texture[tex_num].width + f->tex.x];
	color = (color >> 1) & 8355711;
	if (tex_num == 5
		&& ((game->img.width - game->map.node_size.x - 20) <= x)
		&& (x <= (game->img.width - 20))
		&& (game->img.height - game->map.node_size.y - 21) <= y
		&& (y <= (game->img.height - 21)))
		color = (color >> 1) & 8355711;
	return (color);
}

static void	set_floor_values(int y, t_game *game)
{
	t_floor	*f;

	f = &game->floor;
	f->ray_dir_start.x = game->hero.dir.x - game->hero.plane.x;
	f->ray_dir_start.y = game->hero.dir.y - game->hero.plane.y;
	f->ray_dir_end.x = game->hero.dir.x + game->hero.plane.x;
	f->ray_dir_end.y = game->hero.dir.y + game->hero.plane.y;
	f->p = y - game->half_screen;
	f->z_pos = game->half_screen;
	f->dist_row = f->z_pos / f->p;
	f->step.x = f->dist_row * (f->ray_dir_end.x - f->ray_dir_start.x)
		/ game->img.width;
	f->step.y = f->dist_row * (f->ray_dir_end.y - f->ray_dir_start.y)
		/ game->img.width;
	f->pos.x = game->hero.pos.x + f->dist_row * f->ray_dir_start.x;
	f->pos.y = game->hero.pos.y + f->dist_row * f->ray_dir_start.y;
}

void	draw_floor_and_ceiling(t_game *game)
{
	int		x;
	int		y;
	int		color;
	t_floor	*f;

	f = &game->floor;
	y = -1;
	while (++y < game->img.height)
	{
		set_floor_values(y, game);
		x = -1;
		while (++x < game->img.width)
		{
			color = get_color(x, y, 1, game);
			put_pixel(x, y, color, game);
			color = get_color(x, y, 5, game);
			put_pixel(x, game->img.height - y - 1, color, game);
			f->pos.x += f->step.x;
			f->pos.y += f->step.y;
		}
	}
}

//	 f->tex.x = (int)(game->texture[4].width * (f->pos.x - (int)f->pos.x))
//		& (game->texture[4].width - 1);
//	 f->tex.y = (int)(game->texture[4].width * (f->pos.y - (int)f->pos.y))
//		& (game->texture[4].height - 1);
//	 color = game->texture[4].pixel_map[f->tex.y
//	 * game->texture[4].width + f->tex.x];
//	 put_pixel(x, y, color, game);
//	 f->tex.x = (int)(game->texture[5].width * (f->pos.x - (int)f->pos.x))
//		& (game->texture[5].width - 1);
//	 f->tex.y = (int)(game->texture[5].width * (f->pos.y - (int)f->pos.y))
//		& (game->texture[5].height - 1);
//	 color = game->texture[5].pixel_map[f->tex.y
//	 * game->texture[5].width + f->tex.x];
//	 if (((game->img.width - game->map.node_size.x - 20) <= x)
//		&& (x <= (game->img.width - 20))
//		&& (game->img.height - game->map.node_size.y - 21) <= y
//		&& (y <= (game->img.height - 21)))
//		color = (color >> 1) & 8355711;
//	 put_pixel(x, game->img.height - y - 1, color, game);

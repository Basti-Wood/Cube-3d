/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstorck <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 00:14:56 by bstorck           #+#    #+#             */
/*   Updated: 2025/12/04 00:14:57 by bstorck          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/game.h"

static void	set_node_size(t_game *game)
{
	t_map	*m;

	m = &game->map;
	m->node_size.x = MAX_NODE_SIZE;
	m->node_size.y = MAX_NODE_SIZE;
	if (m->width > m->height)
	{
		m->tile_size = m->node_size.x / m->width;
		m->node_size.x = m->tile_size * m->width;
		m->node_size.y = m->tile_size * m->height;
	}
	else
	{
		m->tile_size = m->node_size.y / m->height;
		m->node_size.x = m->tile_size * m->width;
		m->node_size.y = m->tile_size * m->height;
	}
}

void	init_game_window(t_game *g)
{
	t_img	*i;

	i = &g->img;
	i->width = WIN_WIDTH;
	i->height = WIN_HEIGHT;
	i->aspect_ratio = (double)i->width / (double)i->height;
	set_node_size(g);
	g->half_screen = (double)i->height / 2;
	g->win = mlx_new_window(g->mlx, i->width, i->height, "Picostein: Zero D");
	i->ptr = mlx_new_image(g->mlx, i->width, i->height);
	i->data = mlx_get_data_addr(i->ptr, &i->bpp, &i->size_line, &i->endian);
	mlx_hook(g->win, 2, 1L << 0, key_press, g);
	mlx_hook(g->win, 3, 1L << 1, key_release, g);
	mlx_hook(g->win, WIN_X_BTN, 0, close_game, g);
}

static double	pulse_distance(t_vector start, t_vector pulse, double dir)
{
	return (fabs((pulse.y - start.y) / sin(dir)));
}

//0.15625 * game->map.tile_size
int	game_loop(t_game *game)
{
	if (get_current_time() > (game->last_check + CHECK_AFTER))
	{
		reset_doors(&game->hero, &game->map);
		game->last_check = get_current_time();
	}
	hero_action(&game->hero, &game->map);
	hero_action(&game->mini_hero, &game->map);
	clear_image(game);
	draw_floor_and_ceiling(game);
	if (game->dev_mode.render_walls)
		draw_walls(game);
	if (game->dev_mode.render_map)
	{
		draw_radar(game);
		draw_map(false, game);
		// draw_sonar(game);
		draw_hero(false, game->mini_hero.pos, game->map.tile_size / 6, game);
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img.ptr, 0, 0);
	return (0);
}

// void	draw_pulse(double dir, t_game *game)
// {
// 	t_vector	pulse;
// 	t_vector	start;
// 	t_square	offset;
// 	double		tile_size;
//
// 	tile_size = game->map.tile_size;
// 	offset = get_offset(false, game);
// 	pulse.x = game->mini_hero.pos.x * tile_size;
// 	pulse.y = game->mini_hero.pos.y * tile_size;
// 	start.x = pulse.x;
// 	start.y = pulse.y;
// 	// while (/*!collision(pulse.x / BLOCK_SIZE, pulse.y / BLOCK_SIZE, game->map) && */ (sqrt(pow((pulse.x - start.x), 2) + pow((pulse.y - start.y), 2)) < 7))
// 	// while (sqrt(pow((pulse.x - start.x), 2) + pow((pulse.y - start.y), 2)) <= game->hero.collision_radius)
// 	while (pulse_distance(start, pulse, dir) <= (0.15625 * tile_size))
// 	{
// 		// printf("\tpulse=%f\n", sqrt(powf((pulse.x - start.x), 2) +  powf((pulse.y - start.y), 2)));
// 		// put_pixel(pulse.x + WIN_WIDTH / 2, pulse.y, 0x00FF00, game);
// 		pulse.x += cos(dir);
// 		pulse.y += sin(dir);
// 	}
// 	put_pixel(pulse.x + offset.x, pulse.y + offset.y, 0x00FF00, game);
// 	// printf("\tpulse.len=%f", sqrt(powf((pulse.x - start.x), 2) +  powf((pulse.y - start.y), 2)));
// 	// printf("\tpulse.x=%i\tpulse.y=%i\n", (int)(pulse.x / BLOCK_SIZE), (int)(pulse.y / BLOCK_SIZE));
// 	// while (sqrt(pow((pulse.x - start.x), 2) + pow((pulse.y - start.y), 2)) <= 2.5)
// 	// {
// 	// 	// printf("\tpulse=%f\n", sqrt(powf((pulse.x - start.x), 2) +  powf((pulse.y - start.y), 2)));
// 	// 	// put_pixel(pulse.x + WIN_WIDTH / 2, pulse.y, 0x00FF00, game);
// 	// 	pulse.x += cos(dir);
// 	// 	pulse.y += sin(dir);
// 	// }
// 	// put_pixel(pulse.x + (double)WIN_WIDTH / 2, pulse.y, 0xFF00FF, game);
// }
//
// void	draw_sonar(t_game *game)
// {
// 	int			i;
// 	double		dir;
// 	double		delta_dir;
// 	t_hero		*hero;
//
// 	hero = &game->hero;
// 	delta_dir = PI / 45;
// 	dir = atan2(hero->dir.y, hero->dir.x);
// 	i = -1;
// 	while (++i < 90)
// 	{
// 		draw_pulse(dir, game);
// 		dir += delta_dir;
// 	}
// }

#include "../includes/game.h"

void	draw_line(int screen_x, t_game *game)
{
	int	line_height;
	int	start_y;
	int	end_y;
	int	color;

	line_height = (int)(SCRN_HEIGHT / game->player.ray.perp_dist_wall) / 2;
	start_y = (SCRN_HEIGHT / 2) - (line_height / 2);
	if (start_y < 0)
		start_y = 0;
	end_y = (SCRN_HEIGHT / 2) + (line_height / 2);
	if (end_y < 0)
		end_y = 0;
	while (start_y <= end_y)
	{
		color = 0x0000FF;
		if (game->player.ray.side)
			color /= 2;
		put_pixel(screen_x, start_y, color, game);
		start_y++;
	}
}

void	draw_walls(t_game *game)
{
	int			i;
	t_ray		*ray;
	t_player	*hero;

	hero = &game->player;
	ray = &hero->ray;
	i = -1;
	while (++i < FRM_WIDTH)
	{
		hero->scan_x = 2 * i / (double)FRM_WIDTH - 1;
		cast_ray(hero);
		dda(game);
		if (ray->side)
			ray->perp_dist_wall = ray->side_dist.y - ray->delta_dist.y;
		else
			ray->perp_dist_wall = ray->side_dist.x - ray->delta_dist.x;
		draw_line(i, game);
	}
}

void	draw_beam(double beam, t_game *game)
{
	double	beam_x;
	double	beam_y;

	beam_x = game->mini_player.pos.x * BLOCK_SIZE;
	beam_y = game->mini_player.pos.y * BLOCK_SIZE;
	while (!collision(beam_x / BLOCK_SIZE, beam_y / BLOCK_SIZE, game->map))
	{
		put_pixel(beam_x + FRM_WIDTH, beam_y, 0xFF0000, game);
		beam_x += cos(beam);
		beam_y += sin(beam);
	}
}

void	draw_radar(t_game *game)
{
	t_player	*hero;
	double		beam;
	double		dir;
	int			i;

	hero = &game->mini_player;
	beam = atan2(hero->dir.y, hero->dir.x) - (hero->fov / 2);
	dir = hero->fov / FRM_WIDTH;
	i = -1;
	while (++i < FRM_WIDTH)
	{
		draw_beam(beam, game);
		beam += dir;
	}
}

void	draw_hero(double x, double y, int size, t_game *game)
{
	t_square	square;

	square.x = x * BLOCK_SIZE + FRM_WIDTH;
	square.y = y * BLOCK_SIZE;
	draw_filled_square(square, size, 0x00FF00, game);
	square.x = x * BLOCK_SIZE + FRM_WIDTH - size;
	draw_filled_square(square, size, 0x00FF00, game);
	square.x = x * BLOCK_SIZE + FRM_WIDTH;
	square.y = y * BLOCK_SIZE - size;
	draw_filled_square(square, size, 0x00FF00, game);
	square.x = x * BLOCK_SIZE + FRM_WIDTH - size;
	draw_filled_square(square, size, 0x00FF00, game);
}

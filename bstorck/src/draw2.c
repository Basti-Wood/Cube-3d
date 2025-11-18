#include "../includes/game.h"

void	draw_line(int screen_x, t_game *game)
{
	int	line_height;
	int	start_y;
	int	end_y;
	int	color;

	line_height = (int)(SCRN_HEIGHT / game->player.ray.perp_dist_wall) / 2;
	// printf("\tline_height = %i\n", line_height);
	start_y = (SCRN_HEIGHT / 2) - (line_height / 2);
	if (start_y < 0)
		start_y = 0;
	end_y = (SCRN_HEIGHT / 2) + (line_height / 2);
	if (end_y < 0)
		end_y = 0;
	while (start_y <= end_y)
	{
		color = 255;
		if (game->player.ray.side)
			color /= 2;
		put_pixel(screen_x, start_y, color, game);
		start_y++;
	}
}

void	draw_walls(t_game *game)
{
	int			screen_x;
	t_ray		*ray;
	t_player	*player;

	player = &game->player;
	ray = &player->ray;
	screen_x = -1;
	while (++screen_x < FRM_WIDTH)
	{
		// if (x == 0)
		// 	printf("%i\n", x);
		player->scan_x = 2 * screen_x / (double)FRM_WIDTH - 1;
		// printf("\tscan_x\t%f\n", player->scan_x);
		cast_ray(player);
		// printf("\tdirX\t%f\tdirY\t%f\n", ray->dir.x, ray->dir.y);
		// printf("\t%d\t%d\n", game->player.ray.map.x, game->player.ray.map.y);
		// printf("%f\n", game->player.ray.delta_dist.y);
		dda(game);
		// printf("\n\tdeltaX\t%f\tdeltaY\t%f\n", game->player.ray.delta_dist.x, game->player.ray.delta_dist.y);
		// printf("\tsideX\t%f\tsideY\t%f\n", game->player.ray.side_dist.x, game->player.ray.side_dist.y);
		// printf("\tmapX\t%i\t\tmapY\t%i\n\n", game->player.ray.map.x, game->player.ray.map.y);
		// printf("\t%d\t%d\n", game->player.ray.map.x, game->player.ray.map.y);
		// draw_line(true, game);
		if (ray->side)
		// {
			ray->perp_dist_wall = ray->side_dist.y - ray->delta_dist.y;
			// printf("DING!");
		// }
		else
			ray->perp_dist_wall = ray->side_dist.x - ray->delta_dist.x;
		// printf("\twall_dist = %f\n", ray->perp_dist_wall);
		draw_line(screen_x, game);
	}
}

// radar functions
void	draw_beam(double beam, t_game *game)
{
	// double	cos_angle = cos(start_x);
	// double	sin_angle = sin(start_x);
	double	beam_x;
	double	beam_y;

	beam_x = game->mini_player.pos.x * BLOCK_SIZE;
	beam_y = game->mini_player.pos.y * BLOCK_SIZE;
	while(!collision(beam_x / BLOCK_SIZE, beam_y / BLOCK_SIZE, game->map))
	{
		// if(player->mini == true)
		put_pixel(beam_x + FRM_WIDTH, beam_y, 0xFF0000, game);
		beam_x += cos(beam);
		beam_y += sin(beam);
	}
}

void	draw_radar(t_game *game)
{
	// double	angle = atan2(mini_player->dir.y, mini_player->dir.x);
	// printf("\tangle = %f\n", atan2(mini_player->dir.y, mini_player->dir.x));
	t_player	*player;
	double		fraction;
	double		sweep_x;
	int			screen_x;

	player = &game->mini_player;
	fraction = player->fov / FRM_WIDTH;// 3
	// printf("\tfraction = %f\n", fraction);
	sweep_x = atan2(player->dir.y, player->dir.x) - (player->fov / 2);// 6
	// printf("\tstart_x = %f\n", start_x);
	// fraction = PI / 2 / FRM_WIDTH;// 3
	// start_x = angle - (PI / 4);// 6
	screen_x = -1;
	while(++screen_x < FRM_WIDTH)
	{
		// printf("\tfraction = %f\n", fraction);
		// printf("\tstart_x = %f\n", start_x);
		draw_beam(sweep_x, game);
		sweep_x += fraction;
	}
}

void	draw_player(t_game *game)
{
	int		size = 5;
	double	x = game->mini_player.pos.x * BLOCK_SIZE + FRM_WIDTH;
	double	y = game->mini_player.pos.y * BLOCK_SIZE;
	draw_filled_square(x, y, size, 0x00FF00, game);
	draw_filled_square(x - size, y, size, 0x00FF00, game);
	draw_filled_square(x, y - size, size, 0x00FF00, game);
	draw_filled_square(x - size, y - size, size, 0x00FF00, game);
}

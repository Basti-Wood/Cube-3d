#include "../includes/game.h"

int	close_game(t_game *game)
{
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	int i = 0;
	while (game->map[i])
	{
		free(game->map[i]);
		i++;
	}
	free(game->map);
	exit(0);
	return (0);
}

// raycasting functions
void	draw_line(t_player *player, t_game *game, double start_x, int i)
{
	// double	cos_angle = cos(start_x);
	// double	sin_angle = sin(start_x);
	double	ray_x = player->playerPos.x;
	double	ray_y = player->playerPos.y;
	// printf("\t%f", player->playerPos.x);
	// printf("\t%f\n", player->playerPos.y);
	int	offset = 0;

	if (player->mini == true)
		offset = FRM_WIDTH;
	while(!touch(ray_x - offset, ray_y, game))
	{
		if(player->mini == true)
			put_pixel(ray_x, ray_y, 0xFF0000, game);
		ray_x += cos(start_x);
		ray_y += sin(start_x);
	}
	if(player->mini == false)
	{
		double	dist = fixed_dist(player->playerPos.x, player->playerPos.y, ray_x, ray_y, game);
		double	height = (BLOCK_SIZE / dist) * (((double)FRM_WIDTH) / 2);
		int	start_y = (SCRN_HEIGHT - height) / 2;
		int	end = start_y + height;
		while(start_y < end)
		{
			put_pixel(i, start_y, 255, game);
			start_y++;
		}
	}
}

// raycasting functions
// void	draw_line(bool mini, t_game *game)
// {
// 	int	offset;
// 	double	ray_x;
// 	double	ray_y;
//
// 	offset = 0;
// 	ray_x = game->player.pos.x;
// 	ray_y = game->player.pos.y;
// 	// printf("\t%f\t%f\n", ray_x, ray_y);
// 	if (mini == true)
// 		offset = FRM_WIDTH;
// 	// printf("\t%d\t%d\n", game->player.ray.map.x, game->player.ray.map.y);
// 	while (ray_x < game->player.ray.map.x || ray_y < game->player.ray.map.y)
// 	{
// 		if (mini == true)
// 			// put_pixel(ray_x, ray_y, 0xFF0000, game);
// 			draw_filled_square(ray_x, ray_x, 10, 0xFF0000, game);
// 		ray_x += 1;//game->player.ray.dir.x;
// 		ray_y += 1;//game->player.ray.dir.y;
// 		// printf("\t%f\t%f\n", ray_x, ray_y);
// 	}
// 	// if(player->mini == false)
// 	// {
// 	// 	double	dist = fixed_dist(player->pos.x, player->pos.y, ray_x, ray_y, game);
// 	// 	double	height = (BLOCK_SIZE / dist) * (((double)FRM_WIDTH) / 2);
// 	// 	int	start_y = (SCRN_HEIGHT - height) / 2;
// 	// 	int	end = start_y + height;
// 	// 	while(start_y < end)
// 	// 	{
// 	// 		put_pixel(i, start_y, 255, game);
// 	// 		start_y++;
// 	// 	}
// 	// }
// }

int	draw_loop(t_game *game)
{
	int	i;
	double	fraction;
	double	start_x;
	int			x;
	t_ray		*ray;
	t_player 	*player;
	t_player	*mini_player;

	ray = &game->player.ray;
	player = &game->player;
	mini_player = &game->mini_player;
	fraction = 0;
	start_x = 0;
	clear_image(game);
	move_player(game->map, player);
	move_player(game->map, mini_player);
	draw_mini_map(game);
	draw_mini_player(game);
	draw_floor_or_ceiling(0, 0xdcdcdc, game);
	draw_floor_or_ceiling(1, 0x836953, game);
// 	INSERT HERE
	x = -1;
	while (++x < SCRN_WIDTH)
	{
		// if (x == 0)
		// 	printf("%i\n", x);
		player->scan_x = 2 * x / (double)SCRN_WIDTH - 1;
		// printf("\tscan_x\t%f\n", player->scan_x);
		cast_ray(player);
		// printf("\tdirX\t%f\tdirY\t%f\n", ray->dir.x, ray->dir.y);
		// printf("\t%d\t%d\n", game->player.ray.map.x, game->player.ray.map.y);
		// printf("%f\n", game->player.ray.delta_dist.y);
		dda_ray(game->map, &game->player.ray, game);
		// printf("\t%d\t%d\n", game->player.ray.map.x, game->player.ray.map.y);
		// draw_line(true, game);
		// if (ray->side)
		// 	ray->perp_dist_wall = ray->side_dist.y - ray->delta_dist.y;
		// else
		// 	ray->perp_dist_wall = ray->side_dist.x - ray->delta_dist.x;
	}
//	STOP INSERT HERE
	fraction = PI / 2 / ((double)FRM_WIDTH);// 3
	start_x = mini_player->angle - PI / 4;// 6
	i = 0;
	while(i < (FRM_WIDTH))
	{
		draw_line(mini_player, game, start_x, i);
		start_x += fraction;
		i++;
	}
	// fraction = PI / 2 / ((double)FRM_WIDTH);// 3
	// start_x = player->angle - PI / 4;// 6
	// i = 0;
	// while(i < (FRM_WIDTH))
	// {
	// 	draw_line(player, game, start_x, i);
	// 	start_x += fraction;
	// 	i++;
	// }
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return 0;
}

void	init_game(t_game *game)
{
	// game->time = 0;
	// game->prev_time = 0;
	game->map_width = 15;
	game->map_height = 15;
	game->map = init_map(game->map_width, game->map_width);
	game->player = init_player(false);
	game->mini_player = init_player(true);
	// game->player.ray = init_ray(&game->player);
	// game->ray = game->player.ray;
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, SCRN_WIDTH, SCRN_HEIGHT, "Game");
	game->img = mlx_new_image(game->mlx, SCRN_WIDTH, SCRN_HEIGHT);
	game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, &game->endian);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

int	main(void)
{
	t_game game;
	// init
	init_game(&game);
	// hooks
	mlx_hook(game.win, 2, 1L<<0, key_press, &game);
	mlx_hook(game.win, 3, 1L<<1, key_release, &game);
	mlx_hook(game.win, WIN_X_BTN, 0, close_game, &game);
	// draw loop
	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_loop(game.mlx);
	return 0;
}

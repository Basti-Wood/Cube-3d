# include "../includes/game.h"

t_player	init_player(bool mini)
{
	t_player	player;

	player.playerPos.x = BLOCK_SIZE * 5;
	player.pos.x = 5;
	if (mini == true)
	{
		player.mini = true;
		player.playerPos.x += (double)FRM_WIDTH;
	}
	player.pos.y = 10;
	player.playerPos.y = BLOCK_SIZE * 10;
	player.dir.x = 0;
	player.dir.y = -1;
	player.plane.x = 1;
	player.plane.y = 0;
	player.scan_x = 1;

	player.angle = PI * 3 / 2;

	player.move_forward = false;
	player.move_backward = false;
	player.move_port = false;
	player.move_starboard = false;
	player.move_speed = 3;

	player.turn_sinistral = false;
	player.turn_dextral = false;
	player.turn_speed = PI / 100;
	return (player);
}

int	key_press(int keycode, t_game *game)
{
	if(keycode == KEY_ESC)
		close_game(game);
	if(keycode == KEY_W)
	{
		game->player.move_forward = true;
		game->mini_player.move_forward = true;
	}
	if(keycode == KEY_S)
	{
		game->player.move_backward = true;
		game->mini_player.move_backward = true;
	}
	if(keycode == KEY_A)
	{
		game->player.move_port = true;
		game->mini_player.move_port = true;
	}
	if(keycode == KEY_D)
	{
		game->player.move_starboard = true;
		game->mini_player.move_starboard = true;
	}
	if(keycode == KEY_LEFT || keycode == KEY_J)
	{
		game->player.turn_sinistral = true;
		game->mini_player.turn_sinistral = true;
	}
	if(keycode == KEY_RIGHT || keycode == KEY_L)
	{
		game->player.turn_dextral = true;
		game->mini_player.turn_dextral = true;
	}
	return 0;
}

	int	key_release(int keycode, t_game *game)
	{
	if(keycode == KEY_W)
	{
		game->player.move_forward = false;
		game->mini_player.move_forward = false;
	}
	if(keycode == KEY_S)
	{
		game->player.move_backward = false;
		game->mini_player.move_backward = false;
	}
	if(keycode ==KEY_A)
	{
		game->player.move_port = false;
		game->mini_player.move_port = false;
	}
	if(keycode == KEY_D)
	{
		game->player.move_starboard = false;
		game->mini_player.move_starboard = false;
	}
	if(keycode == KEY_LEFT || keycode == KEY_J)
	{
		game->player.turn_sinistral = false;
		game->mini_player.turn_sinistral = false;
	}
	if(keycode == KEY_RIGHT || keycode == KEY_L)
	{
		game->player.turn_dextral = false;
		game->mini_player.turn_dextral = false;
	}
	return 0;
}

void	move_player(int **map, t_player *player)
{
	// int	speed = 3;
	// double	angle_speed = 0.03;
	double	cos_angle = cos(player->angle);
	double	sin_angle = sin(player->angle);
	double fake_angle = player->angle;

	// printf("\t%f\n", PI/104.72);
	if (player->turn_sinistral)
	{
		// printf("\tray_dirX\t%f", player->ray.dir.x);
		fake_angle = player->angle + player->turn_speed;
		// printf("\tpla_dirX\t%f", player->dir.x);
		player->dir.x = player->dir.x * cos(-PI / 100) - player->dir.y * sin(-PI / 100);
		player->plane.x = player->plane.x * cos(-PI / 100) - player->plane.y * sin(-PI / 100);
		// printf("\tcos_angle\t%f\n", cos_angle);
		player->dir.y = player->dir.x * sin(-PI / 100) + player->dir.y * cos(-PI / 100);
		player->plane.y = player->plane.x * sin(-PI / 100) + player->plane.y * cos(-PI / 100);
		// printf("\tplaneX\t%f\tplaneY\t%f\n", player->plane.x, player->plane.y);
		player->angle = atan2(player->dir.y, player->dir.x);
		// printf("\treal_angle\t%f\tfake_angle\t%f\n", player->angle, fake_angle);
		printf("\trealDirX\t%f\tfakeDirX\t%f\n", player->dir.x, cos(atan2(player->dir.y, player->dir.x)));
	}
	if (player->turn_dextral)
	{

		// printf("\tray_dirX\t%f", player->ray.dir.x);
		fake_angle = player->angle + player->turn_speed;
		// printf("\tpla_dirX\t%f", player->dir.x);
		player->dir.x = player->dir.x * cos(PI / 100) - player->dir.y * sin(PI / 100);
		player->plane.x = player->plane.x * cos(PI / 100) - player->plane.y * sin(PI / 100);
		// printf("\tcos_angle\t%f\n", cos_angle);
		player->dir.y = player->dir.x * sin(PI / 100) + player->dir.y * cos(PI / 100);
		player->plane.y = player->plane.x * sin(PI / 100) + player->plane.y * cos(PI / 100);
		// printf("\tplaneX\t%f\tplaneY\t%f\n", player->plane.x, player->plane.y);
		player->angle = atan2(player->dir.y, player->dir.x);
		// printf("\treal_angle\t%f\tfake_angle\t%f\n", player->angle, fake_angle);
		printf("\trealDirX\t%f\tfakeDirX\t%f\n", player->dir.x, cos(player->angle));
	}
	// if (player->angle > 2 * PI)
	// 	player->angle = 0;
	// if (player->angle < 0)
	// 	player->angle = 2 * PI;
	if (fake_angle > 2 * PI)
		fake_angle = 0;
	if (fake_angle < 0)
		fake_angle = 2 * PI;

	if (player->move_forward)
	{
		player->playerPos.x += cos(player->angle) * player->move_speed;
		player->playerPos.y += sin(player->angle) * player->move_speed;
	}
	if (player->move_backward)
	{
		player->playerPos.x -= cos(player->angle) * player->move_speed;
		player->playerPos.y -= sin(player->angle) * player->move_speed;
	}
	if (player->move_port)
	{
		player->playerPos.x += sin(player->angle) * player->move_speed;
		player->playerPos.y -= cos(player->angle) * player->move_speed;
	}
	if (player->move_starboard)
	{
		player->playerPos.x -= sin(player->angle) * player->move_speed;
		player->playerPos.y += cos(player->angle) * player->move_speed;
	}
}

# include "../includes/game.h"

t_player	init_player(bool mini)
{
	t_player	player;
	double		dir_len;
	double		plane_len;

	if (mini == true)
		player.mini = true;
	player.pos.x = 11;//5;
	player.pos.y = 28;//10;
	player.dir.x = 0;
	player.dir.y = -1;
	dir_len = fabs(player.dir.x + player.dir.y);
	// printf("\tdir_len = %f\n", dir_len);
	player.plane.x = 1;
	player.plane.y = 0;
	plane_len = fabs(player.plane.x + player.plane.y);
	// printf("\tplane_len = %f\n", plane_len);
	player.plane.x = 1;
	player.fov = 2 * atan(plane_len / dir_len);
	// printf("\tFOV = %f\n", player.fov);
	player.scan_x = 0;
	// double	angle = atan2(player.dir.y, player.dir.x);
	// printf("\tangle = %f\n", angle);
	player.move_forward = false;
	player.move_backward = false;
	player.move_port = false;
	player.move_starboard = false;
	player.move_speed = (double)1/30;
	player.turn_sinistral = false;
	player.turn_dextral = false;
	player.turn_speed = PI / 100;
	return (player);
}

void	turn_player(double tmp_dir_x, double tmp_plane_x, t_player *player)
{
	if (player->turn_sinistral)
	{
		// printf("\tray_dirX\t%f", player->ray.dir.x);
		// fake_angle = atan2(player->dir.y, player->dir.x) + player->turn_speed;
		// printf("\tpla_dirX\t%f", player->dir.x);
		player->dir.x = tmp_dir_x * cos(-PI / 100) - player->dir.y * sin(-PI / 100);
		player->plane.x = tmp_plane_x * cos(-PI / 100) - player->plane.y * sin(-PI / 100);
		// printf("\tcos_angle\t%f\n", cos_angle);
		player->dir.y = tmp_dir_x * sin(-PI / 100) + player->dir.y * cos(-PI / 100);
		player->plane.y = tmp_plane_x * sin(-PI / 100) + player->plane.y * cos(-PI / 100);
		// printf("\tplaneX\t%f\tplaneY\t%f\n", player->plane.x, player->plane.y);
		// player->angle = atan2(player->dir.y, player->dir.x);
		// printf("\treal_angle\t%f\tfake_angle\t%f\n", player->angle, fake_angle);
		// printf("\trealDirX\t%f\tfakeDirX\t%f\n", player->dir.x, cos(atan2(player->dir.y, player->dir.x)));
		// printf("\tp_dirX\t%f\tp_dirY\t%f\n", player->dir.x, player->dir.y);
		// printf("\tplaneX\t%f\tplaneY\t%f\n", player->plane.x, player->plane.y);
		// printf("\tFOV = %f\n", player->fov);
	}
	if (player->turn_dextral)
	{

		// printf("\tray_dirX\t%f", player->ray.dir.x);
		// fake_angle = atan2(player->dir.y, player->dir.x) + player->turn_speed;
		// printf("\tpla_dirX\t%f", player->dir.x);
		player->dir.x = tmp_dir_x * cos(PI / 100) - player->dir.y * sin(PI / 100);
		player->plane.x = tmp_plane_x * cos(PI / 100) - player->plane.y * sin(PI / 100);
		// printf("\tcos_angle\t%f\n", cos_angle);
		player->dir.y = tmp_dir_x * sin(PI / 100) + player->dir.y * cos(PI / 100);
		player->plane.y = tmp_plane_x * sin(PI / 100) + player->plane.y * cos(PI / 100);
		// printf("\tplaneX\t%f\tplaneY\t%f\n", player->plane.x, player->plane.y);
		// player->angle = atan2(player->dir.y, player->dir.x);
		// printf("\treal_angle\t%f\tfake_angle\t%f\n", player->angle, fake_angle);
		// printf("\trealDirX\t%f\tfakeDirX\t%f\n", player->dir.x, cos(player->angle));
		// printf("\tFOV = %f\n", player->fov);
	}
}

void	move_longitudal(int **map, t_player *player)
{
	double	tmp_x;
	double	tmp_y;
	// double	player_angle;

	tmp_x = player->pos.x;
	tmp_y = player->pos.y;
	// player_angle = atan2(player->dir.y, player->dir.x);
	if (player->move_forward)
	{
		tmp_x += cos(atan2(player->dir.y, player->dir.x)) * player->move_speed/* * 16*/;
		tmp_y += sin(atan2(player->dir.y, player->dir.x)) * player->move_speed/* * 16*/;
		if (!collision((int)tmp_x, (int)tmp_y, map))
		{
			// player->pos.x += cos(atan2(player->dir.y, player->dir.x)) * player->move_speed;
			// player->pos.y += sin(atan2(player->dir.y, player->dir.x)) * player->move_speed;
			player->pos.x = tmp_x;
			player->pos.y = tmp_y;
		}
	}
	if (player->move_backward)
	{
		tmp_x -= cos(atan2(player->dir.y, player->dir.x)) * player->move_speed/* * 16*/;
		tmp_y -= sin(atan2(player->dir.y, player->dir.x)) * player->move_speed/* * 16*/;
		if (!collision((int)tmp_x, (int)tmp_y, map))
		{
			// player->pos.x -= cos(atan2(player->dir.y, player->dir.x)) * player->move_speed;
			// player->pos.y -= sin(atan2(player->dir.y, player->dir.x)) * player->move_speed;
			player->pos.x = tmp_x;
			player->pos.y = tmp_y;
		}
	}
}

void	move_lateral(int **map, t_player *player)
{
	double	tmp_x;
	double	tmp_y;
	// double	player_angle;

	tmp_x = player->pos.x;
	tmp_y = player->pos.y;
	// player_angle = atan2(player->dir.y, player->dir.x);
	if (player->move_port)
	{
		tmp_x += sin(atan2(player->dir.y, player->dir.x)) * player->move_speed/* * 16*/;
		tmp_y -= cos(atan2(player->dir.y, player->dir.x)) * player->move_speed/* * 16*/;
		if (!collision((int)tmp_x, (int)tmp_y, map))
		{
			// player->pos.x += sin(atan2(player->dir.y, player->dir.x)) * player->move_speed;
			// player->pos.y -= cos(atan2(player->dir.y, player->dir.x)) * player->move_speed;
			player->pos.x = tmp_x;
			player->pos.y = tmp_y;
		}
	}
	if (player->move_starboard)
	{
		tmp_x -= sin(atan2(player->dir.y, player->dir.x)) * player->move_speed/* * 16*/;
		tmp_y += cos(atan2(player->dir.y, player->dir.x)) * player->move_speed/* * 16*/;
		if (!collision((int)tmp_x, (int)tmp_y, map))
		{
			// player->pos.x -= sin(atan2(player->dir.y, player->dir.x)) * player->move_speed;
			// player->pos.y += cos(atan2(player->dir.y, player->dir.x)) * player->move_speed;
			player->pos.x = tmp_x;
			player->pos.y = tmp_y;
		}
	}
}

void	move_player(int **map, t_player *player)
{
	// int		speed = 3;
	// double	angle_speed = 0.03;
	// double	cos_angle = cos(player->angle);
	// double	sin_angle = sin(player->angle);
	// double fake_angle = atan2(player->dir.y, player->dir.x);//player->angle;
	// double	tmp_pos_x;
	// double	tmp_pos_y;

	if (player->turn_sinistral || player->turn_dextral)
		turn_player(player->dir.x, player->plane.x, player);
	// if (player->angle > 2 * PI)
	// 	player->angle = 0;
	// if (player->angle < 0)
	// 	player->angle = 2 * PI;
	// if (fake_angle > 2 * PI)
	//	fake_angle = 0;
	// if (fake_angle < 0)
	//	fake_angle = 2 * PI;
	if (player->move_forward || player->move_backward)
		move_longitudal(map, player);
	if (player->move_port || player->move_starboard)
		move_lateral(map, player);
}

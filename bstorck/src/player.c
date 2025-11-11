# include "../includes/game.h"

void init_player(t_player *player)
{
    // player->x = ((float)WIDTH - 960) / 2;
    // player->y = (float)HEIGHT / 2;
    player->posX = BLOCK * 12;
	if (player->mini == true)
		player->posX += 960;
    player->posY = BLOCK * 6;
    // player->angle = PI / 2;
	player->angle = PI * 3 / 4;

    player->move_forward = false;
    player->move_backward = false;
    player->move_port = false;
    player->move_starboard = false;

    player->rotate_sinistral = false;
    player->rotate_dextral = false;
}

int key_press(int keycode, t_game *game)
{
	if(keycode == 65307)
		close_game(game);
    if(keycode == W)
	{
		game->player.move_forward = true;
		game->mini_player.move_forward = true;
	}
    if(keycode == S)
	{
		game->player.move_backward = true;
		game->mini_player.move_backward = true;
	}
    if(keycode == A)
	{
		game->player.move_port = true;
		game->mini_player.move_port = true;
	}
    if(keycode == D)
	{
		game->player.move_starboard = true;
		game->mini_player.move_starboard = true;
	}
    if(keycode == LEFT || keycode == J)
	{
		game->player.rotate_sinistral = true;
		game->mini_player.rotate_sinistral = true;
	}
    if(keycode == RIGHT || keycode == L)
	{
		game->player.rotate_dextral = true;
		game->mini_player.rotate_dextral = true;
	}
    return 0;
}

int key_release(int keycode, t_game *game)
{
    if(keycode == W)
	{
		game->player.move_forward = false;
		game->mini_player.move_forward = false;
	}
    if(keycode == S)
	{
		game->player.move_backward = false;
		game->mini_player.move_backward = false;
	}
    if(keycode == A)
	{
		game->player.move_port = false;
		game->mini_player.move_port = false;
	}
    if(keycode == D)
	{
		game->player.move_starboard = false;
		game->mini_player.move_starboard = false;
	}
    if(keycode == LEFT || keycode == J)
	{
		game->player.rotate_sinistral = false;
		game->mini_player.rotate_sinistral = false;
	}
    if(keycode == RIGHT || keycode == L)
	{
		game->player.rotate_dextral = false;
		game->mini_player.rotate_dextral = false;
	}
    return 0;
}

void move_player(t_player *player)
{
    int speed = 3;
    float angle_speed = 0.03;
    float cos_angle = cos(player->angle);
    float sin_angle = sin(player->angle);

    if (player->rotate_sinistral)
        player->angle -= angle_speed;
    if (player->rotate_dextral)
        player->angle += angle_speed;
    if (player->angle > 2 * PI)
        player->angle = 0;
    if (player->angle < 0)
        player->angle = 2 * PI;

    if (player->move_forward)
    {
        player->posX += cos_angle * speed;
        player->posY += sin_angle * speed;
    }
    if (player->move_backward)
    {
        player->posX -= cos_angle * speed;
        player->posY -= sin_angle * speed;
    }
    if (player->move_port)
    {
        player->posX += sin_angle * speed;
        player->posY -= cos_angle * speed;
    }
    if (player->move_starboard)
    {
        player->posX -= sin_angle * speed;
        player->posY += cos_angle * speed;
    }
}

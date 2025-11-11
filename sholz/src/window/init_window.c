#include "../../includes/cub3d.h"

/*
** Initialize the game structure with default values
*/
void	init_game(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->img.img_ptr = NULL;
	game->img.addr = NULL;
	game->keys.w = 0;
	game->keys.a = 0;
	game->keys.s = 0;
	game->keys.d = 0;
	game->keys.left = 0;
	game->keys.right = 0;
}

int	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		printf("Error: Failed to initialize MLX\n");
		return (0);
	}
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, WIN_TITLE);
	if (!game->win)
	{
		printf("Error: Failed to create window\n");
		return (0);
	}
	return (1);
}

int	init_image(t_game *game)
{
	game->img.img_ptr = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game->img.img_ptr)
	{
		printf("Error: Failed to create image\n");
		return (0);
	}
	game->img.addr = mlx_get_data_addr(game->img.img_ptr,
			&game->img.bits_per_pixel,
			&game->img.line_length,
			&game->img.endian);
	if (!game->img.addr)
	{
		printf("Error: Failed to get image address\n");
		return (0);
	}
	game->img.width = WIN_WIDTH;
	game->img.height = WIN_HEIGHT;
	return (1);
}

void	init_player(t_game *game)
{
	game->player.pos.x = game->map.player.x + 0.5;
	game->player.pos.y = game->map.player.y + 0.5;
	game->player.move_speed = MOVE_SPEED;
	game->player.rot_speed = ROT_SPEED;
	if (game->map.player_dir == 'N')
	{
		game->player.dir.x = 0;
		game->player.dir.y = -1;
		game->player.plane.x = 0.66;
		game->player.plane.y = 0;
	}
	else if (game->map.player_dir == 'S')
	{
		game->player.dir.x = 0;
		game->player.dir.y = 1;
		game->player.plane.x = -0.66;
		game->player.plane.y = 0;
	}
	else if (game->map.player_dir == 'E')
	{
		game->player.dir.x = 1;
		game->player.dir.y = 0;
		game->player.plane.x = 0;
		game->player.plane.y = 0.66;
	}
	else if (game->map.player_dir == 'W')
	{
		game->player.dir.x = -1;
		game->player.dir.y = 0;
		game->player.plane.x = 0;
		game->player.plane.y = -0.66;
	}
}

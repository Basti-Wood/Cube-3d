#include "../includes/game.h"

// our own put_pixel

void put_pixel(int x, int y, int color, t_game *game)
{
    if(x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
        return;
    
    int index = y * game->size_line + x * game->bpp / 8;
    game->data[index] = color & 0xFF;
    game->data[index + 1] = (color >> 8) & 0xFF;
    game->data[index + 2] = (color >> 16) & 0xFF;
}

// our own clear_image
void clear_image(t_game *game)
{
    for(int y = 0; y < HEIGHT; y++)
        for(int x = 0; x < WIDTH; x++)
            put_pixel(x, y, 0, game);
}

// utils functions
void draw_empty_square(int x, int y, int size, int color, t_game *game)
{
    for(int i = 0; i < size; i++)
        put_pixel(x + i, y, color, game);
    for(int i = 0; i < size; i++)
        put_pixel(x, y + i, color, game);
    for(int i = 0; i < size; i++)
        put_pixel(x + size, y + i, color, game);
    for(int i = 0; i < size; i++)
        put_pixel(x + i, y + size, color, game);
}

void draw_filled_square(int x, int y, int size, int color, t_game *game)
{
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j <size; j++)
		{
			put_pixel(x + i, y + j, color, game);
		}
	}
}

void draw_map(t_game *game)
{
    char **map = game->map;
    int color = 0x0000FF;
    for(int y = 0; map[y]; y++)
        for(int x = 0; map[y][x]; x++)
            if(map[y][x] == '1')
                draw_filled_square(960 + x * BLOCK, y * BLOCK, BLOCK, color, game);
}

// distance calculation functions
float distance(float x, float y){
    return sqrt(x * x + y * y);
}

float fixed_dist(float x1, float y1, float x2, float y2, t_game *game)
{
    float delta_x = x2 - x1;
    float delta_y = y2 - y1;
    float angle = atan2(delta_y, delta_x) - game->player.angle;
    float fix_dist = distance(delta_x, delta_y) * cos(angle);
    return fix_dist;
}

// touch function 
bool touch(float px, float py, t_game *game)
{
    int x = px / BLOCK;
	// printf("%i\n", x);
    int y = py / BLOCK;
    if(game->map[y][x] == '1')
        return true;
    return false;
}

// initialisation functions
char **get_map(void)
{
    char **map = malloc(sizeof(char *) * 13);
    map[0] = "111111111111111";
    map[1] = "100000000000001";
    map[2] = "100000000000001";
    map[3] = "100000100000001";
    map[4] = "100000000000001";
    map[5] = "100000010000001";
    map[6] = "100001000000001";
    map[7] = "100000100010001";
	map[8] = "100000010000001";
    map[9] = "100000000000001";
    map[10] = "100000000000001";
	map[11] = "111111111111111";
    map[12] = NULL;
    return (map);
}

void init_game(t_game *game)
{
	game->player.mini = false;
	init_player(&game->player);
	game->mini_player.mini = true;
	init_player(&game->mini_player);
	game->map = get_map();
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Game");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, &game->endian);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

// raycasting functions
void draw_line(t_player *player, t_game *game, float start_x, int i)
{
    float cos_angle = cos(start_x);
    float sin_angle = sin(start_x);
    float ray_x = player->posX;
    float ray_y = player->posY;
	int offset = 0;
	// float ray_x = BLOCK*12;
    // float ray_y = BLOCK*6;

	if (player->mini == true)
		offset = 960;
    while(!touch(ray_x - offset, ray_y, game))
    {
        if(player->mini == true)
            put_pixel(ray_x, ray_y, 0xFF0000, game);
        ray_x += cos_angle;
        ray_y += sin_angle;
    }
    if(player->mini == false)
    {
        float dist = fixed_dist(player->posX, player->posY, ray_x, ray_y, game);
        float height = (BLOCK / dist) * ((float)(WIDTH - 960) / 2);
        int start_y = (HEIGHT - height) / 2;
        int end = start_y + height;
        while(start_y < end)
        {
            put_pixel(i, start_y, 255, game);
            start_y++;
        }
    }
}

int draw_loop(t_game *game)
{
	t_player *player = &game->player;
	t_player *mini_player = &game->mini_player;
	move_player(player);
	move_player(mini_player);
	clear_image(game);
	draw_filled_square(mini_player->posX, mini_player->posY, 5, 0x00FF00, game);
	draw_filled_square(mini_player->posX - 5, mini_player->posY, 5, 0x00FF00, game);
	draw_filled_square(mini_player->posX, mini_player->posY - 5, 5, 0x00FF00, game);
	draw_filled_square(mini_player->posX - 5, mini_player->posY - 5, 5, 0x00FF00, game);
	draw_map(game);
	float mini_fraction = PI / 2 / (WIDTH - 960);// 3
	float mini_start_x = mini_player->angle - PI / 4;// 6
	int mini_i = 0;
	while(mini_i < (WIDTH - 960))
	{
		draw_line(mini_player, game, mini_start_x, mini_i);
		mini_start_x += mini_fraction;
		mini_i++;
	}
	float fraction = PI / 2 / (WIDTH - 960);// 3
	float start_x = player->angle - PI / 4;// 6
	int i = 0;
	while(i < (WIDTH - 960))
	{
		draw_line(player, game, start_x, i);
		start_x += fraction;
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return 0;
}

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
	free(game->map);
	exit(0);
	return (0);
}

int main(void)
{
    t_game game;
    // init
    init_game(&game);
    // hooks
    mlx_hook(game.win, 2, 1L<<0, key_press, &game);
    mlx_hook(game.win, 3, 1L<<1, key_release, &game);
    // mlx_hook(game.win, 2, 1L<<0, key_press, &game.mini_player);
    // mlx_hook(game.win, 3, 1L<<1, key_release, &game.mini_player);
	mlx_hook(game.win, 17, 0, close_game, &game);
    // draw loop
    mlx_loop_hook(game.mlx, draw_loop, &game);

    mlx_loop(game.mlx);
	// close_game(&game);
	// free(game.map);
    return 0;
}

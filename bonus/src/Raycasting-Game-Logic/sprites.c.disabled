#include "../../includes/game.h"

void	init_sprites(t_game *game)
{
	int			i;
	int			j;
	t_sprite	*sprite;

	sprite = game->map.sprite;

	i = -1;
	while (++i < MAX_SPRITES)
	{
		game->map.render_order[i] = i;
		sprite[i].pos.x = 0;
		sprite[i].pos.y = 0;
		sprite[i].dist = 0;
		sprite[i].impermeable = true;
		sprite[i].animated = false;
		sprite[i].last_shift = 0;
		j = -1;
		while (++j < MAX_CELLS)
			sprite[i].tex_id[j] = 0;
	}

	sprite[0].pos.x = 2.5;
	sprite[0].pos.y = 21.5;
	sprite[0].tex_id[0] = BARREL;

	sprite[1].pos.x = 2.5;
	sprite[1].pos.y = 21.5;
	sprite[1].tex_id[0] = LIGHT;

	sprite[2].pos.x = 3.5;
	sprite[2].pos.y = 19.5;
	sprite[2].animated = true;
	sprite[2].tex_id[0] = TREE_0;
	sprite[2].tex_id[1] = TREE_1;
	sprite[2].tex_id[2] = TREE_2;
	sprite[2].tex_id[3] = TREE_3;
	sprite[2].tex_id[4] = TREE_4;

	sprite[3].pos.x = 5.5;
	sprite[3].pos.y = 28.5;
	sprite[3].tex_id[0] = BARREL;

	sprite[4].pos.x = 8.5;
	sprite[4].pos.y = 19.5;
	sprite[4].tex_id[0] = BARREL;

	sprite[5].pos.x = 7.5;
	sprite[5].pos.y = 28.5;
	sprite[5].tex_id[0] = PILLAR;

	sprite[6].pos.x = 7.5;
	sprite[6].pos.y = 19.5;
	sprite[6].tex_id[0] = PILLAR;

	sprite[7].pos.x = 6.5;
	sprite[7].pos.y = 13.3;
	sprite[7].tex_id[0] = LIGHT;

	sprite[8].pos.x = 6.5;
	sprite[8].pos.y = 13.3;
	sprite[8].tex_id[0] = BARREL;

	sprite[9].pos.x = 4.5;
	sprite[9].pos.y = 23.5;
	sprite[9].tex_id[0] = LIGHT;

	sprite[10].pos.x = 6.5;
	sprite[10].pos.y = 21.5;
	sprite[10].tex_id[0] = LIGHT;

	sprite[11].pos.x = 6.5;
	sprite[11].pos.y = 23.5;
	sprite[11].tex_id[0] = LIGHT;

	sprite[12].pos.x = 6.5;
	sprite[12].pos.y = 25.5;
	sprite[12].tex_id[0] = LIGHT;

	sprite[13].pos.x = 8.5;
	sprite[13].pos.y = 23.5;
	sprite[13].tex_id[0] = LIGHT;

	sprite[14].pos.x = 2.5;
	sprite[14].pos.y = 18.5;
	sprite[14].tex_id[0] = LIGHT;

	game->map.num_sprites = 15;

	i = -1;
	while (++i < game->map.num_sprites)
	{
		// game->map.render_order[i] = i;
		if (sprite[i].tex_id[0] == LIGHT)
			sprite[i].impermeable = false;
		if (sprite[i].animated == true)
			sprite[i].last_shift = get_current_time();
	}
	// printf("\t%i -> %i\n", sprite[0].tex_id[0], sprite[1].tex_id[0]);
}

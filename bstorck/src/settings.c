#include "../includes/game.h"

void	make_slower(t_game *game)
{
	// game->hero.plane.x -= 0.01;
	// game->mini_hero.plane.x -= 0.01;
	// printf("\tFOV = %i%%\n", (int)(fabs(game->hero.plane.x/game->hero.dir.y)*100));
	game->hero.move_speed /= 1.1;
	game->hero.turn_speed /= 1.04;
	game->mini_hero.move_speed /= 1.1;
	game->mini_hero.turn_speed /= 1.04;
	// printf("\thero\t");
	printf("\t\tmove_speed = %f\t", game->hero.move_speed);
	printf("\tturn_speed = %f\n", game->hero.turn_speed);
	// printf("\tmini_hero");
	// printf("\tmove_speed = %f\t", game->mini_hero.move_speed);
	// printf("\tturn_speed = %f\n", game->mini_hero.turn_speed);
}

void	make_faster(t_game *game)
{
	// game->hero.plane.x += 0.01;
	// game->mini_hero.plane.x += 0.01;
	// printf("\tFOV = %i%%\n", (int)(fabs(game->hero.plane.x/game->hero.dir.y)*100));
	game->hero.move_speed *= 1.1;
	game->hero.turn_speed *= 1.04;
	game->mini_hero.move_speed *= 1.1;
	game->mini_hero.turn_speed *= 1.04;
	// printf("\thero\t");
	printf("\t\tmove_speed = %f\t", game->hero.move_speed);
	printf("\tturn_speed = %f\n", game->hero.turn_speed);
	// printf("\tmini_hero");
	// printf("\tmove_speed = %f\t", game->mini_hero.move_speed);
	// printf("\tturn_speed = %f\n", game->mini_hero.turn_speed);

}

#include "../includes/game.h"

void	go_forward(t_hero *h, int **map)
{
	double		speed;
	t_vector	new_pos;

	speed = h->move_speed;
	if (h->axes_of_travel >= 2)
		speed /= sqrt(2);
	h->probe = h->pos;
	h->probe.x = h->pos.x + cos(atan2(h->dir.y, h->dir.x)) * speed;
	if (sonar(h, map) == 0)
		new_pos.x = h->probe.x;
	else
		new_pos.x = h->pos.x - cos(atan2(h->dir.y, h->dir.x)) / 100000;
	h->probe = h->pos;
	h->probe.y = h->pos.y + sin(atan2(h->dir.y, h->dir.x)) * speed;
	if (sonar(h, map) == 0)
		new_pos.y = h->probe.y;
	else
		new_pos.y = h->pos.y - sin(atan2(h->dir.y, h->dir.x)) / 100000;
	h->pos = new_pos;
}

void	go_backward(t_hero *h, int **map)
{
	double		speed;
	t_vector	new_pos;

	speed = h->move_speed;
	if (h->axes_of_travel >= 2)
		speed /= sqrt(2);
	h->probe = h->pos;
	h->probe.x = h->pos.x - cos(atan2(h->dir.y, h->dir.x)) * speed;
	if (sonar(h, map) == 0)
		new_pos.x = h->probe.x;
	else
		new_pos.x = h->pos.x + cos(atan2(h->dir.y, h->dir.x)) / 100000;
	h->probe = h->pos;
	h->probe.y = h->pos.y - sin(atan2(h->dir.y, h->dir.x)) * speed;
	if (sonar(h, map) == 0)
		new_pos.y = h->probe.y;
	else
		new_pos.y = h->pos.y + sin(atan2(h->dir.y, h->dir.x)) / 100000;
	h->pos = new_pos;
}

void	go_port(t_hero *h, int **map)
{
	double		speed;
	t_vector	new_pos;

	speed = h->move_speed;
	if (h->axes_of_travel >= 2)
		speed /= sqrt(2);
	h->probe = h->pos;
	h->probe.x = h->pos.x + sin(atan2(h->dir.y, h->dir.x)) * speed;
	if (sonar(h, map) == 0)
		new_pos.x = h->probe.x;
	else
		new_pos.x = h->pos.x - sin(atan2(h->dir.y, h->dir.x)) / 100000;
	h->probe = h->pos;
	h->probe.y = h->pos.y - cos(atan2(h->dir.y, h->dir.x)) * speed;
	if (sonar(h, map) == 0)
		new_pos.y = h->probe.y;
	else
		new_pos.y = h->pos.y + cos(atan2(h->dir.y, h->dir.x)) / 100000;
	h->pos = new_pos;
}

void	go_starboard(t_hero *h, int **map)
{
	double		speed;
	t_vector	new_pos;

	speed = h->move_speed;
	if (h->axes_of_travel >= 2)
		speed /= sqrt(2);
	h->probe = h->pos;
	h->probe.x = h->pos.x - sin(atan2(h->dir.y, h->dir.x)) * speed;
	if (sonar(h, map) == 0)
		new_pos.x = h->probe.x;
	else
		new_pos.x = h->pos.x + sin(atan2(h->dir.y, h->dir.x)) / 100000;
	h->probe = h->pos;
	h->probe.y = h->pos.y + cos(atan2(h->dir.y, h->dir.x)) * speed;
	if (sonar(h, map) == 0)
		new_pos.y = h->probe.y;
	else
		new_pos.y = h->pos.y - cos(atan2(h->dir.y, h->dir.x)) / 100000;
	h->pos = new_pos;
}

void	turn_hero(double dir_x, double plane_x, t_hero *h)
{
	double	speed;

	speed = h->turn_speed;
	if (h->turn_sinistral)
	{
		h->dir.x = dir_x * cos(-speed) - h->dir.y * sin(-speed);
		h->plane.x = plane_x * cos(-speed) - h->plane.y * sin(-speed);
		h->dir.y = dir_x * sin(-speed) + h->dir.y * cos(-speed);
		h->plane.y = plane_x * sin(-speed) + h->plane.y * cos(-speed);
		// printf("\tdir_x=%f\t\tdir_y=%f\n", h->dir.x, h->dir.y);
		// printf("\tplane_x=%f\tplane_y=%f\n\n", h->plane.x, h->plane.y);
	}
	else if (h->turn_dextral)
	{
		h->dir.x = dir_x * cos(speed) - h->dir.y * sin(speed);
		h->plane.x = plane_x * cos(speed) - h->plane.y * sin(speed);
		h->dir.y = dir_x * sin(speed) + h->dir.y * cos(speed);
		h->plane.y = plane_x * sin(speed) + h->plane.y * cos(speed);
		// printf("\tdir_x=%f\t\tdir_y=%f\n", h->dir.x, h->dir.y);
		// printf("\tplane_x=%f\tplane_y=%f\n\n", h->plane.x, h->plane.y);
	}
}

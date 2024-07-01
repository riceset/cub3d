#include "cub3d.h"

double	init_angle(t_player *player)
{
	if (player->player_status == PLAYER_EAST)
		return (0);
	else if (player->player_status == PLAYER_NORTH)
		return (M_PI * 1 / 2);
	else if (player->player_status == PLAYER_WEST)
		return (M_PI);
	else
		return (M_PI * 3 / 2);
}

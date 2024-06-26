/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_angle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@tokyo.42.school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 10:57:41 by hhagiwar          #+#    #+#             */
/*   Updated: 2024/07/02 10:57:46 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

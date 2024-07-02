/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_direction_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@tokyo.42.school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 10:59:25 by hhagiwar          #+#    #+#             */
/*   Updated: 2024/07/02 11:06:52 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_direction_map(int data)
{
	if (data == PLAYER_EAST || data == PLAYER_WEST || data == PLAYER_SOUTH
		|| data == PLAYER_NORTH)
		return (TRUE);
	return (FALSE);
}

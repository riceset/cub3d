/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riceset <tkomeno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:56:06 by riceset           #+#    #+#             */
/*   Updated: 2024/07/04 18:56:17 by riceset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	calculate_initial_position(float player_position, int tile_size)
{
	return (player_position + tile_size * 3 / 8 + tile_size / 7);
}

float	calculate_step(double angle, int is_x_step)
{
	float	result;

	if (is_x_step)
		result = cos(angle) / 45;
	else
		result = -sin(angle) / 45;
	return (result);
}

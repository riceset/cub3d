/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riceset <tkomeno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 13:55:01 by riceset           #+#    #+#             */
/*   Updated: 2024/07/02 16:23:59 by riceset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_grid(t_mlx *img, t_int_point p, int color, int size)
{
	int	i;

	i = 0;
	while (i <= size)
	{
		my_mlx_pixel_put(img, p.x * size + i, p.y * size, color);
		my_mlx_pixel_put(img, p.x * size, p.y * size + i, color);
		my_mlx_pixel_put(img, (p.x + 1) * size - 1, p.y * size + i, color);
		my_mlx_pixel_put(img, p.x * size + i, (p.y + 1) * size - 1, color);
		i++;
	}
}

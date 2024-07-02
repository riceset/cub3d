/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@tokyo.42.school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:11:10 by hhagiwar          #+#    #+#             */
/*   Updated: 2024/07/02 11:11:11 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_grid(t_mlx *img, int x, int y, int size)
{
	int	i;
	int	color;

	i = 0;
	color = GREY;
	while (i <= size)
	{
		my_mlx_pixel_put(img, x * size + i, y * size, color);
		my_mlx_pixel_put(img, x * size, y * size + i, color);
		my_mlx_pixel_put(img, (x + 1) * size - 1, y * size + i, color);
		my_mlx_pixel_put(img, x * size + i, (y + 1) * size - 1, color);
		i++;
	}
}

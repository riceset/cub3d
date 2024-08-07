/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riceset <tkomeno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:59:07 by riceset           #+#    #+#             */
/*   Updated: 2024/07/04 19:18:34 by riceset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_ceiling(t_mlx *img, int ray, int bottom_pixel, int color)
{
	int	pixel_y;

	pixel_y = 0;
	while (pixel_y < bottom_pixel)
	{
		my_mlx_pixel_put(img, ray, pixel_y, color);
		pixel_y++;
	}
}

void	draw_floor(t_mlx *img, int ray, int top_pixel, int color)
{
	int	pixel_y;

	pixel_y = top_pixel;
	while (pixel_y < HEIGHT)
	{
		my_mlx_pixel_put(img, ray, pixel_y, color);
		pixel_y++;
	}
}

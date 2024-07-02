/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riceset <tkomeno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:38:44 by riceset           #+#    #+#             */
/*   Updated: 2024/07/02 16:42:13 by riceset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_line(t_mlx *img, t_int_point start, t_int_point end, int color)
{
	t_float_point	step;
	int				steps;
	t_float_point	p;
	int				i;

	step.x = end.x - start.x;
	step.y = end.y - start.y;
	steps = (int)fmaxf(fabsf(step.x), fabsf(step.y));
	step.x /= steps;
	step.y /= steps;
	p.x = start.x;
	p.y = start.y;
	i = 0;
	while (i <= steps)
	{
		my_mlx_pixel_put(img, round(p.x), round(p.y), color);
		p.x += step.x;
		p.y += step.y;
		i++;
	}
}

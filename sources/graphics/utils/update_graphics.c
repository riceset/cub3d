/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_graphics.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riceset <tkomeno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:15:54 by riceset           #+#    #+#             */
/*   Updated: 2024/07/02 17:15:59 by riceset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_graphics(t_data *data)
{
	mlx_destroy_image(data->img.mlx, data->img.img);
	data->img.img = mlx_new_image(data->img.mlx, WIDTH, HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel,
			&data->img.line_length, &data->img.endian);
	render_wall(data, &data->img);
	draw_minimap(data, data->img);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture_color.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riceset <tkomeno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:16:28 by riceset           #+#    #+#             */
/*   Updated: 2024/07/02 17:16:29 by riceset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_texture_color(t_texture *texture, int x, int y)
{
	int				offset;
	unsigned char	blue;
	unsigned char	green;
	unsigned char	red;

	offset = (y * texture->width + x) * 3;
	blue = texture->data[offset];
	green = texture->data[offset + 1];
	red = texture->data[offset + 2];
	return ((red << 16) | (green << 8) | blue);
}

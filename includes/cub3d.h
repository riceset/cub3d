/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkomeno <tkomeno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 18:39:40 by tkomeno           #+#    #+#             */
/*   Updated: 2024/03/01 18:39:41 by tkomeno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include "../libraries/mlx/mlx.h"
#include "../libraries/get_next_line/get_next_line.h"
#include "../libraries/ft_printf/ft_printf.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

# define KEY_ESC 53

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

#endif

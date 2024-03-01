/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkomeno <tkomeno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 18:39:48 by tkomeno           #+#    #+#             */
/*   Updated: 2024/03/01 18:39:50 by tkomeno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	void	*mlx;

	(void)argc;
	(void)argv;
	mlx = mlx_init();
	(void)mlx;
	printf("Hello World!\n");
	return (EXIT_SUCCESS);
}

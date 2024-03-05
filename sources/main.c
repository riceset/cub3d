/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiro <hiro@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 18:39:48 by tkomeno           #+#    #+#             */
/*   Updated: 2024/03/05 14:08:57 by hiro             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void my_mlx_pixel_put(t_mlx *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int close_window(void *param)
{
	(void)param;
	exit(EXIT_SUCCESS);
}

int key_press(int keycode)
{
	if (keycode == KEY_ESC)
	{
		ft_printf("ESC key is pressed\n");
		exit(EXIT_SUCCESS);
	}
	return (0);
}

void start_game()
{
	t_mlx img;
	void *mlx;
	void *mlx_win;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								 &img.endian);
	my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_key_hook(mlx_win, key_press, NULL);
	mlx_hook(mlx_win, 17, 0, close_window, NULL);
	mlx_loop(mlx);
}

int main(int argc, char **argv)
{
	t_data *data;

	(void)data;
	if (argc == 2)
	{
		data = init_data(argv);
		start_game();
	}
	exit(EXIT_SUCCESS);
}

__attribute__((destructor)) static void destructor()
{
	system("leaks -q cub3d");
}

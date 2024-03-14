/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiro <hiro@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 18:39:48 by tkomeno           #+#    #+#             */
/*   Updated: 2024/03/14 18:17:54 by hiro             ###   ########.fr       */
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

void draw_line(t_mlx *img, int start_x, int start_y, int end_x, int end_y, int color)
{
	float x_step;
	float y_step;
	int steps;
	float x;
	float y;
	int i;
	
	x_step = end_x - start_x;
	y_step = end_y - start_y;
	steps = (int)fmaxf(fabsf(x_step), fabsf(y_step));
	x_step /= steps;
	y_step /= steps;
	x = start_x;
	y = start_y;
	i = 0;
	while (i <= steps)
	{
		my_mlx_pixel_put(img, round(x), round(y), color);
		x += x_step;
		y += y_step;
		i++;
	}
}

void draw_minimap(t_data *data, t_mlx img)
{
	int x;
	int y;
	int i;
	int j;
	int start_x;
	int start_y;
	int end_x;
	int end_y;
	int color;

	y = 0;
	while (y < data->h_map)
	{
		x = 0;
		while (x < data->w_map)
		{
			if (data->map[y][x] == WALL || data->map[y][x] == FORBIDDEN_SPACE)
			{
				if (data->map[y][x] == WALL)
					color = WHITE;
				else if (data->map[y][x] == FORBIDDEN_SPACE)
					color = RED;
				start_x = x * TILE_SIZE;
				start_y = y * TILE_SIZE;
				end_x = start_x + TILE_SIZE;
				end_y = start_y + TILE_SIZE;
				i = start_y;
				while (i < end_y)
				{
					j = start_x;
					while (j < end_x)
					{
						my_mlx_pixel_put(&img, j, i, color);
						j++;
					}
					i++;
				}
			}
			i = 0;
			while (i <= TILE_SIZE)
			{
				my_mlx_pixel_put(&img, x * TILE_SIZE + i, y * TILE_SIZE, GREY);
				my_mlx_pixel_put(&img, x * TILE_SIZE, y * TILE_SIZE + i, GREY);
				my_mlx_pixel_put(&img, (x + 1) * TILE_SIZE - 1, y * TILE_SIZE + i, GREY);
				my_mlx_pixel_put(&img, x * TILE_SIZE + i, (y + 1) * TILE_SIZE - 1, GREY);
				i++;
			}
			if (data->map[y][x] >= PLAYER_NORTH && data->map[y][x] <= PLAYER_WEST)
			{
				start_x = x * TILE_SIZE + TILE_SIZE * 3 / 8;
				start_y = y * TILE_SIZE + TILE_SIZE * 3 / 8;
				end_x = start_x + TILE_SIZE * 2 / 7;
				end_y = start_y + TILE_SIZE * 2 / 7;
				i = start_y;
				while (i < end_y)
				{
					j = start_x;
					while (j < end_x)
					{
						my_mlx_pixel_put(&img, j, i, YELLOW);
						j++;
					}
					i++;
				}
				start_x = x * TILE_SIZE + TILE_SIZE / 2;
				start_y = y * TILE_SIZE + TILE_SIZE / 2;
				end_x = start_x + (int)(20 * cos(data->player->angle));
				end_y = start_y - (int)(20 * sin(data->player->angle));
				draw_line(&img, start_x, start_y, end_x, end_y, GREEN);
				end_x = start_x + (int)(20 * cos(data->player->angle - data->player->fov_rd / 2));
				end_y = start_y - (int)(20 * sin(data->player->angle - data->player->fov_rd / 2));				
				draw_line(&img, start_x, start_y, end_x, end_y, GREEN);
				end_x = start_x + (int)(20 * cos(data->player->angle + data->player->fov_rd / 2));
				end_y = start_y - (int)(20 * sin(data->player->angle + data->player->fov_rd / 2));				
				draw_line(&img, start_x, start_y, end_x, end_y, GREEN);
			}
			x++;
		}
		y++;
	}
}

void start_game(t_data *data)
{
	t_mlx img;
	void *mlx;
	void *mlx_win;
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, WIDTH, HEIGHT, "Cub3D");
	img.img = mlx_new_image(mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	draw_minimap(data, img);
	(void)data;
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
		if (extension_check(argv[1]) == ERROR)
			ft_exit("File extension must be .cub", NULL);
		data = init_data(argv);
		start_game(data);
	}
	else
		ft_exit("Error: Invalid command line arguments. \nUsage: ./cub3D <path_to_map_file.cub>", NULL);
	exit(EXIT_SUCCESS);
}

__attribute__((destructor)) static void destructor()
{
	printf("\n--------- destructor ---------\n\n");
	system("leaks -q cub3d");
	printf("\n--------- End of destructor ---------\n\n");
}

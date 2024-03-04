/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkomeno <tkomeno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 18:39:48 by tkomeno           #+#    #+#             */
/*   Updated: 2024/03/01 19:25:47 by tkomeno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int get_height(char *filename)
{
	char *line;
	int fd;
	int height;

	fd = open(filename, O_RDONLY, 0);
	if (fd == -1)
	{
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}
	height = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break;
		if (height == INT_MAX)
			exit(EXIT_FAILURE);
		height++;
		free(line);
	}
	close(fd);
	return height;
}

t_data *init_data(char **argv)
{
	char *line;
	int fd;
	t_data *data;

	fd = open(argv[1], O_RDONLY);
	data = (t_data *)malloc(sizeof(t_data));
	data->h_map = get_height(argv[1]);
	printf("map_height: %d\n", data->h_map);
	if (fd == -1)
		perror("Error opening file");
	else
	{
		while ((line = get_next_line(fd)) != NULL)
		{
			printf("%s", line);
			free(line);
		}
		close(fd);
	}
	return data;
}

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

	if (argc == 2)
	{
		data = init_data(argv);
		start_game();
		(void)data;
	}
	exit(EXIT_SUCCESS);
}

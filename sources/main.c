/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiro <hiro@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 18:39:48 by tkomeno           #+#    #+#             */
/*   Updated: 2024/03/12 17:52:17 by hiro             ###   ########.fr       */
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
	
	
	y = 0;
    while (y < data->h_map)
    {
        x = 0;
        while (x < data->w_map)
        {
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
                start_x = x * TILE_SIZE + TILE_SIZE / 3;
                start_y = y * TILE_SIZE + TILE_SIZE / 3;
                end_x = start_x + TILE_SIZE / 3;
                end_y = start_y + TILE_SIZE / 3;
				i = start_y;
				while(i < end_y)
				{
					j = start_x;
					while(j < end_x)
					{
                        my_mlx_pixel_put(&img, j, i, YELLOW);
						j++;
					}
					i++;
				}
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

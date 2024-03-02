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

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	close_window(void *param)
{
	(void)param;
	exit(EXIT_SUCCESS);
}

int	key_press(int keycode)
{
	if (keycode == KEY_ESC)
	{
		ft_printf("ESC key is pressed\n");
		exit(EXIT_SUCCESS);
	}
	return (0);
}

void test_gnl(char **argv)
{
    char *line;
	int fd;
    fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
    } else {
        while ((line = get_next_line(fd)) != NULL) {
            printf("%s", line);
            free(line);
        }
        close(fd);
    }
}

int main(int argc, char **argv)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

    if (argc == 2)
		test_gnl(argv);
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

	exit(EXIT_SUCCESS);
}

#include "cub3d.h"

int close_window(void *param)
{
	(void)param;
	exit(EXIT_SUCCESS);
}

int key_press(int keycode, t_data *data)
{
    const float move_step = 5.0;

    if (keycode == KEY_ESC) {
        ft_printf("ESC key is pressed\n");
        exit(EXIT_SUCCESS);
    } else if (keycode == KEY_A) {
        ft_printf("A key is pressed\n");
        data->player->angle += ROTATION_SPEED;
    } else if (keycode == KEY_D) {
        ft_printf("D key is pressed\n");
        data->player->angle -= ROTATION_SPEED;
    } else if (keycode == KEY_S) {
        data->player->plyr_x -= cos(data->player->angle) * move_step;
        data->player->plyr_y += sin(data->player->angle) * move_step;
        ft_printf("S key is pressed\n");
    } else if (keycode == KEY_W) {
        data->player->plyr_x += cos(data->player->angle) * move_step;
        data->player->plyr_y -= sin(data->player->angle) * move_step;
    }

    if (keycode != KEY_ESC) {
        update_graphics(data);
    }
    return 0;
}


void start_game(t_data *data)
{
	data->img.mlx = mlx_init();
	data->img.mlx_win = mlx_new_window(data->img.mlx, WIDTH, HEIGHT, "Cub3D");
	data->img.img = mlx_new_image(data->img.mlx, WIDTH, HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel, &data->img.line_length, &data->img.endian);
	draw_minimap(data, data->img);
	printf("\n--------- Key action ---------\n\n");
    mlx_hook(data->img.mlx_win, ON_KEYDOWN, KEY_PRESS_MASK, key_press, data);
	printf("\n--------- End of Key action ---------\n\n");

	mlx_loop(data->img.mlx);
}

t_data *init_data(char **argv)
{
	t_data *data;

	print_file(argv[1]);
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		ft_exit("Memory allocation failed", data);
	data->h_map = get_height(argv[1], data);
	data->w_map = get_width(argv[1], data);
	if (data->h_map < 9 || data->w_map < 7)
		ft_exit("Map Error", data);
	data->map = init_map(argv[1], data->h_map, data->w_map, data);
	print_map(data->map, data->w_map);
	data->player = init_player(data);
	print_map(data->map, data->w_map);
	if(validate_map(data))
		ft_exit("Map Error", data);
	return (data);
}
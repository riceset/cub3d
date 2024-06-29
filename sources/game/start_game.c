#include "cub3d.h"

void start_game(t_data *data)
{
    data->img.mlx = mlx_init();
    data->img.mlx_win = mlx_new_window(data->img.mlx, WIDTH, HEIGHT, "Cub3D");
    data->img.img = mlx_new_image(data->img.mlx, WIDTH, HEIGHT);
    data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel, &data->img.line_length, &data->img.endian);
    render_wall(data, &data->img);
    draw_minimap(data, data->img);
    mlx_put_image_to_window(data->img.mlx, data->img.mlx_win, data->img.img, 0, 0);
    mlx_hook(data->img.mlx_win, ON_KEYDOWN, KEY_PRESS_MASK, key_press, data);
    mlx_hook(data->img.mlx_win, ON_DESTROY, NO_EVENT_MASK, close_window, data);
    mlx_loop(data->img.mlx);

    // Clean up
    mlx_destroy_image(data->img.mlx, data->img.img);
    mlx_destroy_window(data->img.mlx, data->img.mlx_win);
}
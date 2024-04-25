#include "cub3d.h"

void draw_player(t_mlx *img, t_data *data)
{
    int start_x = data->player->plyr_x + TILE_SIZE * 3 / 8;
    int start_y = data->player->plyr_y + TILE_SIZE * 3 / 8;
    int end_x = start_x + TILE_SIZE * 2 / 7;
    int end_y = start_y + TILE_SIZE * 2 / 7;
    int i = start_y;
    int j;

    while (i < end_y)
    {
        j = start_x;
        while (j < end_x)
        {
            my_mlx_pixel_put(img, j, i, YELLOW);
            j++;
        }
        i++;
    }
    double start_angle = data->player->angle - data->player->fov_rd / 2;
    double angle_step = data->player->fov_rd / 20;
    while (start_angle < data->player->angle + data->player->fov_rd / 2)
    {
        draw_ray_minimap(img, data, start_angle, GREEN);
        start_angle += angle_step;
    }
}


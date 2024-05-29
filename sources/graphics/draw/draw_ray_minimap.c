#include "cub3d.h"

void draw_ray_minimap(t_mlx *img, t_data *data, double angle, int color)
{
    float ray_length = cast_ray(data, angle);
    int end_x = data->player->plyr_x + TILE_SIZE * 3 / 8 + TILE_SIZE / 7 + (int)(ray_length * cos(angle));
    int end_y = data->player->plyr_y + TILE_SIZE * 3 / 8 + TILE_SIZE / 7 - (int)(ray_length * sin(angle));
    draw_line(img, data->player->plyr_x + TILE_SIZE * 3 / 8 + TILE_SIZE / 7, data->player->plyr_y + TILE_SIZE * 3 / 8 + TILE_SIZE / 7, end_x, end_y, color);
}


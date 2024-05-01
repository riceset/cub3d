#include "cub3d.h"

// 新しい関数をプロトタイプ宣言
static float cast_ray_step(float x, float y, float angle, t_data *data);
static int check_collision(float x, float y, float angle, t_data *data); // 引数を 4 つに修正

float cast_ray(t_data *data, double angle)
{
    float x = data->player->plyr_x + TILE_SIZE * 3 / 8 + TILE_SIZE / 7;
    float y = data->player->plyr_y + TILE_SIZE * 3 / 8 + TILE_SIZE / 7;

    return cast_ray_step(x, y, angle, data);
}

static float cast_ray_step(float x, float y, float angle, t_data *data)
{
    float x_step = cos(angle) / 45;
    float y_step = -sin(angle) / 45;

    while (x >= 0 && x < data->w_map * TILE_SIZE && y >= 0 && y < data->h_map * TILE_SIZE &&
           data->map[(int)(y / TILE_SIZE)][(int)(x / TILE_SIZE)] != WALL)
    {
        x += x_step;
        y += y_step;
        if (check_collision(x, y, angle, data))
            break;
        if (x < 0 || x >= data->w_map * TILE_SIZE || y < 0 || y >= data->h_map * TILE_SIZE)
            break;
    }
    return hypot(x - data->player->plyr_x - TILE_SIZE * 3 / 8 - TILE_SIZE / 7, y - data->player->plyr_y - TILE_SIZE * 3 / 8 - TILE_SIZE / 7);
}

static int check_collision(float x, float y, float angle, t_data *data)
{
    int previous_x = (int)((x - cos(angle) / 45) / TILE_SIZE);
    int previous_y = (int)((y + sin(angle) / 45) / TILE_SIZE);
    if ((previous_x < 0 || previous_y < 0 || previous_x >= data->w_map || previous_y >= data->h_map) ||
        ((int)(x / TILE_SIZE) < 0 || (int)(y / TILE_SIZE) < 0 || (int)(x / TILE_SIZE) >= data->w_map || (int)(y / TILE_SIZE) >= data->h_map))
        return 1;
    return abs((previous_x - (int)(x / TILE_SIZE))) + abs((previous_y - (int)(y / TILE_SIZE))) == 2 &&
           ((data->map[previous_y][(int)(x / TILE_SIZE)] == WALL) || (data->map[(int)(y / TILE_SIZE)][previous_x] == WALL));
}
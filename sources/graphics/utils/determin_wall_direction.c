#include "cub3d.h"

float calculate_initial_position(float player_position, int tile_size) {
    return player_position + tile_size * 3 / 8 + tile_size / 7;
}

float calculate_step(double angle, int is_x_step) {
    return (is_x_step ? cos(angle) : -sin(angle)) / 45;
}

int trace_ray(t_data *data, float x, float y, float x_step, float y_step) {
    int previous_x = (int)(x / TILE_SIZE);
    int previous_y = (int)(y / TILE_SIZE);
    
    while (data->map[(int)(y / TILE_SIZE)][(int)(x / TILE_SIZE)] != WALL) {
        x += x_step;
        y += y_step;
        if (x < 0 || x >= data->w_map * TILE_SIZE || y < 0 || y >= data->h_map * TILE_SIZE)
            break;
        int current_x = (int)(x / TILE_SIZE);
        int current_y = (int)(y / TILE_SIZE);
        if (current_y >= 0 && current_y < data->h_map && current_x >= 0 && current_x < data->w_map) {
            if (data->map[current_y][current_x] == WALL) {
                if (current_x != previous_x)
                    return (x_step > 0) ? 2 : 1;
                else if (current_y != previous_y)
                    return (y_step > 0) ? 4 : 3;
            }
        }
        previous_x = current_x;
        previous_y = current_y;
    }
    return 0;
}

int determine_wall_direction(t_data *data, double ray_angle) {
    float x = calculate_initial_position(data->player->plyr_x, TILE_SIZE);
    float y = calculate_initial_position(data->player->plyr_y, TILE_SIZE);
    float x_step = calculate_step(ray_angle, 1);
    float y_step = calculate_step(ray_angle, 0);
    
    return trace_ray(data, x, y, x_step, y_step);
}

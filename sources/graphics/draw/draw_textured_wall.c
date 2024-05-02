#include "cub3d.h"

static void calculate_texture_coordinates(t_data *data, int ray, double *hitX, double *hitY, double *wallX, int *texX, t_texture *texture);
static void draw_textured_pixels(t_mlx *img, int ray, int top_pixel, int bottom_pixel, t_texture *texture, int wallHeight, int texX);

void draw_textured_wall(t_mlx *img, int ray, int top_pixel, int bottom_pixel, t_texture *texture, t_data *data)
{
    int wallHeight;
    int texX;
    double hitX;
    double hitY;
    double wallX;

    wallHeight = bottom_pixel - top_pixel;
    calculate_texture_coordinates(data, ray, &hitX, &hitY, &wallX, &texX, texture);
    draw_textured_pixels(img, ray, top_pixel, bottom_pixel, texture, wallHeight, texX);
}

static void calculate_texture_coordinates(t_data *data, int ray, double *hitX, double *hitY, double *wallX, int *texX, t_texture *texture)
{
    double ray_angle = data->player->angle + (data->player->fov_rd / 2) - (ray * data->player->fov_rd / WIDTH);
    float distance = cast_ray(data, ray_angle);
    double corrected_distance = distance * cos(ray_angle - data->player->angle);
    int direction = determine_wall_direction(data, ray_angle, distance);

    if (direction == 1)
    { // 東側の壁
        *hitY = data->player->plyr_y - corrected_distance * sin(ray_angle);
        *wallX = fmod(*hitY, TILE_SIZE);
        *texX = (int)((TILE_SIZE / 2 - *wallX) * texture->width / TILE_SIZE) % texture->width;
    }
    else if (direction == 2)
    { // 西側の壁
        *hitY = data->player->plyr_y - corrected_distance * sin(ray_angle);
        *wallX = fmod(*hitY, TILE_SIZE);
        *texX = (int)((TILE_SIZE / 2 + *wallX) * texture->width / TILE_SIZE) % texture->width;
    }
    else if (direction == 3)
    { // 南側の壁
        *hitX = data->player->plyr_x + corrected_distance * cos(ray_angle);
        *wallX = fmod(*hitX, TILE_SIZE);
        *texX = (int)((TILE_SIZE / 2 + *wallX) * texture->width / TILE_SIZE) % texture->width;
    }
    else if (direction == 4)
    { // 北側の壁
        *hitX = data->player->plyr_x + corrected_distance * cos(ray_angle);
        *wallX = fmod(*hitX, TILE_SIZE);
        *texX = (int)((TILE_SIZE / 2 - *wallX) * texture->width / TILE_SIZE) % texture->width;
    }
}

static void draw_textured_pixels(t_mlx *img, int ray, int top_pixel, int bottom_pixel, t_texture *texture, int wallHeight, int texX)
{
    for (int pixel_y = top_pixel; pixel_y < bottom_pixel; pixel_y++)
    {
        int texY = ((pixel_y - top_pixel) * texture->height) / wallHeight;
        int color = get_texture_color(texture, texX, texY);
        my_mlx_pixel_put(img, ray, pixel_y, color);
    }
}

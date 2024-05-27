#include "cub3d.h"

static int calculate_texture_coordinates(t_data *data, int ray, double *hitX, double *hitY, double *wallX, int *texX, t_texture *texture);
static void draw_textured_pixels(t_mlx *img, int ray, int top_pixel, int bottom_pixel, int wall_top_pixel, int wall_bottom_pixel, t_texture *texture, int wallHeight, int texX);

void draw_textured_wall(t_mlx *img, int ray, int top_pixel, int bottom_pixel, int wall_top_pixel, int wall_bottom_pixel, t_texture *texture, t_data *data)
{
    int wallHeight;
    int texX;
    double hitX;
    double hitY;
    double wallX;
    int direction;

    wallHeight = wall_bottom_pixel - wall_top_pixel;
    direction = calculate_texture_coordinates(data, ray, &hitX, &hitY, &wallX, &texX, texture);
    draw_textured_pixels(img, ray, direction, top_pixel, bottom_pixel, wall_top_pixel, texture, wallHeight, texX);
}

static void calculate_hits_and_texture(t_data *data, double ray_angle, double distance, int direction, double *hitX, double *hitY, double *wallX, int *texX, t_texture *texture)
{
    if (direction == EAST)
    { // 東側の壁
        *hitY = data->player->plyr_y - distance * sin(ray_angle);
        *wallX = fmod(*hitY, TILE_SIZE);
        *texX = -(int)((TILE_SIZE / 2 + *wallX) * texture->width / TILE_SIZE) % texture->width;
    }
    else if (direction == WEST)
    { // 西側の壁
        *hitY = data->player->plyr_y - distance * sin(ray_angle);
        *wallX = fmod(*hitY, TILE_SIZE);
        *texX = (int)((TILE_SIZE / 2 + *wallX) * texture->width / TILE_SIZE) % texture->width;
    }
    else if (direction == SOUTH)
    { // 南側の壁
        *hitX = data->player->plyr_x + distance * cos(ray_angle);
        *wallX = fmod(*hitX, TILE_SIZE);
        *texX = (int)((TILE_SIZE / 2 + *wallX) * texture->width / TILE_SIZE) % texture->width;
    }
    else if (direction == NORTH)
    { // 北側の壁
        *hitX = data->player->plyr_x + distance * cos(ray_angle);
        *wallX = fmod(*hitX, TILE_SIZE);
        *texX = -(int)((TILE_SIZE / 2 + *wallX) * texture->width / TILE_SIZE) % texture->width;
    }
}

static int calculate_texture_coordinates(t_data *data, int ray, double *hitX, double *hitY, double *wallX, int *texX, t_texture *texture)
{
    double ray_angle;
    int direction;

    ray_angle = data->player->angle + (data->player->fov_rd / 2) - (ray * data->player->fov_rd / WIDTH);
    direction = determine_wall_direction(data, ray_angle);
    calculate_hits_and_texture(data, ray_angle, cast_ray(data, ray_angle), direction, hitX, hitY, wallX, texX, texture);
    return direction;
}

static void draw_textured_pixels(t_mlx *img, int ray, int direction, int top_pixel, int bottom_pixel, int wall_top_pixel, t_texture *texture, int wallHeight, int texX)
{
    (void)direction; // texture
    for (int pixel_y = top_pixel; pixel_y < bottom_pixel; pixel_y++)
    {
        int texY = ((pixel_y - wall_top_pixel) * texture->height) / wallHeight;
        if (texY < 0) texY = 0;
        if (texY >= texture->height) texY = texture->height - 1;
        int color = get_texture_color(texture, texX, texY);
        my_mlx_pixel_put(img, ray, pixel_y, color);
    }
}

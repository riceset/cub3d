#include "cub3d.h"

void render_wall(t_data *data, t_mlx *img);
static float calculate_ray_distance(t_data *data, int ray);
static int calculate_wall_height(float distance, t_data *data);
static void draw_ceiling_floor(t_data *data, t_mlx *img, int ray, int top_pixel, int bottom_pixel);

void render_wall(t_data *data, t_mlx *img)
{
    int ray = 0;
    while (ray < WIDTH)
    {
        float distance = calculate_ray_distance(data, ray);
        int wall_height = calculate_wall_height(distance, data);
        int top_pixel = (HEIGHT / 2) - (wall_height / 2);
        int bottom_pixel = (HEIGHT / 2) + (wall_height / 2);

        t_texture *texture = load_texture_from_bmp("test.bmp");
        if (texture == NULL)
            ft_exit("Failed to load texture", data);
        int draw_start = top_pixel < 0 ? 0 : top_pixel;
        int draw_end = bottom_pixel > HEIGHT ? HEIGHT : bottom_pixel;
        draw_textured_wall(img, ray, draw_start, draw_end, top_pixel, bottom_pixel, texture, data);
        draw_ceiling_floor(data, img, ray, draw_start, draw_end);
        ray++;
    }
}

static float calculate_ray_distance(t_data *data, int ray)
{
    double ray_angle = data->player->angle + (data->player->fov_rd / 2) - (ray * data->player->fov_rd / WIDTH);
    return cast_ray(data, ray_angle);
}

static int calculate_wall_height(float distance, t_data *data)
{
    return (int)((TILE_SIZE / distance) * (WIDTH / (2 * tan(data->player->fov_rd / 2))));
}

static void draw_ceiling_floor(t_data *data, t_mlx *img, int ray, int top_pixel, int bottom_pixel)
{
    draw_wall(img, ray, 0, top_pixel, data->colors.ceiling_color);
    draw_wall(img, ray, bottom_pixel, HEIGHT, data->colors.floor_color);
}


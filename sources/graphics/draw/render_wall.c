#include "cub3d.h"

void render_wall(t_data *data, t_mlx *img);
static float calculate_ray_distance(t_data *data, int ray);
static void draw_ceiling_floor(t_data *data, t_mlx *img, int ray, t_wall_data *wall_data);
static void fill_wall_data(t_wall_data *wall_data, float distance, t_data *data);
static void load_textures(t_data *data, t_texture *textures[4]);

static void free_textures(t_texture *textures[4])
{
    int i;

    i = 0;
    while (i < 4)
    {
        if (textures[i] != NULL)
        {
            free(textures[i]->data);
            free(textures[i]);
        }
        i++;
    }
}

void render_wall(t_data *data, t_mlx *img)
{
    int ray = 0;
    float distance;
    t_wall_data wall_data;
    t_texture_data tex_data;

    load_textures(data, tex_data.texture);
    while (ray < WIDTH)
    {
        distance = calculate_ray_distance(data, ray);
        fill_wall_data(&wall_data, distance, data);

        draw_textured_wall(img, ray, &wall_data, &tex_data, data);
        draw_ceiling_floor(data, img, ray, &wall_data);

        ray++;
    }
    free_textures(tex_data.texture);
}

static void load_textures(t_data *data, t_texture *textures[4])
{
    int i = 0;

    while (i < 4)
    {
        textures[i] = load_texture_from_bmp(extract_filename(data->texture[i]));
        if (textures[i] == NULL)
            ft_exit("Failed to load texture", data);
        i++;
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

static void fill_wall_data(t_wall_data *wall_data, float distance, t_data *data)
{
    wall_data->distance = distance;
    wall_data->wall_height = calculate_wall_height(distance, data);
    wall_data->top_pixel = (HEIGHT / 2) - (wall_data->wall_height / 2);
    wall_data->bottom_pixel = (HEIGHT / 2) + (wall_data->wall_height / 2);
}

static void draw_ceiling_floor(t_data *data, t_mlx *img, int ray, t_wall_data *wall_data)
{
    draw_wall(img, ray, 0, wall_data->top_pixel, data->colors.ceiling_color);
    draw_wall(img, ray, wall_data->bottom_pixel, HEIGHT, data->colors.floor_color);
}

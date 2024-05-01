#include "cub3d.h"

int get_texture_color(t_texture *texture, int x, int y) {
    int offset = (y * texture->width + x) * 3;
    unsigned char blue = texture->data[offset];
    unsigned char green = texture->data[offset + 1];
    unsigned char red = texture->data[offset + 2];

    return (red << 16) | (green << 8) | blue;
}

int determine_wall_direction(t_data *data, double ray_angle, float distance) {
    float x = data->player->plyr_x + TILE_SIZE * 3 / 8 + TILE_SIZE / 7;
    float y = data->player->plyr_y + TILE_SIZE * 3 / 8 + TILE_SIZE / 7;
    float x_step = cos(ray_angle) / 45;
    float y_step = -sin(ray_angle) / 45;
    int previous_x = (int)(x / TILE_SIZE);
    int previous_y = (int)(y / TILE_SIZE);
    (void)distance;

    while (data->map[(int)(y / TILE_SIZE)][(int)(x / TILE_SIZE)] != WALL) {
        x += x_step;
        y += y_step;
        if (x < 0 || x >= data->w_map * TILE_SIZE || y < 0 || y >= data->h_map * TILE_SIZE) {
            break; // Ensure we stop if out of map bounds
        }

        int current_x = (int)(x / TILE_SIZE);
        int current_y = (int)(y / TILE_SIZE);

        if (current_x != previous_x || current_y != previous_y) {
            if (data->map[current_y][current_x] == WALL) {
                if (current_x != previous_x) {
                    // Hit was triggered by a change in x coordinate
                    return (x_step > 0) ? 2 : 1; // East or West facing wall
                } else if (current_y != previous_y) {
                    // Hit was triggered by a change in y coordinate
                    return (y_step > 0) ? 4 : 3; // South or North facing wall
                }
            }
        }

        previous_x = current_x;
        previous_y = current_y;
    }
    
    return 0;
}

void draw_textured_wall(t_mlx *img, int ray, int top_pixel, int bottom_pixel, t_texture *texture, t_data *data) {
    int wallHeight = bottom_pixel - top_pixel;
    double ray_angle = data->player->angle + (data->player->fov_rd / 2) - (ray * data->player->fov_rd / WIDTH);
    float distance = cast_ray(data, ray_angle);
    double corrected_distance = distance * cos(ray_angle - data->player->angle);

    int direction = determine_wall_direction(data, ray_angle, distance);

    double hitX, hitY, wallX;
    int texX;
    if (direction == 1) { // 東側の壁
        hitY = data->player->plyr_y - corrected_distance * sin(ray_angle);
        wallX = fmod(hitY, TILE_SIZE);
        texX = (int)((TILE_SIZE / 2 - wallX) * texture->width / TILE_SIZE) % texture->width;
    } else if (direction == 2) { // 西側の壁
        hitY = data->player->plyr_y - corrected_distance * sin(ray_angle);
        wallX = fmod(hitY, TILE_SIZE);
        texX = (int)((TILE_SIZE / 2 + wallX) * texture->width / TILE_SIZE) % texture->width;
    } else if (direction == 3) { // 南側の壁
        hitX = data->player->plyr_x + corrected_distance * cos(ray_angle);
        wallX = fmod(hitX, TILE_SIZE);
        texX = (int)((TILE_SIZE / 2 + wallX) * texture->width / TILE_SIZE) % texture->width;
    } else if (direction == 4) { // 北側の壁
        hitX = data->player->plyr_x + corrected_distance * cos(ray_angle);
        wallX = fmod(hitX, TILE_SIZE);
        texX = (int)((TILE_SIZE / 2 - wallX) * texture->width / TILE_SIZE) % texture->width;
    }

    for (int pixel_y = top_pixel; pixel_y < bottom_pixel; pixel_y++) {
        int texY = ((pixel_y - top_pixel) * texture->height) / wallHeight;
        int color = get_texture_color(texture, texX, texY);
        my_mlx_pixel_put(img, ray, pixel_y, color);
    }
}



void render_wall(t_data *data, t_mlx *img) {
    int ray;
    double ray_angle;
    float distance;
    double corrected_distance;
    int wall_height = 0;
    int top_pixel;
    int bottom_pixel;
	t_texture *texture = load_texture_from_bmp("test.bmp");

    ray = 0;
    while (ray < WIDTH) {
        ray_angle = data->player->angle + (data->player->fov_rd / 2) - (ray * data->player->fov_rd / WIDTH);
       distance = cast_ray(data, ray_angle);
        corrected_distance = distance * cos(ray_angle - data->player->angle);

        // 壁の高さを計算
        wall_height = (int)((TILE_SIZE / corrected_distance) * (WIDTH / (2 * tan(data->player->fov_rd / 2))));
        top_pixel = (HEIGHT / 2) - (wall_height / 2);
        bottom_pixel = (HEIGHT / 2) + (wall_height / 2);

        // 画面範囲外を超えて描画しないように調整
        if (top_pixel < 0) top_pixel = 0;
        if (bottom_pixel > HEIGHT) bottom_pixel = HEIGHT;


		draw_textured_wall(img, ray, top_pixel, bottom_pixel, texture, data);

        draw_wall(img, ray, 0, top_pixel, data->colors.ceiling_color);
        draw_wall(img, ray, bottom_pixel, HEIGHT, data->colors.floor_color);

        ray++;
    }
}

float cast_ray(t_data *data, double angle)
{
    float x = data->player->plyr_x + TILE_SIZE * 3 / 8 + TILE_SIZE / 7;
    float y = data->player->plyr_y + TILE_SIZE * 3 / 8 + TILE_SIZE / 7;
    float x_step = cos(angle) / 45;
    float y_step = -sin(angle) / 45;
    int previous_x = (int)(x / TILE_SIZE);
    int previous_y = (int)(y / TILE_SIZE);

    while (data->map[(int)(y / TILE_SIZE)][(int)(x / TILE_SIZE)] != WALL)
    {
        x += x_step;
        y += y_step;
        if (abs((previous_x - (int)(x / TILE_SIZE))) + abs((previous_y - (int)(y / TILE_SIZE))) == 2)
            if (data->map[(int)(previous_y)][(int)(x / TILE_SIZE)] == WALL || data->map[(int)(y / TILE_SIZE)][previous_x] == WALL)
                break;
        previous_x = (int)(x / TILE_SIZE);
        previous_y = (int)(y / TILE_SIZE);
        if (x < 0 || x >= data->w_map * TILE_SIZE || y < 0 || y >= data->h_map * TILE_SIZE)
        {
            break;
        }
    }
    // printf("x:%f, y:%f\n", (x / TILE_SIZE), (y / TILE_SIZE));
    return hypot(x - data->player->plyr_x - TILE_SIZE * 3 / 8 - TILE_SIZE / 7, y - data->player->plyr_y - TILE_SIZE * 3 / 8 - TILE_SIZE / 7);
}

void update_graphics(t_data *data)
{
    mlx_destroy_image(data->img.mlx, data->img.img);
    data->img.img = mlx_new_image(data->img.mlx, WIDTH, HEIGHT);
    data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel, &data->img.line_length, &data->img.endian);
    render_wall(data, &data->img);
    draw_minimap(data, data->img);
}

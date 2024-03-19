
#include "cub3d.h"
#include "mlx.h"

float cast_ray(t_data *data, double angle);

void my_mlx_pixel_put(t_mlx *img, int x, int y, int color)
{
    char *dst;

    dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

void draw_wall(t_mlx *img, int ray, int top_pixel, int bottom_pixel)
{
    int pixel_y = top_pixel;
    int color = CORNSILK;

    while (pixel_y < bottom_pixel)
    {
        my_mlx_pixel_put(img, ray, pixel_y, color);
        pixel_y++;
    }
}

void render_wall(t_data *data, t_mlx img)
{
    int ray;
    double ray_angle;
    float distance;
    double corrected_distance;
    int wall_height;
    int top_pixel;
    int bottom_pixel;

    ray = 0;
    while (ray < WIDTH )
    {
        ray_angle = data->player->angle - (data->player->fov_rd / 2) + (ray * data->player->fov_rd / WIDTH);
        distance = cast_ray(data, ray_angle);
        corrected_distance = distance * cos(ray_angle - data->player->angle); // Fisheye effect correction
        wall_height = (int)((TILE_SIZE / corrected_distance) * (WIDTH / (2 * tan(data->player->fov_rd / 2))));

        top_pixel = (HEIGHT / 2) - (wall_height / 2);
        if (top_pixel < 0)
            top_pixel = 0;

        bottom_pixel = (HEIGHT / 2) + (wall_height / 2);
        if (bottom_pixel > HEIGHT)
            bottom_pixel = HEIGHT;
        draw_wall(&img, ray, top_pixel, bottom_pixel);
        ray++;
    }
}

void draw_minimap(t_data *data, t_mlx img)
{
    int x = 0;
    int y = 0;
    int color;

    while (y < data->h_map)
    {
        x = 0;
        while (x < data->w_map)
        {
            if (data->map[y][x] == WALL || data->map[y][x] == FORBIDDEN_SPACE)
            {
                if (data->map[y][x] == WALL)
                    color = WHITE;
                else if (data->map[y][x] == FORBIDDEN_SPACE)
                    color = RED;
                draw_square(&img, x * TILE_SIZE, y * TILE_SIZE, color, TILE_SIZE);
            }
            draw_grid(&img, x, y, GREY, TILE_SIZE);
            if (data->map[y][x] >= PLAYER_NORTH && data->map[y][x] <= PLAYER_WEST)
                draw_player(&img, data);
            x++;
        }
        y++;
    }
    mlx_put_image_to_window(data->img.mlx, data->img.mlx_win, data->img.img, 0, 0);
}

float cast_ray(t_data *data, double angle)
{
    float x = data->player->plyr_x + TILE_SIZE * 3 / 8 + TILE_SIZE / 7;
    float y = data->player->plyr_y + TILE_SIZE * 3 / 8 + TILE_SIZE / 7;
    float x_step = cos(angle) / 2;
    float y_step = -sin(angle) / 2;
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
    return hypot(x - data->player->plyr_x - TILE_SIZE * 3 / 8 - TILE_SIZE / 7, y - data->player->plyr_y - TILE_SIZE * 3 / 8 - TILE_SIZE / 7);
}

void draw_ray_minimap(t_mlx *img, t_data *data, double angle, int color)
{
    float ray_length = cast_ray(data, angle);
    printf("ray: %f\n", ray_length);
    int end_x = data->player->plyr_x + TILE_SIZE * 3 / 8 + TILE_SIZE / 7 + (int)(ray_length * cos(angle));
    int end_y = data->player->plyr_y + TILE_SIZE * 3 / 8 + TILE_SIZE / 7 - (int)(ray_length * sin(angle));
    draw_line(img, data->player->plyr_x + TILE_SIZE * 3 / 8 + TILE_SIZE / 7, data->player->plyr_y + TILE_SIZE * 3 / 8 + TILE_SIZE / 7, end_x, end_y, color);
}

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

void draw_line(t_mlx *img, int start_x, int start_y, int end_x, int end_y, int color)
{
    float x_step;
    float y_step;
    int steps;
    float x;
    float y;
    int i;

    x_step = end_x - start_x;
    y_step = end_y - start_y;
    steps = (int)fmaxf(fabsf(x_step), fabsf(y_step));
    x_step /= steps;
    y_step /= steps;
    x = start_x;
    y = start_y;
    i = 0;
    while (i <= steps)
    {
        my_mlx_pixel_put(img, round(x), round(y), color);
        x += x_step;
        y += y_step;
        i++;
    }
}

void draw_square(t_mlx *img, int start_x, int start_y, int color, int size)
{
    int end_x;
    int end_y;
    int i;
    int j;

    end_x = start_x + size;
    end_y = start_y + size;
    i = start_y;
    while (i < end_y)
    {
        j = start_x;
        while (j < end_x)
        {
            my_mlx_pixel_put(img, j, i, color);
            j++;
        }
        i++;
    }
}

void draw_grid(t_mlx *img, int x, int y, int color, int size)
{
    int i = 0;
    while (i <= size)
    {
        my_mlx_pixel_put(img, x * size + i, y * size, color);
        my_mlx_pixel_put(img, x * size, y * size + i, color);
        my_mlx_pixel_put(img, (x + 1) * size - 1, y * size + i, color);
        my_mlx_pixel_put(img, x * size + i, (y + 1) * size - 1, color);
        i++;
    }
}

void update_graphics(t_data *data)
{
    mlx_destroy_image(data->img.mlx, data->img.img);
    data->img.img = mlx_new_image(data->img.mlx, WIDTH, HEIGHT);
    data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel, &data->img.line_length, &data->img.endian);
    render_wall(data, data->img);
    draw_minimap(data, data->img);
}

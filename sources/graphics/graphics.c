#include "cub3d.h"
#include "mlx.h"

float cast_ray(t_data *data, double angle);

void my_mlx_pixel_put(t_mlx *img, int x, int y, int color)
{
    char *dst;

    dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

void skip_bmp_header(int fd)
{
	unsigned char header[54];

	if (read(fd, header, 54) != 54) {
		perror("Failed to read header");
		close(fd);
		exit(1);
	}
}

t_texture *load_texture_from_bmp(const char *file_path) {
    int fd = open(file_path, O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
        exit(1);
    }

    skip_bmp_header(fd);

    t_texture *texture = malloc(sizeof(t_texture));
    if (!texture) {
        perror("Failed to allocate texture");
        close(fd);
        exit(1);
    }

    texture->width = 128;
    texture->height = 128;
    int dataSize = texture->width * texture->height * 3;
    texture->data = malloc(dataSize);
    if (!texture->data) {
        perror("Failed to allocate texture data");
        free(texture);
        close(fd);
        exit(1);
    }

    if (read(fd, texture->data, dataSize) != dataSize) {
        perror("Error reading texture data");
        free(texture->data);
        free(texture);
        close(fd);
        exit(1);
    }

    close(fd);
    return texture;
}

int get_texture_color(t_texture *texture, int x, int y) {
    int offset = (y * texture->width + x) * 3;
    unsigned char blue = texture->data[offset];
    unsigned char green = texture->data[offset + 1];
    unsigned char red = texture->data[offset + 2];

    return (red << 16) | (green << 8) | blue;
}

void draw_wall(t_mlx *img, int ray, int top_pixel, int bottom_pixel, int color)
{
    int pixel_y = top_pixel;

    while (pixel_y < bottom_pixel)
    {
        my_mlx_pixel_put(img, ray, pixel_y, color);
        pixel_y++;
    }
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
        texX = (int)(wallX / 2 * texture->width / TILE_SIZE) % texture->width;
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
    printf("x:%f, y:%f\n", (x / TILE_SIZE), (y / TILE_SIZE));
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
    render_wall(data, &data->img);
    draw_minimap(data, data->img);
}

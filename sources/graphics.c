
#include "cub3d.h"
#include "mlx.h"

void my_mlx_pixel_put(t_mlx *img, int x, int y, int color) {
    char    *dst;

    dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void draw_minimap(t_data *data, t_mlx img) {
    int x = 0;
    int y = 0;
    int color;

    while (y < data->h_map) {
        x = 0;
        while (x < data->w_map) {
            if (data->map[y][x] == WALL || data->map[y][x] == FORBIDDEN_SPACE){
                if (data->map[y][x] == WALL)
                    color = WHITE;
                else if (data->map[y][x] == FORBIDDEN_SPACE)
                    color = RED;
                draw_square(&img, x * TILE_SIZE, y * TILE_SIZE, color, TILE_SIZE);
            }
            draw_grid(&img, x, y, GREY, TILE_SIZE);

            if (data->map[y][x] >= PLAYER_NORTH && data->map[y][x] <= PLAYER_WEST) {
                draw_player(&img, data);
            }
            x++;
        }
        y++;
    }
    mlx_put_image_to_window(data->img.mlx, data->img.mlx_win, data->img.img, 0, 0);
}

void draw_player(t_mlx *img, t_data *data) {
    int start_x = data->player->plyr_x + TILE_SIZE * 3 / 8;
    int start_y = data->player->plyr_y + TILE_SIZE * 3 / 8;
    int end_x = start_x + TILE_SIZE * 2 / 7;
    int end_y = start_y + TILE_SIZE * 2 / 7;
    int i = start_y;
    int j;

    while (i < end_y) {
        j = start_x;
        while (j < end_x) {
            my_mlx_pixel_put(img, j, i, YELLOW);
            j++;
        }
        i++;
    }

	start_x += TILE_SIZE / 2 - TILE_SIZE * 3 / 8;
	start_y += TILE_SIZE / 2 - TILE_SIZE * 3 / 8;

    end_x = start_x + (int)(20 * cos(data->player->angle));
    end_y = start_y - (int)(20 * sin(data->player->angle));
    draw_line(img, start_x, start_y, end_x, end_y, GREEN);

    end_x = start_x + (int)(20 * cos(data->player->angle - data->player->fov_rd / 2));
    end_y = start_y - (int)(20 * sin(data->player->angle - data->player->fov_rd / 2));                
    draw_line(img, start_x, start_y, end_x, end_y, GREEN);

    end_x = start_x + (int)(20 * cos(data->player->angle + data->player->fov_rd / 2));
    end_y = start_y - (int)(20 * sin(data->player->angle + data->player->fov_rd / 2));                
    draw_line(img, start_x, start_y, end_x, end_y, GREEN);
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

void draw_square(t_mlx *img, int start_x, int start_y, int color, int size) {
    int end_x;
    int end_y;
    int i;
    int j;
    
	end_x = start_x + size;
	end_y = start_y + size;
	i = start_y;
    while (i < end_y) {
        j = start_x;
        while (j < end_x) {
            my_mlx_pixel_put(img, j, i, color);
            j++;
        }
        i++;
    }
}

void draw_grid(t_mlx *img, int x, int y, int color, int size) {
    int i = 0;
    while (i <= size) {
        my_mlx_pixel_put(img, x * size + i, y * size, color);
        my_mlx_pixel_put(img, x * size, y * size + i, color);
        my_mlx_pixel_put(img, (x + 1) * size - 1, y * size + i, color);
        my_mlx_pixel_put(img, x * size + i, (y + 1) * size - 1, color);
        i++;
    }
}

void update_graphics(t_data *data) {
    mlx_destroy_image(data->img.mlx, data->img.img);
    data->img.img = mlx_new_image(data->img.mlx, WIDTH, HEIGHT);
    data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel, &data->img.line_length, &data->img.endian);
    draw_minimap(data, data->img);
}

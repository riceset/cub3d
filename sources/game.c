#include "cub3d.h"

void render_wall(t_data *data, t_mlx img);

int close_window(void *param)
{
    (void)param;
    exit(EXIT_SUCCESS);
}

int is_hitting_wall(float player_center_x, float player_center_y, t_data *data) {
    int radius = TILE_SIZE / 7;
    int map_x, map_y;

    map_x = (int)(player_center_x / TILE_SIZE);
    map_y = (int)((player_center_y - radius) / TILE_SIZE);
    if (data->map[map_y][map_x] == WALL)
        return 1;
    map_y = (int)((player_center_y + radius) / TILE_SIZE);
    if (data->map[map_y][map_x] == WALL)
        return 1;
    map_x = (int)((player_center_x - radius) / TILE_SIZE);
    map_y = (int)(player_center_y / TILE_SIZE);
    if (data->map[map_y][map_x] == WALL)
        return 1;
    map_x = (int)((player_center_x + radius) / TILE_SIZE);
    if (data->map[map_y][map_x] == WALL)
        return 1;
    return 0;
}

int key_press(int keycode, t_data *data)
{
    const float move_step = 4.5;
    float new_x, new_y, player_center_x, player_center_y;

    if (keycode == KEY_ESC)
    {
        ft_printf("ESC key is pressed\n");
        exit(EXIT_SUCCESS);
    }
    else if (keycode == KEY_A)
    {
        ft_printf("A key is pressed\n");
        data->player->angle += ROTATION_SPEED;
    }
    else if (keycode == KEY_D)
    {
        ft_printf("D key is pressed\n");
        data->player->angle -= ROTATION_SPEED;
    }
    else if (keycode == KEY_S)
    {
        new_x = data->player->plyr_x - cos(data->player->angle) * move_step;
        new_y = data->player->plyr_y + sin(data->player->angle) * move_step;
        player_center_x = new_x + TILE_SIZE / 2;
        player_center_y = new_y + TILE_SIZE / 2;
        if (!is_hitting_wall(player_center_x, player_center_y, data)) {
            data->player->plyr_x = new_x;
            data->player->plyr_y = new_y;
            ft_printf("S key is pressed and player moved\n");
        } else {
            ft_printf("S key is pressed but player hit a wall\n");
        }
    }
    else if (keycode == KEY_W) {
        new_x = data->player->plyr_x + cos(data->player->angle) * move_step;
        new_y = data->player->plyr_y - sin(data->player->angle) * move_step;
        player_center_x = new_x + TILE_SIZE / 2;
        player_center_y = new_y + TILE_SIZE / 2;
        if (!is_hitting_wall(player_center_x, player_center_y, data)) {
            data->player->plyr_x = new_x;
            data->player->plyr_y = new_y;
            ft_printf("W key is pressed and player moved\n");
        } else {
            ft_printf("W key is pressed but player hit a wall\n");
        }
    }

    if (keycode != KEY_ESC)
        update_graphics(data);

    return 0;
}


void start_game(t_data *data)
{
    printf("%08X, %08X\n", data->colors.ceiling_color, data->colors.floor_color);
    data->img.mlx = mlx_init();
    data->img.mlx_win = mlx_new_window(data->img.mlx, WIDTH, HEIGHT, "Cub3D");
    data->img.img = mlx_new_image(data->img.mlx, WIDTH, HEIGHT);
    data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel, &data->img.line_length, &data->img.endian);
    render_wall(data, data->img);
    draw_minimap(data, data->img);
    mlx_put_image_to_window(data->img.mlx, data->img.mlx_win, data->img.img, 0, 0);
    mlx_hook(data->img.mlx_win, ON_KEYDOWN, KEY_PRESS_MASK, key_press, data);
    mlx_hook(data->img.mlx_win, ON_DESTROY, NO_EVENT_MASK, close_window, NULL);
    mlx_loop(data->img.mlx);
}

int get_floor_color(char *filename, t_data *data)
{
    int color;
    int fd;
    char *line;
    char **tmp;

    color = -1;
	fd = open(filename, O_RDONLY, 0);
	if (fd == -1)
		ft_exit("Error opening file", data);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break;
        if(line[0] == 'F' && ft_isspace(line[1]))
        {
            if(color != -1 || check_line(line) == ERROR)
                ft_exit("Map Error", data);
            tmp = ft_split(line, ',');
            color = rgb_to_int(ft_atoi(++tmp[0]), ft_atoi(tmp[1]), ft_atoi(tmp[2]));
            if(color == -1)
            {
                free_array(tmp);
                ft_exit("Map Error", data);
            }
            printf("Floor color code: %08X\n", color);
        }
        free(line);
    }
    close(fd);
    return color;
}

int get_ceiling_color(char *filename, t_data *data)
{
    int color;
    int fd;
    char *line;
    char **tmp;

    color = -1;
	fd = open(filename, O_RDONLY, 0);
	if (fd == -1)
		ft_exit("Error opening file", data);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break;
        if(line[0] == 'C' && ft_isspace(line[1]))
        {
            if(color != -1 || check_line(line) == ERROR)
                ft_exit("Map Error", data);
            tmp = ft_split(line, ',');
            color = rgb_to_int(ft_atoi(++tmp[0]), ft_atoi(tmp[1]), ft_atoi(tmp[2]));
            if(color == -1)
            {
                free_array(tmp);
                ft_exit("Map Error", data);
            }
            printf("Ceiling color code: %08X\n", color);
        }
        free(line);
    }
    close(fd);
    return color;
}

t_data *init_data(char **argv)
{
    t_data *data;

    print_file(argv[1]);
    data = (t_data *)malloc(sizeof(t_data));
    if (!data)
        ft_exit("Memory allocation failed", data);
    data->colors.floor_color = get_floor_color(argv[1], data);
    data->colors.ceiling_color = get_ceiling_color(argv[1], data);
    data->h_map = get_height(argv[1], data);
    data->w_map = get_width(argv[1], data);
    if (data->h_map < 3 || data->w_map < 3)
        ft_exit("Map Error", data);
    data->map = init_map(argv[1], data->h_map, data->w_map, data);
    print_map(data->map, data->w_map, data->h_map);
    data->player = init_player(data);
    print_map(data->map, data->w_map, data->h_map);
    if (validate_map(data))
        ft_exit("Map Error", data);
    return (data);
}
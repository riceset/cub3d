#include "cub3d.h"

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

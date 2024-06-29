#include "cub3d.h"

void handle_key_esc(t_data *data);
void handle_key_a(t_data *data);
void handle_key_s(t_data *data);
void handle_key_d(t_data *data);
void handle_key_w(t_data *data);

void move_player(t_data *data, float move_x, float move_y) {
    float new_x = data->player->plyr_x + move_x;
    float new_y = data->player->plyr_y + move_y;
    float player_center_x = new_x + TILE_SIZE / 2;
    float player_center_y = new_y + TILE_SIZE / 2;

    if (!is_hitting_wall(player_center_x, player_center_y, data)) {
        data->player->plyr_x = new_x;
        data->player->plyr_y = new_y;
        ft_printf("Player moved\n");
    } else {
        ft_printf("Player hit a wall\n");
    }
}

int key_press(int keycode, t_data *data)
{
    switch(keycode) {
        case KEY_ESC:
            handle_key_esc(data);
            break;
        case KEY_A:
            handle_key_a(data);
            break;
        case KEY_D:
            handle_key_d(data);
            break;
        case KEY_S:
            handle_key_s(data);
            break;
        case KEY_W:
            handle_key_w(data);
            break;
    }
    if (keycode != KEY_ESC)
        update_graphics(data);
    return 0;
}

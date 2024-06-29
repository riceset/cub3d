#include "cub3d.h"

void move_player(t_data *data, float move_x, float move_y);

void handle_key_esc(t_data *data) {
    ft_printf("ESC key is pressed\n");
    free_data(data);
    exit(EXIT_SUCCESS);
}

void handle_key_a(t_data *data) {
    ft_printf("A key is pressed\n");
    data->player->angle += ROTATION_SPEED;
}

void handle_key_d(t_data *data) {
    ft_printf("D key is pressed\n");
    data->player->angle -= ROTATION_SPEED;
}

void handle_key_s(t_data *data) {
    ft_printf("S key is pressed\n");
    move_player(data, -cos(data->player->angle) * 4.5, sin(data->player->angle) * 4.5);
}

void handle_key_w(t_data *data) {
    ft_printf("W key is pressed\n");
    move_player(data, cos(data->player->angle) * 4.5, -sin(data->player->angle) * 4.5);
}

#include "cub3d.h"

int get_texture_color(t_texture *texture, int x, int y) {
    int offset = (y * texture->width + x) * 3;
    unsigned char blue = texture->data[offset];
    unsigned char green = texture->data[offset + 1];
    unsigned char red = texture->data[offset + 2];

    return (red << 16) | (green << 8) | blue;
}
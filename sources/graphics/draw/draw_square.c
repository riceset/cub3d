#include "cub3d.h"

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


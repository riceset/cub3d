#include "cub3d.h"

void	draw_line(t_mlx *img, int start_x, int start_y, int end_x, int end_y,
		int color)
{
	float	x_step;
	float	y_step;
	int		steps;
	float	x;
	float	y;
	int		i;

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

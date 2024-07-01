#include "cub3d.h"

void	draw_grid(t_mlx *img, int x, int y, int color, int size)
{
	int	i;

	i = 0;
	while (i <= size)
	{
		my_mlx_pixel_put(img, x * size + i, y * size, color);
		my_mlx_pixel_put(img, x * size, y * size + i, color);
		my_mlx_pixel_put(img, (x + 1) * size - 1, y * size + i, color);
		my_mlx_pixel_put(img, x * size + i, (y + 1) * size - 1, color);
		i++;
	}
}

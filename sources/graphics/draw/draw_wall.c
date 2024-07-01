#include "cub3d.h"

void	draw_wall(t_mlx *img, int ray, int top_pixel, int bottom_pixel,
		int color)
{
	int	pixel_y;

	pixel_y = top_pixel;
	while (pixel_y < bottom_pixel)
	{
		my_mlx_pixel_put(img, ray, pixel_y, color);
		pixel_y++;
	}
}

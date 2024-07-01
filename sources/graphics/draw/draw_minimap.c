#include "cub3d.h"

void	draw_minimap(t_data *data, t_mlx img)
{
	int	x;
	int	y;
	int	color;

	x = 0;
	y = 0;
	while (y < data->h_map)
	{
		x = 0;
		while (x < data->w_map)
		{
			if (data->map[y][x] == WALL || data->map[y][x] == FORBIDDEN_SPACE)
			{
				if (data->map[y][x] == WALL)
					color = WHITE;
				else if (data->map[y][x] == FORBIDDEN_SPACE)
					color = RED;
				draw_square(&img, x * TILE_SIZE, y * TILE_SIZE, color,
					TILE_SIZE);
			}
			draw_grid(&img, x, y, GREY, TILE_SIZE);
			if (data->map[y][x] >= PLAYER_NORTH
				&& data->map[y][x] <= PLAYER_WEST)
				draw_player(&img, data);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->img.mlx, data->img.mlx_win, data->img.img, 0,
		0);
}

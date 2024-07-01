#include "cub3d.h"

void	draw_player_rectangle(t_mlx *img, t_data *data)
{
	int	start_x;
	int	start_y;
	int	end_x;
	int	end_y;
	int	i;
	int	j;

	start_x = data->player->plyr_x + TILE_SIZE * 3 / 8;
	start_y = data->player->plyr_y + TILE_SIZE * 3 / 8;
	end_x = start_x + TILE_SIZE * 2 / 7;
	end_y = start_y + TILE_SIZE * 2 / 7;
	i = start_y;
	while (i < end_y)
	{
		j = start_x;
		while (j < end_x)
		{
			my_mlx_pixel_put(img, j, i, YELLOW);
			j++;
		}
		i++;
	}
}

void	draw_player_fov(t_mlx *img, t_data *data)
{
	double	start_angle;
	double	angle_step;

	start_angle = data->player->angle - data->player->fov_rd / 2;
	angle_step = data->player->fov_rd / 20;
	while (start_angle < data->player->angle + data->player->fov_rd / 2)
	{
		draw_ray_minimap(img, data, start_angle, GREEN);
		start_angle += angle_step;
	}
}

void	draw_player(t_mlx *img, t_data *data)
{
	draw_player_rectangle(img, data);
	draw_player_fov(img, data);
}

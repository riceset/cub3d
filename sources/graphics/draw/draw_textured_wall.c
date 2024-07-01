#include "cub3d.h"

static void	draw_textured_pixels(t_mlx *img, int ray, int direction,
				t_wall_data *wall_data, t_texture_data *tex_data);
static int	get_direction(t_data *data, int ray, t_texture_data *tex_data);

void	draw_textured_wall(t_mlx *img, int ray, t_wall_data *wall_data,
		t_texture_data *tex_data, t_data *data)
{
	int	direction;

	direction = get_direction(data, ray, tex_data);
	draw_textured_pixels(img, ray, direction, wall_data, tex_data);
}

static void	calculate_hits_and_texture(t_data *data, double ray_angle,
		double distance, int direction, t_texture_data *tex_data)
{
	if (direction == EAST)
	{
		tex_data->hitY = data->player->plyr_y - distance * sin(ray_angle);
		tex_data->wallX = fmod(tex_data->hitY, TILE_SIZE);
		tex_data->texX = -(int)((TILE_SIZE / 2 + tex_data->wallX)
				* tex_data->texture[EAST]->width / TILE_SIZE)
			% tex_data->texture[EAST]->width;
	}
	else if (direction == WEST)
	{
		tex_data->hitY = data->player->plyr_y - distance * sin(ray_angle);
		tex_data->wallX = fmod(tex_data->hitY, TILE_SIZE);
		tex_data->texX = (int)((TILE_SIZE / 2 + tex_data->wallX)
				* tex_data->texture[WEST]->width / TILE_SIZE)
			% tex_data->texture[WEST]->width;
	}
	else if (direction == SOUTH)
	{
		tex_data->hitX = data->player->plyr_x + distance * cos(ray_angle);
		tex_data->wallX = fmod(tex_data->hitX, TILE_SIZE);
		tex_data->texX = (int)((TILE_SIZE / 2 + tex_data->wallX)
				* tex_data->texture[SOUTH]->width / TILE_SIZE)
			% tex_data->texture[SOUTH]->width;
	}
	else if (direction == NORTH)
	{
		tex_data->hitX = data->player->plyr_x + distance * cos(ray_angle);
		tex_data->wallX = fmod(tex_data->hitX, TILE_SIZE);
		tex_data->texX = -(int)((TILE_SIZE / 2 + tex_data->wallX)
				* tex_data->texture[NORTH]->width / TILE_SIZE)
			% tex_data->texture[NORTH]->width;
	}
}

static int	get_direction(t_data *data, int ray, t_texture_data *tex_data)
{
	double	ray_angle;
	int		direction;

	ray_angle = data->player->angle + (data->player->fov_rd / 2) - (ray
			* data->player->fov_rd / WIDTH);
	direction = determine_wall_direction(data, ray_angle);
	calculate_hits_and_texture(data, ray_angle, cast_ray(data, ray_angle),
		direction, tex_data);
	return (direction);
}

static void	draw_textured_pixels(t_mlx *img, int ray, int direction,
		t_wall_data *wall_data, t_texture_data *tex_data)
{
	int	pixel_y;
	int	texY;
	int	color;
	int	draw_start;
	int	draw_end;

	draw_start = wall_data->top_pixel;
	draw_end = wall_data->bottom_pixel;
	for (pixel_y = draw_start; pixel_y < draw_end; pixel_y++)
	{
		if (pixel_y >= 0 && pixel_y < HEIGHT) // ウィンドウの範囲内のピクセルのみ描画
		{
			texY = ((pixel_y - wall_data->top_pixel)
					* tex_data->texture[direction]->height)
				/ wall_data->wall_height;
			if (texY < 0)
				texY = 0;
			if (texY >= tex_data->texture[direction]->height)
				texY = tex_data->texture[direction]->height - 1;
			color = get_texture_color(tex_data->texture[direction],
					tex_data->texX, texY);
			my_mlx_pixel_put(img, ray, pixel_y, color);
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture_from_bmp.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riceset <tkomeno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:20:51 by riceset           #+#    #+#             */
/*   Updated: 2024/07/04 18:54:36 by riceset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	allocate_and_read_data(int fd, t_texture *texture)
{
	int	data_size;

	data_size = texture->width * texture->height * 3;
	texture->data = malloc(data_size);
	if (!texture->data)
	{
		perror("Failed to allocate texture data");
		free(texture);
		close(fd);
		exit(1);
	}
	if (read(fd, texture->data, data_size) != data_size)
	{
		perror("Error reading texture data");
		free(texture->data);
		free(texture);
		close(fd);
		exit(1);
	}
}

t_texture	*load_texture_from_bmp(const char *file_path)
{
	t_texture	*texture;
	int			fd;
	int			has_alpha;

	fd = open_texture_file(file_path);
	texture = allocate_texture();
	read_and_validate_header(fd, texture, &has_alpha);
	allocate_and_read_data(fd, texture);
	close(fd);
	return (texture);
}

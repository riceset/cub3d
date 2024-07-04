/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riceset <tkomeno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:53:33 by riceset           #+#    #+#             */
/*   Updated: 2024/07/04 18:54:31 by riceset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	bytes_to_int(byte *bytes, int num_bytes)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (i < num_bytes)
	{
		res |= bytes[i] << (8 * i);
		i++;
	}
	return (res);
}

void	read_bmp_header(int fd, int *width, int *height, int *has_alpha)
{
	unsigned char	header[54];
	int				bits_per_pixel;
	int				compression;

	if (read(fd, header, 54) != 54)
	{
		perror("Failed to read header");
		close(fd);
		exit(1);
	}
	*width = bytes_to_int(&header[18], 4);
	*height = bytes_to_int(&header[22], 4);
	bits_per_pixel = bytes_to_int(&header[28], 2);
	compression = bytes_to_int(&header[30], 4);
	if (bits_per_pixel == 32 && (compression == 3 || compression == 6))
		*has_alpha = 1;
	else
		*has_alpha = 0;
	if (*height < 0)
		*height *= -1;
}

int	open_texture_file(const char *file_path)
{
	int	fd;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		exit(1);
	}
	return (fd);
}

t_texture	*allocate_texture(void)
{
	t_texture	*texture;

	texture = malloc(sizeof(t_texture));
	if (!texture)
	{
		perror("Failed to allocate texture");
		exit(1);
	}
	return (texture);
}

void	read_and_validate_header(int fd, t_texture *texture, int *has_alpha)
{
	read_bmp_header(fd, &texture->width, &texture->height, has_alpha);
	if (*has_alpha)
	{
		perror("Provide a 24bit bitmap image");
		exit(1);
	}
}

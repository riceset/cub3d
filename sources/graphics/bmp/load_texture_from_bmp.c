#include "cub3d.h"

static void	read_bmp_header(int fd, int *width, int *height, int *has_alpha)
{
	unsigned char	header[54];
	int				bitsPerPixel;
	int				compression;

	if (read(fd, header, 54) != 54)
	{
		perror("Failed to read header");
		close(fd);
		exit(1);
	}
	*width = header[18] | (header[19] << 8) | (header[20] << 16) | (header[21] << 24);
	*height = header[22] | (header[23] << 8) | (header[24] << 16) | (header[25] << 24);
	bitsPerPixel = header[28] | (header[29] << 8);
	compression = header[30] | (header[31] << 8) | (header[32] << 16) | (header[33] << 24);
	if (bitsPerPixel == 32 && (compression == 3 || compression == 6))
	{
		*has_alpha = 1;
	}
	else
	{
		*has_alpha = 0;
	}
	if (*height < 0)
	{
		*height *= -1;
	}
}

t_texture	*load_texture_from_bmp(const char *file_path)
{
	int			fd;
	int			has_alpha;
	t_texture	*texture;
	int			dataSize;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		exit(1);
	}
	texture = malloc(sizeof(t_texture));
	if (!texture)
	{
		perror("Failed to allocate texture");
		close(fd);
		exit(1);
	}
	read_bmp_header(fd, &texture->width, &texture->height, &has_alpha);
	if (has_alpha)
	{
		perror("Provide a 24bit bitmap image");
		exit(1);
	}
	dataSize = texture->width * texture->height * 3;
	texture->data = malloc(dataSize);
	if (!texture->data)
	{
		perror("Failed to allocate texture data");
		free(texture);
		close(fd);
		exit(1);
	}
	if (read(fd, texture->data, dataSize) != dataSize)
	{
		perror("Error reading texture data");
		free(texture->data);
		free(texture);
		close(fd);
		exit(1);
	}
	close(fd);
	return (texture);
}

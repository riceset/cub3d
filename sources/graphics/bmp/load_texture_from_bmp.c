#include "cub3d.h"

static void skip_bmp_header(int fd)
{
	unsigned char header[54];

	if (read(fd, header, 54) != 54) {
		perror("Failed to read header");
		close(fd);
		exit(1);
	}
}

t_texture *load_texture_from_bmp(const char *file_path) {
    int fd = open(file_path, O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
        exit(1);
    }

    skip_bmp_header(fd);

    t_texture *texture = malloc(sizeof(t_texture));
    if (!texture) {
        perror("Failed to allocate texture");
        close(fd);
        exit(1);
    }

    texture->width = 128;
    texture->height = 128;
    int dataSize = texture->width * texture->height * 3;
    texture->data = malloc(dataSize);
    if (!texture->data) {
        perror("Failed to allocate texture data");
        free(texture);
        close(fd);
        exit(1);
    }

    if (read(fd, texture->data, dataSize) != dataSize) {
        perror("Error reading texture data");
        free(texture->data);
        free(texture);
        close(fd);
        exit(1);
    }

    close(fd);
    return texture;
}

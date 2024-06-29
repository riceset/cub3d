#include "cub3d.h"

char **get_textures(char *filename, t_data **data)
{
    int fd = open_file(filename, *data);
    char *line;
    int texture_index;

    texture_index = 0;
    while ((line = get_next_line(fd)) != NULL)
    {
        if (strncmp(line, "NO ", 3) == 0 || strncmp(line, "SO ", 3) == 0 ||
            strncmp(line, "WE ", 3) == 0 || strncmp(line, "EA ", 3) == 0)
        {
            char *path = ft_strtrim(line + 3, " \t\n");
            if (path == NULL)
            {
                free(line);
                close(fd);
                ft_exit("Failed to allocate memory for texture path", *data);
            }
            (*data)->texture[texture_index++] = path;
        }
        free(line);
    }
    close(fd);

    return (NULL);
}

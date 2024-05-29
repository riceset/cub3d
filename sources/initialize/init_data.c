#include "cub3d.h"

char **get_textures(char *filename, t_data **data)
{
    int fd = open_file(filename, *data);
    if (fd == -1)
        ft_exit("Error opening file", *data);

    char *line;
    int texture_index;

    texture_index = 0;
    while ((line = get_next_line(fd)) != NULL) {
    if (strncmp(line, "NO ", 3) == 0 || strncmp(line, "SO ", 3) == 0 || 
            strncmp(line, "WE ", 3) == 0 || strncmp(line, "EA ", 3) == 0) {
            char *path = malloc(strlen(line) - 3 + 1);
            if (path == NULL) {
                ft_exit("Failed to allocate memory for texture path", *data);
            }
            strcpy(path, line + 3);
            (*data)->texture[texture_index++] = path;
        }
        free(line);
        if (texture_index >= 4)
            break;
    }
    close(fd);
    return (NULL);
}

t_data *init_data(char **argv)
{
    t_data *data;

    print_file(argv[1]);
    data = (t_data *)malloc(sizeof(t_data));
    if (!data)
        ft_exit("Memory allocation failed", data);
    data->colors.floor_color = get_map_colors(argv[1], data, FLOOR);
    data->colors.ceiling_color = get_map_colors(argv[1], data, CEILING);
    get_textures(argv[1], &data);
    data->h_map = get_map_height(argv[1], data);
    data->w_map = get_map_width(argv[1], data);
    if (data->h_map < 3 || data->w_map < 3)
        ft_exit("Map Error", data);
    data->map = init_map(argv[1], data->h_map, data->w_map, data);
    print_map(data->map, data->w_map, data->h_map);
    data->player = init_player(data);
    print_map(data->map, data->w_map, data->h_map);
    if (validate_map(data))
        ft_exit("Map Error", data);
    return (data);
}

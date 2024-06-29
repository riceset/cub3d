#include "cub3d.h"

int get_map_colors(char *filename, t_data *data, char type)
{
    int color = -1;
    int fd = open_file(filename, data);
    if (fd == -1)
        ft_exit("Error opening file", data);

    char *line;
    while ((line = get_next_line(fd)) != NULL) {
        if (line[0] == type && ft_isspace(line[1])) {
            if (color != -1 || check_line(line) == ERROR) {
                close(fd);
                ft_exit("Map Error", data);
            }
            char **tmp = ft_split(line, ',');
            color = rgb_to_int(ft_atoi(tmp[0] + 1), ft_atoi(tmp[1]), ft_atoi(tmp[2]));
            if (color == -1) {
                free_array(tmp);
                close(fd);
                ft_exit("Map Error", data);
            }
            free_array(tmp);
        }
        free(line);
    }
    close(fd);
    return color;
}

#include "cub3d.h"

void	free_map(int **map, int height)
{
	int	i;

	if (map)
	{
		for (i = 0; i < height; i++)
		{
			if (map[i])
			{
				free(map[i]);
			}
		}
		free(map);
	}
}

int open_file(char *filename)
{
	int fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		ft_exit("Error opening file", NULL);
	return (fd);
}

void	ft_exit(char *err_msg, t_data *data)
{
	if (err_msg)
	{
		perror(err_msg);
	}
	if (data)
	{
		if (data->map)
		{
			free_map(data->map, data->h_map);
		}
		if (data->player)
		{
			free(data->player);
		}
		free(data);
	}
	exit(EXIT_FAILURE);
}
int	extension_check(char *filename)
{
	int	i;

	i = 0;
	while (filename[i] != '\0' && filename[i] != '.')
		i++;
	if (i != 0 && filename[i] == '.' && filename[i + 1] == 'c' && filename[i
		+ 2] == 'u' && filename[i + 3] == 'b' && filename[i + 4] == '\0')
		return (SUCCESS);
	return (ERROR);
}

void free_array(char **array) {
    int i;

    i = 0;
    if(!array)
    {
        while(!array[i])
        {
            free(array[i]);
            i++;
        }
        free(array);
    }
}

int rgb_to_int(int r, int g, int b) {
    if((0 <= r && r <= 255) && (0 <= g && g <= 255) && (0 <= b && b <= 255))
        return (r << 24) | (g << 16) | (b << 8);
    return -1;
}

int check_line(char *line)
{
    int i;

    i = 2;
    while(line[i] != '\0')
    {
        if(!('0' <= line[i] && line[i] <= '9') && line[i] != ',' && !ft_isspace(line[i]))
            return ERROR;
        i++;
    }
    return SUCCESS;
}

void	print_file(char *filename)
{
	char	*line;
	int		fd;
	int		line_number;

	line_number = 1;
	printf("\n--------- Start of %s ---------\n\n", filename);
	fd = open(filename, O_RDONLY);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%d: %s", line_number, line);
		free(line);
		line_number++;
	}
	printf("\n\n--------- End of %s ---------\n\n", filename);
	close(fd);
}

void	print_map(int **map, int w_map, int h_map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	printf("\n--------- Start of Map ---------\n\n");
	while (i < h_map)
	{
		while (j < w_map)
		{
			printf("%d", map[i][j]);
			j++;
		}
		printf("\n");
		j = 0;
		i++;
	}
	printf("\n--------- End of Map ---------\n\n");
}

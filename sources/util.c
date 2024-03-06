/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiro <hiro@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:07:17 by hiro              #+#    #+#             */
/*   Updated: 2024/03/06 13:48:23 by hiro             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void ft_exit(char *err_msg)
{
	perror(err_msg);
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

void print_file(char *filename)
{
    char *line;
    int fd;
    int line_number = 1;
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

void print_map(int **map, int w_map)
{
    int i = 0;
	int j = 0;
    printf("\n--------- Start of Map ---------\n\n");
    while(map[i] != NULL)
    {
		while(j < w_map)
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

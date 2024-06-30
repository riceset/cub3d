/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@tokyo.42.school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 17:24:05 by hhagiwar          #+#    #+#             */
/*   Updated: 2024/06/30 17:39:55 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_file(char *filename)
{
	char	*line;
	int		fd;
	int		line_number;

	line_number = 1;
	ft_printf("\n--------- Start of %s ---------\n\n", filename);
	fd = open(filename, O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
		{
			free(line);
			break ;
		}
		ft_printf("%d: %s", line_number, line);
		free(line);
		line_number++;
	}
	ft_printf("\n\n--------- End of %s ---------\n\n", filename);
	close(fd);
}

void	print_map(int **map, int w_map, int h_map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	ft_printf("\n--------- Start of Map ---------\n\n");
	while (i < h_map)
	{
		while (j < w_map)
		{
			ft_printf("%d", map[i][j]);
			j++;
		}
		ft_printf("\n");
		j = 0;
		i++;
	}
	ft_printf("\n--------- End of Map ---------\n\n");
}

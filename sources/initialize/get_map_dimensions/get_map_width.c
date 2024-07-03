/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_width.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@tokyo.42.school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 00:06:45 by hhagiwar          #+#    #+#             */
/*   Updated: 2024/07/03 00:06:45 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_map_width(char *filename, t_data *data)
{
	int		width;
	int		fd;
	char	*line;
	int		tmp;

	fd = open(filename, O_RDONLY, 0);
	if (fd == -1)
		ft_exit("Error opening file", data);
	tmp = -1;
	width = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		tmp = num_count(line);
		if (tmp > width && (ft_isdigit(line[0]) || ft_isspace(line[0])))
			width = tmp;
		free(line);
	}
	close(fd);
	if (width > 50)
		ft_exit("Map width must be <= 50", data);
	return (width - 1);
}

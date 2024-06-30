/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@tokyo.42.school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 17:12:50 by hhagiwar          #+#    #+#             */
/*   Updated: 2024/06/30 17:23:56 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_exit(char *err_msg, t_data *data)
{
	if (err_msg)
		perror(err_msg);
	free_data(data);
	exit(EXIT_FAILURE);
}

int	extension_check(char *filename)
{
	int	i;

	i = 0;
	while (filename[i] != '\0' && filename[i] != '.')
		i++;
	if (i != 0 && filename[i] == '.' && filename[i + 1] == 'c' && \
	filename[i + 2] == 'u' && filename[i + 3] == 'b' && filename[i + 4] == '\0')
		return (SUCCESS);
	return (ERROR);
}

int	rgb_to_int(int r, int g, int b)
{
	if ((0 <= r && r <= 255) && (0 <= g && g <= 255) && (0 <= b && b <= 255))
		return ((r << 16) | (g << 8) | b);
	return (-1);
}

int	open_file(const char *filename, t_data *data)
{
	int	fd;

	fd = open(filename, O_RDONLY, 0);
	if (fd == -1)
		ft_exit("Error opening file", data);
	return (fd);
}

int	check_line(char *line)
{
	int	i;

	i = 2;
	while (line[i] != '\0')
	{
		if (!('0' <= line[i] && line[i] <= '9') && line[i] != ','
			&& !ft_isspace(line[i]))
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

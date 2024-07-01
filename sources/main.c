/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@tokyo.42.school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 17:10:32 by hhagiwar          #+#    #+#             */
/*   Updated: 2024/06/30 17:27:39 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	(void)data;
	if (argc == 2)
	{
		if (extension_check(argv[1]) == ERROR)
			ft_exit("File extension must be .cub", NULL);
		data = init_data(argv);
		start_game(data);
	}
	else
		ft_exit("Error: Invalid command line arguments. \n \
		Usage: ./cub3D <path_to_map_file.cub>",
				NULL);
	exit(EXIT_SUCCESS);
}

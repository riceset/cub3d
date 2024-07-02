/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_count.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@tokyo.42.school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 00:07:02 by hhagiwar          #+#    #+#             */
/*   Updated: 2024/07/03 00:07:03 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	num_count(char *str)
{
	int	count;

	count = 0;
	while (*str != '\0')
	{
		if (ft_isdigit(*str) || ft_isspace(*str))
		{
			count++;
			if (count == INT_MAX)
				exit(EXIT_FAILURE);
		}
		str++;
	}
	return (count);
}

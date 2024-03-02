/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_printf.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:16:39 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/06/21 17:37:26 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr_printf(char *str)
{
	int	count;

	count = 0;
	while (*str != '\0')
	{
		write(1, str, sizeof(*str));
		count++;
		str++;
	}
	return (count);
}

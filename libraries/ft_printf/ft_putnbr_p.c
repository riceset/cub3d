/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:25:56 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/06/27 11:45:50 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_num_p(int digit)
{
	char	num;

	if (digit < 10)
		num = '0' + digit;
	else
		num = 'a' + (digit - 10);
	return (ft_putchar_printf(num));
}

int	count_digit(uintptr_t ptr_value)
{
	int	count;

	count = 0;
	if (ptr_value >= 0x10)
		count += count_digit(ptr_value / 0x10);
	count += print_num_p(ptr_value % 0x10);
	return (count);
}

int	ft_putnbr_p(void *ptr)
{
	unsigned long	count;
	uintptr_t		ptr_value;

	count = 0;
	ptr_value = (uintptr_t)ptr;
	if (ptr == NULL)
		count = ft_putchar_printf('0');
	else
	{
		count += count_digit(ptr_value);
	}
	return (count);
}

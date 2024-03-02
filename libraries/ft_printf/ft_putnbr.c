/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:25:56 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/07/14 15:27:21 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static long	get_digit(long n, int base)
{
	long	digit;

	digit = 1;
	if (n < 0)
		n = -n;
	while (n / base > 0)
	{
		n /= base;
		digit *= base;
	}
	return (digit);
}

long	ft_putnbr(long n, char *base)
{
	unsigned long	digit;
	int				i;
	long			count;

	count = 0;
	i = ft_strlen(base);
	digit = get_digit(n, i);
	if (n == 0)
		count = ft_putchar_printf('0');
	else
	{
		if (n < 0)
		{
			count += ft_putchar_printf('-');
			n = -n;
		}
		while (digit != 0)
		{
			count++;
			ft_putchar_printf(base[n / digit]);
			n %= digit;
			digit /= i;
		}
	}
	return (count);
}

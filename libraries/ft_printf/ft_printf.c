/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 12:01:17 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/06/18 14:18:59 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	put_format_extension(const char *str, va_list ap)
{
	int	count;

	count = 0;
	if (*str == 'p')
	{
		count = ft_putstr_printf("0x");
		count += ft_putnbr_p(va_arg(ap, void *));
	}
	else if (*str == 'd' || *str == 'i')
		count = ft_putnbr(va_arg(ap, int), "0123456789");
	else if (*str == 'u')
		count = ft_putnbr(va_arg(ap, unsigned int), "0123456789");
	else if (*str == 'x')
		count = ft_putnbr(va_arg(ap, unsigned int), "0123456789abcdef");
	else if (*str == 'X')
		count = ft_putnbr(va_arg(ap, unsigned int), "0123456789ABCDEF");
	else if (*str == '%')
		count = ft_putchar_printf('%');
	else
		count = ft_putchar_printf(*str);
	return (count);
}

int	put_format(const char *str, va_list ap)
{
	int		count;
	char	*tmp;

	count = 0;
	if (*str == 'c')
		count = ft_putchar_printf(va_arg(ap, int));
	else if (*str == 's')
	{
		tmp = (char *)va_arg(ap, char *);
		if (tmp == NULL)
			count = ft_putstr_printf("(null)");
		else
			count = ft_putstr_printf(tmp);
	}
	else
		count = put_format_extension(str, ap);
	return (count);
}

int	ft_printf(const char *arg, ...)
{
	va_list	ap;
	int		count;

	count = 0;
	va_start(ap, arg);
	if (arg == NULL)
		return (-1);
	while (*arg != '\0')
	{
		if (*arg == '%')
		{
			arg++;
			count += put_format(arg, ap);
		}
		else
		{
			count += ft_putchar_printf(*arg);
		}
		arg++;
	}
	va_end(ap);
	return (count);
}

// int	main(void)
// {
// 	ft_printf("---ft_printf---\n");
// 	ft_printf("char:%c\nstring:%s\nint(d):%d\n", '\0', NULL, NULL);
// 	ft_printf("hexadecimal(p):%p\n", (void *)0);
// 	ft_printf("int(i):%i\n", -11110);
// 	ft_printf("unsigned int:%u\n", (unsigned int)-4294967196);
// 	ft_printf("base16:%x\n", 3000);
// 	ft_printf("BASE16:%X\n", 3000);
// 	ft_printf("%%\n");
// 	//
// 	printf("\n---printf---\n");
// 	printf("char:%c\nstring:%s\nint(d):%d\n", '\0', NULL, NULL);
// 	printf("hexadecimal(p):%p\n", (void *)(0));
// 	// printf("hexadecimal(p):%zu\n", ULONG_MAX);
// 	printf("int(i):%i\n", -11110);
// 	printf("unsigned int:%u\n", (unsigned int)922337203685);
// 	printf("base16:%x\n", 3000);
// 	printf("BASE16:%X\n", 3000);
// 	printf("%%\n");
// 	// printf("%zu\n", );
// 	printf("\n\n-----end------");
// 	return (0);
// }

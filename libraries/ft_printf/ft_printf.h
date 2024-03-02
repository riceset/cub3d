/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 12:20:06 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/06/18 12:47:59 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <limits.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

int		ft_printf(const char *arg, ...);
size_t	ft_strlen(const char *s);
int		ft_putchar_printf(char chr);
int		ft_putstr_printf(char *str);
long	ft_putnbr(long n, char *base);
int		ft_putnbr_p(void *ptr);

#endif
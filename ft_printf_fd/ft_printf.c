/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:02:38 by ncharbog          #+#    #+#             */
/*   Updated: 2024/12/19 11:14:51 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_format(int fd, char format, va_list args)
{
	if (format == '%')
		return (ft_putchar(fd, format));
	if (format == 'c')
		return (ft_putchar(fd, (char)va_arg(args, int)));
	if (format == 's')
		return (ft_putstr(fd, va_arg(args, char *)));
	if (format == 'd' || format == 'i')
		return (ft_putnbr_base_fd(fd, (long long)va_arg(args, int),
				"0123456789"));
	if (format == 'x')
		return (ft_putnbr_u_fd(fd, (unsigned int)va_arg(args, int),
				"0123456789abcdef"));
	if (format == 'X')
		return (ft_putnbr_u_fd(fd, (unsigned int)va_arg(args, int),
				"0123456789ABCDEF"));
	if (format == 'p')
		return (ft_p_fd(fd, va_arg(args, void *)));
	if (format == 'u')
		return (ft_putnbr_u_fd(fd, (unsigned int)va_arg(args, int),
				"0123456789"));
	return (0);
}

int	ft_printf_fd(int fd, char const *format, ...)
{
	unsigned int	i;
	unsigned int	len;
	va_list			args;

	i = 0;
	len = 0;
	if (!format)
		return (-1);
	va_start(args, format);
	while (format[i])
	{
		if (format[i] && format[i] == '%')
		{
			i++;
			len += ft_format(fd, format[i], args);
			i++;
		}
		else if (format[i])
		{
			len += ft_putchar(fd, format[i]);
			i++;
		}
	}
	va_end (args);
	return (len);
}

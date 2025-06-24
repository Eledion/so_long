/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danoguer <danoguer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:47:15 by danoguer          #+#    #+#             */
/*   Updated: 2025/04/28 18:39:06 by danoguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_format_handler(va_list args, const char format)
{
	int	count;

	count = 0;
	if (format == 'c')
		count += ft_print_char(va_arg(args, int));
	else if (format == 's')
		count += ft_print_string(va_arg(args, char *));
	else if (format == 'p')
		count += ft_print_pointer(va_arg(args, void *));
	else if (format == 'd' || format == 'i')
		count += ft_print_int(va_arg(args, int));
	else if (format == 'u')
		count += ft_print_uint(va_arg(args, unsigned int));
	else if (format == 'x')
		count += ft_print_hex(va_arg(args, unsigned int), 0);
	else if (format == 'X')
		count += ft_print_hex(va_arg(args, unsigned int), 1);
	else if (format == '%')
		count += ft_print_percent();
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;
	int		i;

	if (!format)
		return (-1);
	va_start(args, format);
	count = 0;
	i = 0;
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			count += ft_format_handler(args, format[i + 1]);
			i++;
		}
		else if (format[i] != '%')
			count += ft_print_char(format[i]);
		i++;
	}
	va_end(args);
	return (count);
}

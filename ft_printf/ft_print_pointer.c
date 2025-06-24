/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danoguer <danoguer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:29:25 by danoguer          #+#    #+#             */
/*   Updated: 2025/04/28 18:54:00 by danoguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_count_ptr_digits(unsigned long n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n = n / 16;
		count++;
	}
	return (count);
}

static void	ft_putptr_fd(unsigned long n, int fd)
{
	char	*base;

	base = "0123456789abcdef";
	if (n >= 16)
		ft_putptr_fd(n / 16, fd);
	write(fd, &base[n % 16], 1);
}

int	ft_print_pointer(void *ptr)
{
	unsigned long	address;
	int				len;

	address = (unsigned long)ptr;
	if (ptr == NULL)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	write(1, "0x", 2);
	ft_putptr_fd(address, 1);
	len = ft_count_ptr_digits(address);
	return (len + 2);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danoguer <danoguer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:29:18 by danoguer          #+#    #+#             */
/*   Updated: 2025/04/28 17:55:08 by danoguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_count_hex_digits(unsigned int n)
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

static void	ft_puthex_fd(unsigned int n, int fd, int uppercase)
{
	char	*base;

	if (uppercase)
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	if (n >= 16)
		ft_puthex_fd(n / 16, fd, uppercase);
	write(fd, &base[n % 16], 1);
}

int	ft_print_hex(unsigned int n, int uppercase)
{
	ft_puthex_fd(n, 1, uppercase);
	return (ft_count_hex_digits(n));
}

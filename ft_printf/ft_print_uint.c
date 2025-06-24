/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_uint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danoguer <danoguer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:29:30 by danoguer          #+#    #+#             */
/*   Updated: 2025/05/01 11:55:02 by danoguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_count_udigits(unsigned int n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

int	ft_print_uint(unsigned int n)
{
	char	result;
	int		count;

	if (n == 2147483648)
	{
		write(1, "2147483648", 10);
		return (10);
	}
	if (n >= 10)
	{
		ft_print_uint(n / 10);
	}
	result = (n % 10) + '0';
	write(1, &result, 1);
	count = ft_count_udigits(n);
	return (count);
}

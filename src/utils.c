/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 20:43:43 by marvin            #+#    #+#             */
/*   Updated: 2025/06/23 20:43:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_putendl_fd(const char *s, int fd)
{
	if (!s)
		return;
	while (*s)
		write(fd, s++, 1);
	write(fd, "\n", 1);
}

char	*ft_strdup(const char *s)
{
	unsigned int	len;
	char			*copy;
	unsigned int	i;

	len = 0;
	while (s[len] != '\0')
		len++;
	copy = (char *)malloc(sizeof(char) * (len + 1));
	if (!copy)
		return (0);
	i = 0;
	while (i < len)
	{
		copy[i] = s[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

static size_t	intlen(long n)
{
	size_t	len;

	len = 1;
	if (n < 0)
	{
		len = 2;
		n = -n;
	}
	while (n > 9)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*result;
	int		sign;
	long	num;

	num = (long)n;
	sign = (num < 0);
	len = intlen(n);
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	result[len] = '\0';
	if (sign)
	{
		num = -num;
		result[0] = '-';
	}
	while (len > sign)
	{
		result[len - 1] = num % 10 + '0';
		num = num / 10;
		len--;
	}
	return (result);
}

bool	report_error(const char *message)
{
	ft_putendl_fd("Error\n", 2);
	ft_putendl_fd(message, 2);
	return (false);
}
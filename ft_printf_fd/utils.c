/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 15:34:25 by ncharbog          #+#    #+#             */
/*   Updated: 2024/12/19 11:12:13 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(int fd, char *s)
{
	int	i;

	i = 0;
	if (!s)
		s = "(null)";
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
	return (i);
}

int	ft_putchar(int fd, char c)
{
	write(fd, &c, 1);
	return (1);
}

int	ft_count(long long nb, char *base)
{
	unsigned int	count;
	unsigned int	i;

	i = 0;
	while (base[i])
		i++;
	count = 0;
	if (nb < 0)
	{
		nb = -nb;
		count++;
	}
	while (nb >= i)
	{
		nb = nb / i;
		count++;
	}
	return (count + 1);
}

int	ft_putnbr_base_fd(int fd, long long nbr, char *base)
{
	long long		nb;
	unsigned int	i;
	unsigned int	len;

	i = 0;
	while (base[i])
		i++;
	len = ft_count(nbr, base);
	if (nbr < 0)
	{
		write (fd, "-", 1);
		nb = nbr * -1;
	}
	else
		nb = nbr;
	if (nb >= i)
		ft_putnbr_base_fd(fd, nb / i, base);
	ft_putchar(fd, base[nb % i]);
	return (len);
}

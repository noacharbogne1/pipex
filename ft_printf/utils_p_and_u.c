/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_p_and_u.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 09:46:40 by ncharbog          #+#    #+#             */
/*   Updated: 2024/10/24 08:54:48 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_u(unsigned int nb, char *base)
{
	unsigned int	len;
	unsigned int	i;

	i = 0;
	while (base[i])
		i++;
	len = ft_count(nb, base);
	if (nb >= i)
		ft_putnbr_u(nb / i, base);
	ft_putchar(base[nb % i]);
	return (len);
}

int	ft_count_p(uint64_t nb, char *base)
{
	unsigned int	count;
	unsigned int	i;

	i = 0;
	while (base[i])
		i++;
	count = 0;
	while (nb >= i)
	{
		nb = nb / i;
		count++;
	}
	return (count + 1);
}

int	ft_putnbr_base_p(uint64_t nb, char *base)
{
	unsigned int	i;
	unsigned int	len;

	i = 0;
	while (base[i])
		i++;
	len = ft_count_p(nb, base);
	if (nb >= i)
		ft_putnbr_base(nb / i, base);
	ft_putchar(base[nb % i]);
	return (len);
}

int	ft_p(void *nb)
{
	unsigned int	len;
	uint64_t		adress;

	len = 0;
	adress = (uint64_t)nb;
	if (adress == 0)
		return (ft_putstr("(nil)"));
	len = ft_putstr("0x");
	len += ft_putnbr_base_p(adress, "0123456789abcdef");
	return (len);
}

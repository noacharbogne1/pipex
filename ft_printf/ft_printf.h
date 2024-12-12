/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:50:40 by ncharbog          #+#    #+#             */
/*   Updated: 2024/10/22 10:04:44 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdint.h>

int		ft_putstr(char *s);
int		ft_putchar(char c);
int		ft_printf(char const *format, ...);
int		ft_putnbr_base(long long nbr, char *base);
int		ft_putnbr_base_p(uint64_t nb, char *base);
int		ft_count(long long nb, char *base);
int		ft_count_p(uint64_t nb, char *base);
int		ft_putnbr_u(unsigned int nb, char *base);
int		ft_p(void *nb);

#endif
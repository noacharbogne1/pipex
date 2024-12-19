/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:50:40 by ncharbog          #+#    #+#             */
/*   Updated: 2024/12/19 10:53:14 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdint.h>

int		ft_putstr(int fd, char *s);
int		ft_putchar(int fd, char c);
int		ft_printf_fd(int fd, char const *format, ...);
int		ft_putnbr_base_fd(int fd, long long nbr, char *base);
int		ft_putnbr_base_p_fd(int fd, uint64_t nb, char *base);
int		ft_count(long long nb, char *base);
int		ft_count_p(uint64_t nb, char *base);
int		ft_putnbr_u_fd(int fd, unsigned int nb, char *base);
int		ft_p_fd(int fd, void *nb);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 09:20:11 by ncharbog          #+#    #+#             */
/*   Updated: 2024/12/19 15:52:31 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error(int flag, char *msg)
{
	if (flag == 1)
		ft_printf_fd(2, "Error: %s: %s\n", msg, strerror(errno));
	if (flag == 2)
		ft_printf_fd(2, "Error: %s\n", msg);
	if (flag == 3)
	{
		ft_printf_fd(2, "Error: %s: %s\n", msg, strerror(errno));
		free(msg);
	}
	exit(EXIT_FAILURE);
}

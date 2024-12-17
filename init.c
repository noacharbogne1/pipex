/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 09:34:15 by ncharbog          #+#    #+#             */
/*   Updated: 2024/12/17 09:34:45 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_init(t_data *data, char **argv, int argc)
{
	init_struct(data);
	if (access(argv[1], R_OK) == -1 || access(argv[1], W_OK) == -1)
		ft_free_error(NULL, FILE);
	if (access(argv[argc - 1], R_OK) == -1 || access(argv[argc - 1], W_OK) == -1)
		ft_free_error(NULL, FILE);
}

void	init_struct(t_data *data)
{
	data->fd = NULL;
	data->cmd = NULL;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 09:34:15 by ncharbog          #+#    #+#             */
/*   Updated: 2024/12/17 11:29:17 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_init(t_data *data, char **argv, int argc)
{
	init_struct(data);
	if (access(argv[1], R_OK) == -1 || access(argv[1], W_OK) == -1)
		ft_free_error(NULL, FILE);
}

void	init_struct(t_data *data)
{
	data->pipe_count = 0;
	data->cmd_count = 0;
	data->fd = NULL;
	data->cmd = NULL;
}

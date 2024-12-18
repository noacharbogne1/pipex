/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 09:34:15 by ncharbog          #+#    #+#             */
/*   Updated: 2024/12/18 17:47:01 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_init(t_data *data, char **argv)
{
	if (access(argv[1], R_OK) == -1 || access(argv[1], W_OK) == -1)
		ft_free_error(NULL, FILE);
	init_struct(data);
}

void	init_struct(t_data *data)
{
	data->pipe_count = 0;
	data->cmd_count = 0;
	data->infile = 0;
	data->outfile = 0;
	data->fd = NULL;
	data->cmd = NULL;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:03:04 by ncharbog          #+#    #+#             */
/*   Updated: 2024/12/13 16:20:29 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_exec(t_data *data, t_cmd *current, char **env)
{
	int		fd[2];
	__pid_t	p;

	if (pipe(fd) == -1)
		ft_free_error(data, PIPE);
	p = fork();
	if (p < 0)
		ft_free_error(data, FORK);
	else if (p > 0)
	{
		close(fd[0]);
	}
	if (execve(current->cmd, current->args, env) == -1)
		ft_free_error(data, EXEC);
}

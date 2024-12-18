/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:03:04 by ncharbog          #+#    #+#             */
/*   Updated: 2024/12/18 18:18:23 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	parent(t_data *data, int i)
{
	if (i > 0)
		close(data->fd[i - 1][0]);
	if (i < data->pipe_count)
		close(data->fd[i][1]);
}

void	child(t_data *data, t_cmd *current, char **env, int i)
{
	if (i > 0)
		dup2(data->fd[i - 1][0], STDIN_FILENO);
	if (i < data->pipe_count)
		dup2(data->fd[i][1], STDOUT_FILENO);
	if (i == 0)
		dup2(data->infile, STDIN_FILENO);
	if (i == data->pipe_count)
		dup2(data->outfile, STDOUT_FILENO);
	close_files(data);
	if (execve(current->cmd, current->args, env) == -1)
		ft_free_error(data, NULL);
}

void	ft_exec(t_data *data, char **env)
{
	t_cmd	*current;
	__pid_t	p;
	int		i;

	i = 0;
	current = data->cmd;
	while (current)
	{
		p = fork();
		if (p < 0)
			ft_free_error(data, FORK);
		else if (p > 0)
			parent(data, i);
		else
			child(data, current, env, i);
		i++;
		current = current->next;
	}
	while (wait(NULL) != -1)
		;
	close_files(data);
}

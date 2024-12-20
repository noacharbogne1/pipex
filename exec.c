/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:03:04 by ncharbog          #+#    #+#             */
/*   Updated: 2024/12/20 13:24:34 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	parent(int *fd)
{
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
}

void	child(t_data *data, t_cmd *current, char **env, int i, int *fd)
{
	if (data->infile == -1 && i == 0)
		close(STDIN_FILENO);
	if (i == data->cmd_count - 1)
	{
		close(fd[1]);
		close(fd[0]);
		dup2(data->outfile, STDOUT_FILENO);
	}
	else
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	close_files(data);
	if (execve(current->cmd, current->args, env) == -1)
		ft_free_all(data, ft_strdup(current->cmd), 3);
}

void	ft_exec(t_data *data, char **env)
{
	t_cmd	*current;
	int		fd[2];
	__pid_t	p;
	int		i;

	i = 0;
	current = data->cmd;
	if (data->infile == -1)
	{
		data->cmd_count--;
		current = current->next;
	}
	else
		dup2(data->infile, STDIN_FILENO);
	while (current)
	{
		if (pipe(fd) == -1)
			ft_free_all(data, PIPE, 2);
		p = fork();
		if (p < 0)
			ft_free_all(data, FORK, 1);
		else if (p == 0)
			child(data, current, env, i, fd);
		else
			parent(fd);
		i++;
		current = current->next;
	}
	while (wait(NULL) != -1)
		;
	close_files(data);
}

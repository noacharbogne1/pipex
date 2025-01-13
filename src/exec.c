/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:03:04 by ncharbog          #+#    #+#             */
/*   Updated: 2025/01/13 14:32:11 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	incorrect_infile(void)
{
	int	null;

	null = open("/dev/null", O_RDONLY);
	if (null != -1)
	{
		dup2(null, STDIN_FILENO);
		close(null);
	}
}

void	incorrect_outfile(void)
{
	int	null;

	null = open("/dev/null", O_WRONLY);
	if (null != -1)
	{
		dup2(null, STDOUT_FILENO);
		close(null);
	}
}

void	parent(t_data *data)
{
	close(data->fd[1]);
	dup2(data->fd[0], STDIN_FILENO);
	close(data->fd[0]);
}

void	child(t_data *data, t_cmd *current, char **env, int i)
{
	if (i == 0)
	{
		if (data->infile == -1)
			incorrect_infile();
		else
			dup2(data->infile, STDIN_FILENO);
	}
	if (i == data->cmd_count - 1)
	{
		close(data->fd[1]);
		close(data->fd[0]);
		if (data->outfile == -1)
			incorrect_outfile();
		dup2(data->outfile, STDOUT_FILENO);
	}
	else
	{
		close(data->fd[0]);
		dup2(data->fd[1], STDOUT_FILENO);
		close(data->fd[1]);
	}
	close_files(data);
	if (execve(current->cmd, current->args, env) == -1)
		ft_free_all(data, ft_strdup(current->cmd), 3);
}

void	ft_exec(t_data *data, char **env, t_cmd *current)
{
	__pid_t	p;
	int		i;

	i = 0;
	while (current && i < data->cmd_count)
	{
		if (pipe(data->fd) == -1)
			ft_free_all(data, PIPE, 2);
		p = fork();
		if (p < 0)
			ft_free_all(data, FORK, 1);
		else if (p == 0)
			child(data, current, env, i);
		else
			parent(data);
		i++;
		current = current->next;
	}
	while (wait(NULL) != -1)
		;
	close_files(data);
}

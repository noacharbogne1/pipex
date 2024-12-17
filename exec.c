/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:03:04 by ncharbog          #+#    #+#             */
/*   Updated: 2024/12/17 10:27:47 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_exec(t_data *data, int argc, char **argv, char **env)
{
	t_cmd	*current;
	int		i;
	int		infile;
	int		outfile;
	__pid_t	p;

	i = 0;
	current = data->cmd;
	infile = open(argv[1], O_RDONLY);
	if (infile == -1)
		ft_free_error(data, FILE);
	outfile = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (outfile == -1)
		ft_free_error(data, FILE);
	while (current)
	{
		p = fork();
		if (p < 0)
			ft_free_error(data, FORK);
		else if (p > 0) // parent : cmd2
		{
			if (i > 0)
				close(data->fd[i - 1][0]);
			if (i < data->pipe_count)
				close(data->fd[i][1]);
			waitpid(p, NULL, 0);
		}
		else // child : cmd1
		{
			if (i > 0)
				dup2(data->fd[i - 1][0], STDIN_FILENO);
			if (i < data->pipe_count)
				dup2(data->fd[i][1], STDOUT_FILENO);
			if (i == 0)
				dup2(infile, STDIN_FILENO);
			if (i == data->pipe_count)
				dup2(outfile, STDOUT_FILENO);
			if (execve(current->cmd, current->args, env) == -1)
				ft_free_error(data, EXEC);
		}
		i++;
		current = current->next;
	}
	close(infile);
	close(outfile);
	i = 0;
	while (i < data->pipe_count)
	{
		close(data->fd[i][0]);
		close(data->fd[i][1]);
		i++;
	}
}

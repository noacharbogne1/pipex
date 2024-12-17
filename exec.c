/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:03:04 by ncharbog          #+#    #+#             */
/*   Updated: 2024/12/17 09:08:12 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_exec(t_data *data, t_cmd *current, char **argv, char **env)
{
	int		fd[2];
	int		infile;
	int		outfile;
	__pid_t	p;

	infile = open(argv[1], O_RDONLY);
	if (infile == -1)
		ft_free_error(data, FILE);
	outfile = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (outfile == -1)
		ft_free_error(data, FILE);
	if (pipe(fd) == -1)
		ft_free_error(data, PIPE);
	p = fork();
	if (p < 0)
		ft_free_error(data, FORK);
	else if (p > 0) // parent : cmd2
	{
		close(fd[1]);
		waitpid(p, NULL, 0);
		dup2(outfile, STDOUT_FILENO);
		dup2(fd[0],STDIN_FILENO);
		close(fd[0]);
		if (execve(current->next->cmd, current->next->args, env) == -1)
			ft_free_error(data, EXEC);
	}
	else // child : cmd1
	{
		close(fd[0]);
		dup2(infile, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		if (execve(current->cmd, current->args, env) == -1)
			ft_free_error(data, EXEC);
	}
	close(infile);
	close(outfile);
}

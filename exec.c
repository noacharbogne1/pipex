/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:03:04 by ncharbog          #+#    #+#             */
/*   Updated: 2024/12/16 16:49:16 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_exec(t_data *data, t_cmd *current, char **argv, char **env)
{
	int		fd_parent[2];
	int		fd_child[2];
	int		infile;
	int		outfile;
	__pid_t	p;

	infile = open(argv[1], O_RDONLY);
	outfile = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pipe(fd_parent) == -1)
		ft_free_error(data, PIPE);
	if (pipe(fd_child) == -1)
		ft_free_error(data, PIPE);
	p = fork();
	if (p < 0)
		ft_free_error(data, FORK);
	else if (p > 0) // parent : cmd2
	{
		waitpid(p, NULL, 0);
		close(fd_parent[1]);
		dup2(outfile, STDOUT_FILENO);
		dup2(fd_child[0],STDIN_FILENO);
		if (execve(current->next->cmd, current->next->args, env) == -1)
			ft_free_error(data, EXEC);
		close(fd_child[0]);
	}
	else // child : cmd1
	{
		close(fd_child[0]);
		dup2(infile, STDIN_FILENO);
		dup2(fd_parent[1], STDOUT_FILENO);
		close (fd_child[1]);
		if (execve(current->cmd, current->args, env) == -1)
			ft_free_error(data, EXEC);
	}
	close(infile);
	close(outfile);
}

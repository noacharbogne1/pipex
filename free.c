/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 08:59:19 by ncharbog          #+#    #+#             */
/*   Updated: 2024/12/20 12:22:08 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_files(t_data *data)
{
	int	i;

	i = 0;
	if (data->infile != -1)
	{
		close(data->infile);
		data->infile = -1;
	}
	if (data->outfile != -1)
	{
		close(data->outfile);
		data->outfile = -1;
	}
	/*if (data->fd[0] != -1)
	{
		close(data->fd[0]);
		data->fd[0] = -1;
	}
	if (data->fd[1] != -1)
	{
		close(data->fd[1]);
		data->fd[1] = -1;
	}*/
}

void	ft_free_lst(t_cmd **head)
{
	t_cmd	*current;
	t_cmd	*next_node;

	current = *head;
	next_node = NULL;
	while (current)
	{
		next_node = current->next;
		free(current->cmd);
		current->cmd = NULL;
		if (current->args)
			ft_free_tab_char(current->args);
		current->args = NULL;
		free(current);
		current = next_node;
	}
}

void	ft_free_tab_char(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
	tab = NULL;
}

void	ft_free_tab_int(int **tab, int cmd)
{
	int	i;

	i = 0;
	while (i < cmd - 1)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
}

void	ft_free_all(t_data *data, char *msg, int flag)
{
	if (data && flag > 0)
	{
		close_files(data);
		if (data->cmd)
			ft_free_lst(&data->cmd);
	}
	if (msg && flag == 0)
	{
		ft_printf_fd(2, "Error : %s\n", msg);
		return ;
	}
	if (flag > 0)
		ft_error(flag, msg);
	exit(EXIT_SUCCESS);
}

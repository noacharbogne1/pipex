/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 10:24:08 by ncharbog          #+#    #+#             */
/*   Updated: 2024/12/18 09:48:05 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_files(t_data *data)
{
	int	i;

	i = 0;
	close(data->infile);
	close(data->outfile);
	while (i < data->pipe_count)
	{
		close(data->fd[i][0]);
		close(data->fd[i][1]);
		i++;
	}
}

void ft_free_lst(t_cmd **head)
{
	t_cmd *current;
	t_cmd *next_node;

	current = *head;
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

void	ft_free_error(t_data *data, char *msg)
{
	int	i;

	i = 0;
	if (data)
	{
		close_files(data);
		if (data->cmd)
			ft_free_lst(&data->cmd);
		if (data->fd)
			ft_free_tab_int(data->fd, data->cmd_count);
	}
	if (msg)
	{
		ft_printf("Error : %s\n", msg);
		exit(EXIT_FAILURE);
	}
	exit(0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 08:59:19 by ncharbog          #+#    #+#             */
/*   Updated: 2025/01/10 11:50:26 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

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

void	ft_free_all(t_data *data, char *msg, int flag)
{
	if (data)
	{
		close_files(data);
		if (data->cmd)
			ft_free_lst(&data->cmd);
	}
	if (flag == 4)
	{
		ft_printf_fd(2, "Error: %s: %s\n", msg, strerror(errno));
		return ;
	}
	if (flag == 0)
	{
		ft_printf_fd(2, "Error: %s\n", msg);
		exit(EXIT_FAILURE);
	}
	if (flag > 0)
		ft_error(flag, msg);
	exit(EXIT_SUCCESS);
}

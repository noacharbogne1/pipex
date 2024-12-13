/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 10:24:08 by ncharbog          #+#    #+#             */
/*   Updated: 2024/12/13 11:15:02 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


void	ft_init(t_data *data, char **argv, int argc)
{
	if (access(argv[1], R_OK) == -1 || access(argv[1], W_OK) == -1)
		ft_free_error(NULL, FILE);
	if (access(argv[argc - 1], R_OK) == -1 || access(argv[argc - 1], W_OK) == -1)
		ft_free_error(NULL, FILE);
	// // data->cmd = malloc((argc - 2) * sizeof(char *));
	// if (!data->cmd)
	// 	ft_free_error(NULL, INIT);
	init_struct(data);
}

void	init_struct(t_data *data)
{
	data->cmd = NULL;
}

void	ft_free_lst(t_cmd **head)
{
	t_cmd	*current;

	current = (*head);
	while (*head)
	{
		current = (*head);
		free(current->cmd);
		current->cmd = NULL;
		if (current->args)
			ft_free_tab(current->args);
		(*head) = (*head)->next;
		free(current);
		if ((*head)->next == NULL)
			break;
	}
	free((*head));
}

void	ft_free_tab(char **tab)
{
	int	i;
	i = 0;
	while (tab[i])
		i++;
	while (i--)
		free(tab[i]);
	free(tab);
	tab = NULL;
}

void	ft_free_error(t_data *data, char *msg)
{
	if (data)
	{
		if (data->cmd)
			ft_free_lst(&data->cmd);
		free(data->cmd);
	}
	if (msg)
	{
		ft_printf("Error : %s\n", msg);
		exit(EXIT_FAILURE);
	}
	exit(0);
}

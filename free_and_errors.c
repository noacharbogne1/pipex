/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 10:24:08 by ncharbog          #+#    #+#             */
/*   Updated: 2024/12/12 17:03:31 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_lst(t_cmd **head)
{
	while ((*head))
	{
		free((*head)->cmd);
		if ((*head)->param)
			ft_free_tab((*head)->param);
		(*head) = (*head)->next;
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
}

void	ft_free_error(t_data *data, char *msg)
{
	if (data)
	{
		if (data->file1)
			free(data->file1);
		if (data->file2)
			free(data->file2);
		if (data->path)
			ft_free_tab(data->path);
		if (data->cmd)
			ft_free_lst(&data->cmd);
	}
	if (msg)
	{
		ft_printf("Error : %s\n", msg);
		exit(EXIT_FAILURE);
	}
	exit(0);
}
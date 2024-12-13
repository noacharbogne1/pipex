/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 10:24:08 by ncharbog          #+#    #+#             */
/*   Updated: 2024/12/13 08:53:03 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_init(t_data *data, char **argv, int argc)
{
	if (access(argv[1], R_OK) == -1 || access(argv[1], W_OK) == -1)
		ft_free_error(NULL, FILE);
	if (access(argv[argc - 1], R_OK) == -1 || access(argv[argc - 1], W_OK) == -1)
		ft_free_error(NULL, FILE);
	data->cmd = malloc((argc - 2) * sizeof(char *));
	if (!data->cmd)
		ft_free_error(NULL, INIT);
}

void	init_struct(t_data *data)
{
	data->cmd = NULL;
	data->args = NULL;
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
			ft_free_tab(data->cmd);
		if (data->args)
			ft_free_tab(data->args);
	}
	if (msg)
	{
		ft_printf("Error : %s\n", msg);
		exit(EXIT_FAILURE);
	}
	exit(0);
}
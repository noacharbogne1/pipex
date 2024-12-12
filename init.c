/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 11:30:28 by ncharbog          #+#    #+#             */
/*   Updated: 2024/12/12 16:01:10 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_init_argv(t_data *data, int argc, char **argv)
{
	int		i;
	char	*dup;

	i = 2;
	data->file1 = ft_strdup(argv[1]);
	if (!data->file1)
		ft_free_error(data, INIT);
	data->file2 = ft_strdup(argv[argc - 1]);
	if (!data->file2)
			ft_free_error(data, INIT);
	while (i < argc - 1)
	{
		dup = ft_strdup(argv[i]);
		if (!data->cmd)
		{
			data->cmd = ft_lstnew2(dup);
			if (!data->cmd)
			{
				free(dup);
				ft_free_error(data, INIT);
			}
		}
		else
			ft_lstadd_back2(&(data->cmd), ft_lstnew2(dup));
		free(dup);
		dup = NULL;
		i++;
	}
}

void	init_structs(t_data *data)
{
	data->file1 = NULL;
	data->file2 = NULL;
	data->path = NULL;
	data->cmd = NULL;
}

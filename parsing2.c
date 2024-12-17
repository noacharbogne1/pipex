/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:51:33 by ncharbog          #+#    #+#             */
/*   Updated: 2024/12/17 09:37:21 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_parse_args(t_data *data, char **argv, int argc)
{
	t_cmd	*tmp;
	int		i;

	i = 2;
	tmp = data->cmd;
	while (i < argc - 1)
	{
		tmp->args = ft_split(argv[i], ' ');
		tmp = tmp->next;
		i++;
	}
}

void	pipes(t_data *data, int argc)
{
	int	i;

	i = 0;
	data->fd = malloc((argc - 4) * sizeof (int *));
	if (!data->fd)
		ft_free_error(data, PIPE);
	while (i < argc - 4)
	{
		if (pipe(data->fd[i]) == -1)
			ft_free_error(data, PIPE);
	}
}
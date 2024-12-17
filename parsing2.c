/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:51:33 by ncharbog          #+#    #+#             */
/*   Updated: 2024/12/17 17:25:57 by ncharbog         ###   ########.fr       */
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
		data->fd[i] = malloc(2 * sizeof(int));
		if (!data->fd[i])
			ft_free_error(data, PIPE);
		if (pipe(data->fd[i]) == -1)
			ft_free_error(data, PIPE);
		i++;
	}
	data->pipe_count = i;
}

void	files(t_data *data, char **argv, int argc)
{
	data->infile = open(argv[1], O_RDONLY);
	if (data->infile == -1)
		ft_free_error(data, FILE);
	data->outfile = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (data->outfile == -1)
		ft_free_error(data, FILE);
}

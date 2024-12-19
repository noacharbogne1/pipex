/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:24:27 by ncharbog          #+#    #+#             */
/*   Updated: 2024/12/19 09:35:11 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_parse_args(t_data *data, char **argv)
{
	t_cmd	*tmp;
	int		i;

	i = 2;
	tmp = data->cmd;
	while (i < data->cmd_count + 2)
	{
		tmp->args = ft_split(argv[i], ' ');
		tmp = tmp->next;
		i++;
	}
}

void	pipes(t_data *data)
{
	int	i;

	i = 0;
	data->fd = malloc((data->cmd_count) * sizeof (int *));
	if (!data->fd)
		ft_free_all(data, PIPE, 1);
	while (i < data->cmd_count - 1)
	{
		data->fd[i] = malloc(2 * sizeof(int));
		if (!data->fd[i])
			ft_free_all(data, PIPE, 1);
		if (pipe(data->fd[i]) == -1)
			ft_free_all(data, PIPE, 1);
		i++;
	}
	data->pipe_count = i;
}

void	files(t_data *data, char **argv, int argc)
{
	data->infile = open(argv[1], O_RDONLY);
	if (data->infile == -1)
		ft_free_all(data, FILE1, 1);
	data->outfile = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (data->outfile == -1)
		ft_free_all(data, FILE2, 1);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	init_struct(&data);
	if (argc >= 5)
	{
		ft_init(&data, argv);
		ft_parse_cmds(&data, argv, env, argc);
		ft_parse_args(&data, argv);
		if (data.cmd_count > 1)
			pipes(&data);
		files(&data, argv, argc);
		ft_exec(&data, env);
		ft_free_all(&data, NULL, 0);
		return (1);
	}
	ft_free_all(NULL, ARGC, 1);
	return (0);
}

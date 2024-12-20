/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:24:27 by ncharbog          #+#    #+#             */
/*   Updated: 2024/12/20 09:13:07 by ncharbog         ###   ########.fr       */
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

void	files(t_data *data, char **argv, int argc)
{
	data->infile = open(argv[1], O_RDONLY);
	if (data->infile == -1)
		ft_free_all(data, FILE1, 0);
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
		init_struct(&data);
		ft_parse_cmds(&data, argv, env, argc);
		ft_parse_args(&data, argv);
		files(&data, argv, argc);
		ft_exec(&data, env);
		ft_free_all(&data, NULL, 0);
		return (1);
	}
	ft_free_all(NULL, ARGC, 0);
	return (0);
}

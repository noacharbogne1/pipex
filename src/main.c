/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 13:45:28 by ncharbog          #+#    #+#             */
/*   Updated: 2024/12/20 16:08:41 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	t_cmd	*current;

	init_struct(&data);
	current = NULL;
	if (argc >= 5)
	{
		init_struct(&data);
		ft_parse_cmds(&data, argv, env, argc);
		ft_parse_args(&data, argv);
		files(&data, argv, argc);
		current = data.cmd;
		if (data.infile == -1)
		{
			data.cmd_count--;
			current = current->next;
		}
		else
			dup2(data.infile, STDIN_FILENO);
		ft_exec(&data, env, current);
		ft_free_all(&data, NULL, 0);
		return (1);
	}
	ft_free_all(NULL, ARGC, 0);
	return (0);
}

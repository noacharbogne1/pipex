/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 13:45:28 by ncharbog          #+#    #+#             */
/*   Updated: 2025/01/13 15:20:31 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	t_cmd	*current;

	init_struct(&data);
	current = NULL;
	if (argc >= 5)
	{
		ft_parse_cmds(&data, argv, env, argc);
		ft_parse_args(&data, argv);
		files(&data, argv, argc);
		current = data.cmd;
		if (data.infile == -1)
			data.cmd_count--;
		if (data.outfile == -1)
			data.cmd_count--;
		if (data.infile == -1)
			current = current->next;
		ft_exec(&data, env, current);
		ft_free_all(&data, NULL, -1);
		return (0);
	}
	ft_free_all(NULL, ARGC, 0);
	return (1);
}

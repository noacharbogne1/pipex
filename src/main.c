/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 13:45:28 by ncharbog          #+#    #+#             */
/*   Updated: 2024/12/20 13:53:32 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

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
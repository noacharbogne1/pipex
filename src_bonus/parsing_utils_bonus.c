/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 13:43:57 by ncharbog          #+#    #+#             */
/*   Updated: 2025/01/10 11:12:08 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

char	*path_not_found(char *filename, char *cmd)
{
	free(filename);
	return (ft_strdup(cmd));
}

void	init_struct(t_data *data)
{
	data->cmd_count = 0;
	data->infile = 0;
	data->outfile = 0;
	data->cmd = NULL;
}

void	files(t_data *data, char **argv, int argc)
{
	data->infile = open(argv[1], O_RDONLY);
	if (data->infile == -1)
		ft_free_all(NULL, FILE1, 4);
	data->outfile = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (data->outfile == -1)
	{
		if (errno == EACCES)
			ft_free_all(NULL, FILE2, 4);
	}
}

char	*skip_spaces(char *cmd)
{
	int		start;
	int		end;

	start = 0;
	while (cmd[start] && cmd[start] == ' ')
		start++;
	end = start;
	while (cmd[end] && cmd[end] != ' ')
		end++;
	return (ft_substr(cmd, start, (end - start)));
}

void	ft_error(int flag, char *msg)
{
	if (flag == 1)
		ft_printf_fd(2, "Error: %s: %s\n", msg, strerror(errno));
	if (flag == 2)
		ft_printf_fd(2, "Error: %s\n", msg);
	if (flag == 3)
	{
		ft_printf_fd(2, "Error: %s: %s\n", msg, strerror(errno));
		free(msg);
	}
	exit(EXIT_FAILURE);
}

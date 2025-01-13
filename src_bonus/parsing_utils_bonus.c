/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 13:43:57 by ncharbog          #+#    #+#             */
/*   Updated: 2025/01/13 15:20:21 by ncharbog         ###   ########.fr       */
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
	if (ft_strncmp(argv[1], argv[argc - 1], ft_strlen(argv[1])) == 0)
	{
		data->infile = open(argv[1], O_RDONLY);
		if (data->infile == -1)
			ft_free_all(NULL, FILE1, 4);
		data->outfile = open(argv[1], O_RDWR | O_APPEND, 0644);
		if (data->outfile == -1)
			ft_free_all(NULL, FILE2, 4);
	}
	else
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
	char	*error;
	char	*tmp;

	error = ft_strjoin("Error: ", msg);
	if (flag == 1 || flag == 3)
	{
		tmp = error;
		error = ft_strjoin(error, ": ");
		free(tmp);
		tmp = error;
		error = ft_strjoin(error, strerror(errno));
		free(tmp);
	}
	tmp = error;
	error = ft_strjoin(error, "\n");
	free(tmp);
	write(2, error, ft_strlen(error));
	free(error);
	if (flag == 3)
		free(msg);
	exit(EXIT_FAILURE);
}

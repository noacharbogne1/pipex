/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:24:27 by ncharbog          #+#    #+#             */
/*   Updated: 2024/12/12 17:03:35 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**add_slash(char **path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		path[i] = ft_strjoin(path[i], "/");
		i++;
	}
	return (path);
}

void	get_path(t_data *data, char **env)
{
	char	*str;
	char	**tmp;
	int		line;
	int		i;

	i = 0;
	line = -1;
	str = malloc(280 * sizeof(char));
	if (!str)
		ft_free_error(data, INIT);
	while (env[i])
	{
		line = ft_strncmp(env[i], "PATH=", 5);
		if (line == 0)
			break;
		i++;
	}
	if (line != 0)
		ft_free_error(data, PATH);
	str = ft_strtrim(env[i], "PATH=");
	tmp = ft_split(str, ':');
	data->path = add_slash(tmp);
	ft_free_tab(tmp);
	free(str);
	if (!data->path)
		ft_free_error(data, INIT);
}

int	get_cmd(t_data *data, char *cmd)
{
	char	*filename;
	t_cmd	*cmd_node;
	int		i;
	int		a;

	i = 0;
	a = -1;
	cmd_node = data->cmd;
	while (data->path[i])
	{
		filename = ft_strjoin(data->path[i], cmd);
		a = access(filename, X_OK);
		if (a == 0)
			break;
		free(filename);
		filename = NULL;
		i++;
	}
	if (a != 0)
		return (0);
	while (cmd_node->cmd != cmd)
		cmd_node = cmd_node->next;
	cmd_node->cmd = filename;
	return (1);
}

void	ft_check_args(t_data *data, int argc, char **env)
{
	int		n_cmd;
	t_cmd	*cmd_node;

	n_cmd = 2;
	cmd_node = data->cmd;
	if (access(data->file1, R_OK) == -1 || access(data->file1, W_OK) == -1)
		ft_free_error(data, FILE);
	if (access(data->file2, R_OK) == -1 || access(data->file2, W_OK) == -1)
		ft_free_error(data, FILE);
	while (n_cmd < argc - 1 && cmd_node->cmd)
	{
		if (access(cmd_node->cmd, X_OK) == -1)
		{
			if (data->path == NULL)
			get_path(data, env);
			if (!get_cmd(data, cmd_node->cmd))
				ft_free_error(data, CMD);
		}
		n_cmd++;
		cmd_node = cmd_node->next;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	init_structs(&data);
	if (argc == 5)
	{
		ft_init_argv(&data, argc, argv);
		ft_check_args(&data, argc, env);
		ft_free_error(&data, NULL);
		return (1);
	}
	ft_free_error(&data, ARGC);
	return (0);
}

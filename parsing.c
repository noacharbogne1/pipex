/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:24:27 by ncharbog          #+#    #+#             */
/*   Updated: 2024/12/13 08:55:30 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_path(t_data *data, char **env)
{
	char	*str;
	char	**path;
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			break;
		i++;
	}
	if (env[i] == NULL)
		ft_free_error(data, PATH);
	str = ft_strtrim(env[i], "PATH=");
	path = ft_split(str, ':');
	free(str);
	str = NULL;
	if (!path)
		ft_free_error(data, INIT);
	return (path);
}

char	*get_pathname(char *cmd, char *path)
{
	char	*buf;
	char	*pathname;

	buf = ft_strjoin(path, "/");
	pathname = ft_strjoin(buf, cmd);
	free(buf);
	buf = NULL;
	return (pathname);
}

char	*get_cmd(t_data *data, char **env, char *cmd)
{
	char	*filename;
	char	**path;
	int		i;
	int		a;

	i = 0;
	a = -1;
	path = get_path(data, env);
	while (path[i])
	{
		filename = get_pathname(cmd, path[i]);
		a = access(filename, X_OK);
		if (a == 0)
			break;
		free(filename);
		filename = NULL;
		i++;
	}
	if (a != 0)
		return (0);
	ft_free_tab(path);
	path = NULL;
	return (filename);
}

void	ft_parse_cmds(t_data *data, char **argv, char **env, int argc)
{
	int	i;
	int	n_cmd;

	i = 0;
	n_cmd = 2;
	while (n_cmd < argc - 1)
	{
		if (access(argv[n_cmd], X_OK) == -1)
			data->cmd[i] = get_cmd(data, env, argv[n_cmd]);
		else
			data->cmd[i] = ft_strdup(argv[n_cmd]);
		if (!data->cmd[i])
			ft_free_error(data, CMD);
		n_cmd++;
		i++;
	}
	data->cmd[i] = 0;
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	init_struct(&data);
	if (argc == 5)
	{
		ft_init(&data, argv, argc);
		ft_parse_cmds(&data, argv, env, argc);
		//ft_parse_args;
		int i = 0;
		while (data.cmd[i])
		{
			ft_printf("%s\n", data.cmd[i]);
			i++;
		}
		ft_free_error(&data, NULL);
		return (1);
	}
	ft_free_error(NULL, ARGC);
	return (0);
}

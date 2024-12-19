/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 09:25:01 by ncharbog          #+#    #+#             */
/*   Updated: 2024/12/19 08:57:38 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_path(t_data *data, char **env)
{
	char	*str;
	char	**path;
	int		i;

	i = 0;
	path = NULL;
	str = NULL;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	if (env[i] == NULL)
		ft_free_all(data, PATH, 1);
	str = ft_strtrim(env[i], "PATH=");
	path = ft_split(str, ':');
	free(str);
	if (!path)
		ft_free_all(data, PATH, 1);
	return (path);
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

char	*get_pathname(char *cmd, char *path)
{
	char	*buf;
	char	*pathname;

	buf = ft_strjoin(path, "/");
	pathname = ft_strjoin(buf, cmd);
	free(buf);
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
	filename = NULL;
	while (path[i])
	{
		filename = get_pathname(cmd, path[i]);
		a = access(filename, X_OK);
		if (a == 0)
			break ;
		free(filename);
		filename = NULL;
		i++;
	}
	ft_free_tab_char(path);
	if (a != 0)
	{
		free(filename);
		return (ft_strdup(cmd));
	}
	return (filename);
}

void	ft_parse_cmds(t_data *data, char **argv, char **env, int argc)
{
	t_cmd	*tmp;
	char	*dup;
	char	*only_cmd;
	int		n_cmd;

	n_cmd = 2;
	dup = NULL;
	tmp = NULL;
	only_cmd = NULL;
	while (n_cmd < argc - 1)
	{
		only_cmd = skip_spaces(argv[n_cmd]);
		if (access(only_cmd, X_OK) == -1)
			dup = get_cmd(data, env, only_cmd);
		else
			dup = ft_strdup(only_cmd);
		tmp = ft_lstnew2(dup);
		ft_lstadd_back2(&(data->cmd), tmp);
		free(only_cmd);
		n_cmd++;
	}
	data->cmd_count = ft_lstsize2(data->cmd);
}

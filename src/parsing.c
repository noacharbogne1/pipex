/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:24:27 by ncharbog          #+#    #+#             */
/*   Updated: 2025/01/15 13:38:48 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

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

char	**get_path(char **env)
{
	char	*str;
	char	**path;
	int		i;

	i = 0;
	if (!env)
		return (NULL);
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	str = ft_strtrim(env[i], "PATH=");
	path = ft_split(str, ':');
	if (str)
		free(str);
	return (path);
}

char	*get_pathname(char *cmd, char *path)
{
	char	*buf;
	char	*pathname;

	buf = ft_strjoin(path, "/");
	pathname = ft_strjoin(buf, cmd);
	if (buf)
		free(buf);
	return (pathname);
}

char	*get_cmd(char **env, char *cmd)
{
	char	*filename;
	char	**path;
	int		i;
	int		a;

	i = 0;
	a = -1;
	path = get_path(env);
	if (!path)
		return (ft_strdup(cmd));
	filename = NULL;
	while (path[i])
	{
		filename = get_pathname(cmd, path[i++]);
		a = access(filename, X_OK);
		if (a == 0)
			break ;
		if (filename)
			free(filename);
		filename = NULL;
	}
	ft_free_tab_char(path);
	if (a != 0)
		return (path_not_found(filename, cmd));
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
		dup = get_cmd(env, only_cmd);
		tmp = ft_lstnew2(dup);
		ft_lstadd_back2(&(data->cmd), tmp);
		if (only_cmd)
			free(only_cmd);
		n_cmd++;
	}
	data->cmd_count = ft_lstsize2(data->cmd);
}

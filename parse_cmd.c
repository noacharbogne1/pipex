/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 09:25:01 by ncharbog          #+#    #+#             */
/*   Updated: 2024/12/18 15:39:33 by ncharbog         ###   ########.fr       */
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
	return(ft_substr(cmd, start, (end - start)));
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
	ft_free_tab_char(path);
	if (a != 0)
	{
		free(filename);
		return (NULL);
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
	only_cmd = NULL;
	while (n_cmd < argc - 1)
	{
		only_cmd = skip_spaces(argv[n_cmd]);
		if (access(only_cmd, X_OK) == -1)
			dup = get_cmd(data, env, only_cmd);
		else
			dup = ft_strdup(only_cmd);
		if (!dup)
			ft_printf("Error : command doesn't exist");
		else
		{
			tmp = ft_lstnew2(dup);
			ft_lstadd_back2(&(data->cmd), tmp);
			tmp->pos = n_cmd;
		}
		free(only_cmd);
		n_cmd++;
	}
	data->cmd_count = ft_lstsize2(data->cmd);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:24:27 by ncharbog          #+#    #+#             */
/*   Updated: 2024/12/13 11:19:52 by ncharbog         ###   ########.fr       */
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
	char	*dest;
	int		start;
	int		end;
	int		i;

	i = 0;
	start = 0;
	end = 0;
	while (cmd[i] && cmd[i] == ' ')
		i++;
	if (cmd[i] && cmd[i] != ' ')
	{
		start = i;
		while (cmd[i] && cmd[i] != ' ')
			i++;
	}
	if (cmd[i] && cmd[i] == ' ')
		end = i;
	if (end == 0 && start == 0)
		end = ft_strlen(cmd) - 1;
	dest = malloc((end - start + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	i = 0;
	while(dest[i] && i < (end - start))
	{
		dest[i] = cmd[start];
		i++;
		start++;
	}
	dest[i] = '\0';
	free(cmd);
	return(dest);
}

char	*get_pathname(char *cmd, char *path)
{
	char	*buf;
	char	*pathname;
	//char	*only_cmd;

	//only_cmd = skip_spaces(cmd);
	buf = ft_strjoin(path, "/");
	pathname = ft_strjoin(buf, cmd);
	free(buf);
	buf = NULL;
	//free(only_cmd);
	//only_cmd = NULL;
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
	t_cmd	*tmp;
	char	*dup;
	int		n_cmd;

	n_cmd = 2;
	while (n_cmd < argc - 1)
	{
		if (access(argv[n_cmd], X_OK) == -1)
			dup = get_cmd(data, env, argv[n_cmd]);
		else
			dup = ft_strdup(argv[n_cmd]);
		tmp = ft_lstnew2(dup);
		if (!tmp)
			ft_free_error(data, CMD);
		ft_lstadd_back2(&(data->cmd), tmp);
		n_cmd++;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	t_cmd *current;

	init_struct(&data);
	current = NULL;
	if (argc == 5)
	{
		ft_init(&data, argv, argc);
		ft_parse_cmds(&data, argv, env, argc);
		//ft_parse_args;
		current = data.cmd;
		while (current)
		{
			ft_printf("%s\n", current->cmd);
			current = current->next;
		}
		ft_free_error(&data, NULL);
		return (1);
	}
	ft_free_error(NULL, ARGC);
	return (0);
}

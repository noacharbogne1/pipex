/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:25:57 by ncharbog          #+#    #+#             */
/*   Updated: 2024/12/18 09:26:49 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include "macros.h"
# include "ft_printf/ft_printf.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_data
{
	int		pipe_count;
	int		cmd_count;
	int		infile;
	int		outfile;
	int		**fd;
	t_cmd	*cmd;
}	t_data;

// parse_cmd.c
void	ft_parse_cmds(t_data *data, char **argv, char **env, int argc);
char	*get_cmd(t_data *data, char **env, char *cmd);
char	**get_path(t_data *data, char **env);
char	*get_pathname(char *cmd, char *path);
char	*skip_spaces(char *cmd);

// parsing.c
void	ft_parse_args(t_data *data, char **argv, int argc);
void	pipes(t_data *data, int argc);
void	files(t_data *data, char **argv, int argc);

// free_and_errors.c
void	ft_free_error(t_data *data, char *msg);
void	ft_free_tab_char(char **tab);
void	ft_free_tab_int(int **tab, int cmd);
void	ft_free_lst(t_cmd **head);
void	close_files(t_data *data);

// init.c
void	init_struct(t_data *data);
void	ft_init(t_data *data, char **argv);

// libft_modified.c
void	ft_lstadd_back2(t_cmd **lst, t_cmd *new);
t_cmd	*ft_lstnew2(void *content);

// exec.c
void	ft_exec(t_data *data, char **env);
void	parent(t_data *data, int i);
void	child(t_data *data, t_cmd *current, char **env, int i);

#endif
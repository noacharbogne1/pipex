/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:25:57 by ncharbog          #+#    #+#             */
/*   Updated: 2025/01/13 10:56:12 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/libft.h"
# include "macros_bonus.h"
# include "../ft_printf_fd/ft_printf.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_data
{
	int		fd[2];
	int		cmd_count;
	int		infile;
	int		outfile;
	t_cmd	*cmd;
}	t_data;

// exec_bonus.c
void	ft_exec(t_data *data, char **env, t_cmd *current);
void	parent(t_data *data);
void	child(t_data *data, t_cmd *current, char **env, int i);
void	incorrect_infile(void);
void	incorrect_outfile(void);

// free_bonus.c
void	ft_free_all(t_data *data, char *msg, int flag);
void	ft_free_tab_char(char **tab);
void	ft_free_lst(t_cmd **head);
void	close_files(t_data *data);

// libft_modified_bonus.c
void	ft_lstadd_back2(t_cmd **lst, t_cmd *new);
t_cmd	*ft_lstnew2(void *content);
int		ft_lstsize2(t_cmd *lst);

// parsing_utils_bonus.c
void	init_struct(t_data *data);
void	files(t_data *data, char **argv, int argc);
char	*skip_spaces(char *cmd);
void	ft_error(int flag, char *msg);
char	*path_not_found(char *filename, char *cmd);

// parsing_bonus.c
void	ft_parse_args(t_data *data, char **argv);
char	**get_path(char **env);
char	*get_pathname(char *cmd, char *path);
char	*get_cmd(char **env, char *cmd);
void	ft_parse_cmds(t_data *data, char **argv, char **env, int argc);

#endif

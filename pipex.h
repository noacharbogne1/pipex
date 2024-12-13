/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:25:57 by ncharbog          #+#    #+#             */
/*   Updated: 2024/12/13 15:38:40 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include "macros.h"
# include "ft_printf/ft_printf.h"

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_data
{
	t_cmd	*cmd;
}	t_data;

// parsing.c
void	ft_parse_cmds(t_data *data, char **argv, char **env, int argc);
char	*get_cmd(t_data *data, char **env, char *cmd);
char	**get_path(t_data *data, char **env);
char	*get_pathname(char *cmd, char *path);
char	*skip_spaces(char *cmd);

// parsing2.c
void	ft_parse_args(t_data *data, char **argv, int argc);

// free_and_errors.c
void	ft_free_error(t_data *data, char *msg);
void	ft_free_tab(char **tab);
void	init_struct(t_data *data);
void	ft_init(t_data *data, char **argv, int argc);
void	ft_free_lst(t_cmd **head);

// libft_modified.c
void	ft_lstadd_back2(t_cmd **lst, t_cmd *new);
t_cmd	*ft_lstnew2(void *content);

void	ft_exec(t_data *data, t_cmd *current, char **env);

#endif
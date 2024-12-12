/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:25:57 by ncharbog          #+#    #+#             */
/*   Updated: 2024/12/12 15:36:39 by ncharbog         ###   ########.fr       */
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
	char			**param;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_data
{
	char	*file1;
	char	*file2;
	char	**path;
	t_cmd	*cmd;
}	t_data;

// parsing.c
void	ft_check_args(t_data *data, int argc, char **env);
void	get_path(t_data *data, char **env);
char	**add_slash(char **path);
int		get_cmd(t_data *data, char *cmd);

// init.c
void	ft_init_argv(t_data *data, int argc, char **argv);
void	init_structs(t_data *data);

// libft_modified.c
t_cmd	*ft_lstnew2(void *content);
void	ft_lstadd_back2(t_cmd **lst, t_cmd *new);

// free_and_errors.c
void	ft_free_error(t_data *data, char *msg);
void	ft_free_tab(char **tab);
void	ft_free_lst(t_cmd **head);

#endif
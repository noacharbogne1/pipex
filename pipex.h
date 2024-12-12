/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:25:57 by ncharbog          #+#    #+#             */
/*   Updated: 2024/12/12 17:44:56 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include "macros.h"
# include "ft_printf/ft_printf.h"

typedef struct s_data
{
	char	**cmd;
	char	**args;
}	t_data;

// parsing.c
void	ft_check_files(char **argv, int argc);
void	ft_parse_cmds(t_data *data, char **argv, char **env, int argc);
char	*get_cmd(t_data *data, char **env, char *cmd);
char	**get_path(t_data *data, char **env);
char	**add_slash(char **path);

// free_and_errors.c
void	ft_free_error(t_data *data, char *msg);
void	ft_free_tab(char **tab);
void	init_struct(t_data *data);

#endif
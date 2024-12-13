/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:51:33 by ncharbog          #+#    #+#             */
/*   Updated: 2024/12/13 14:56:35 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	count_words(char *str)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (str[i])
	{
		while (str[i] && str[i] == ' ')
			i++;
		if (str[i] && str[i] != ' ')
		{
			words++;
			while (str[i] && str[i] != ' ')
				i++;
		}
		while (str[i] && str[i] == ' ')
			i++;
	}
	return (words);
}

void	ft_parse_args(t_data *data, char **argv, int argc)
{
	t_cmd	*tmp;
	int		i;

	i = 2;
	tmp = data->cmd;
	while (i < argc - 1)
	{
		tmp->args = ft_split(argv[i], ' ');
		tmp = tmp->next;
		i++;
	}
}

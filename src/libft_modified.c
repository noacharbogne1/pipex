/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_modified.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 09:01:24 by ncharbog          #+#    #+#             */
/*   Updated: 2024/12/20 13:53:28 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_lstadd_back2(t_cmd **lst, t_cmd *new)
{
	t_cmd	*temp;

	if (!lst || !new)
		return ;
	temp = *lst;
	if (!temp)
	{
		*lst = new;
		return ;
	}
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
}

t_cmd	*ft_lstnew2(void *content)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (new == NULL)
		return (NULL);
	new->cmd = content;
	new->args = NULL;
	new->next = NULL;
	return (new);
}

int	ft_lstsize2(t_cmd *lst)
{
	t_cmd	*tmp;
	int		i;

	i = 0;
	tmp = lst;
	if (!lst)
		return (0);
	if (lst->next == NULL)
		return (1);
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	return (i + 1);
}

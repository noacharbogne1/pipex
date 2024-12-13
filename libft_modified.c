/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_modified.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 09:01:24 by ncharbog          #+#    #+#             */
/*   Updated: 2024/12/13 10:16:17 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
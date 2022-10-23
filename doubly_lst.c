/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doubly_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <yobenali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 15:45:43 by yobenali          #+#    #+#             */
/*   Updated: 2022/10/23 19:14:00 by yobenali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_token	*ft_lstnew(void *content)
// {
// 	t_token	*head;

// 	head = (t_token *)malloc(sizeof(t_token));
// 	if (!head)
// 		return (NULL);
// 	head->prev = NULL;
// 	head->content = content;
// 	head->next = NULL;
// 	return (head);
// }

t_token	*ft_lstlast(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_token **lst, t_token *new)
{
	if (!(*lst) || !lst)
		*lst = new;
	else
		ft_lstlast(*lst)->next = new;
}

void	ft_lstadd_front(t_token **lst, t_token *new)
{
	if (!lst)
		return ;
	new->next = *lst;
	*lst = new;
}

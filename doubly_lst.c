/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doubly_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <yobenali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 15:45:43 by yobenali          #+#    #+#             */
/*   Updated: 2022/11/13 22:35:24 by yobenali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_dlstlast(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

t_parser	*ft_dlstlast2(t_parser *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_dlstadd_back2(t_parser **lst, t_parser *new)
{
	t_parser	*tmp;

	tmp = NULL;
	if (!(*lst) || !lst)
		*lst = new;
	else
	{	
		tmp = ft_dlstlast2(*lst);
		if (!tmp)
			return ;
		tmp->next = new;
		new->prev = tmp;
	}
}

void	ft_dlstadd_back(t_token **lst, t_token *new)
{
	t_token	*tmp;

	tmp = NULL;
	if (!(*lst) || !lst)
		*lst = new;
	else
	{	
		tmp = ft_dlstlast(*lst);
		if (!tmp)
			return ;
		tmp->next = new;
		new->prev = tmp;
	}
}

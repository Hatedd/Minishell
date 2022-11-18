/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouizar <mouizar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 02:02:41 by mouizar           #+#    #+#             */
/*   Updated: 2021/12/06 20:28:34 by mouizar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*temp;

	new = NULL;
	while (lst)
	{
		temp = ft_lstnew(f(lst->content));
		if (!temp)
		{
			ft_lstclear(&new, del);
			return (0);
		}
		lst = lst->next;
		ft_lstadd_back(&new, temp);
	}
	return (new);
}
/*
void * f(void *content)
{
	return content = ft_strdup("map ");
}

#include <stdio.h>
void ft_affiche(t_list *node)
{
	while(node->next)
	{
		printf("%s",(char*)node->content);
		node = node->next;
	}
}

void *f(void * content)
{
	*((char*)content) += 1;
	//char * str = (char*) content;
	return content;
	// ft_strlcpy(str,"modif ",6);
}

void del(void * content)
{
	free(content);
}

int main()
{
	
	t_list *head = NULL;
	t_list *nudes = ft_lstnew(ft_strdup("ghitia mashi 3owra"));
	size_t i = 1;
	
	while (i <= 20)
	{
		ft_lstadd_front(&head,ft_lstnew(ft_strdup("please libfft")));
		i++;
	}
		ft_lstadd_front(&head,ft_lstnew(ft_strdup("nudes")));
		ft_lstadd_back(&head,nudes);
		//ft_lstdelone(nudes,del);
		//ft_lstiter(head,f);
		//ft_affiche(head);
		//printf("\n%s\n",ft_lstlast(head)->content);
		//printf("\n%d\n",ft_lstsize(head));
		t_list *mapnode;
		mapnode = ft_lstmap(head,f,del);
		ft_affiche(mapnode);
}*/
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouizar <mouizar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:15:07 by mouizar           #+#    #+#             */
/*   Updated: 2022/11/18 19:31:44 by mouizar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_parser_env(t_parser	*cmdl)
{
	t_list	*tmp;
	// if (!g_all.g_lst_env)
	// 	{
	// 		ft_lstadd_back(&g_all.g_lst_env,
	// 		ft_lstnew("SHLVL=1"));
	// 		ft_lstadd_back(&g_all.g_lst_env,
	// 		ft_lstnew("PWD=/Users/mouizar"));
	// 		ft_lstadd_back(&g_all.g_lst_env,
	// 		ft_lstnew("oldPWD=/Users/mouizar"));
	// 	}
	(void)cmdl;
	tmp = g_all.g_lst_env;
	while (tmp)
	{
		if (ft_strchr(tmp->content, '='))
			printf("%s\n", tmp->content);
		tmp = tmp->next;
	}
}

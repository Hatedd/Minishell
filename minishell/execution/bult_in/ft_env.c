/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <yobenali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:15:07 by mouizar           #+#    #+#             */
/*   Updated: 2022/11/18 00:25:13 by yobenali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_parser_env(t_parser	*cmdl)
{
	t_list	*tmp;

	(void)cmdl;
	tmp = g_all.g_lst_env;
	while (tmp)
	{
		if (ft_strchr(tmp->content, '='))
			printf("%s\n", tmp->content);
		tmp = tmp->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouizar <mouizar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 23:05:19 by mouizar           #+#    #+#             */
/*   Updated: 2022/11/20 06:49:56 by mouizar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_lstsize_cmd(t_parser *lst)
{
	t_parser	*ptr;
	int			count;

	count = 0;
	ptr = NULL;
	ptr = lst;
	while (ptr != NULL)
	{
		count++;
		ptr = ptr->next;
	}
	return (count);
}

int	is_bultin(char *str)
{
	return ((ft_strncmp(str, "cd", 3) == 0) || \
			(ft_strncmp(str, "echo", 5) == 0)
		|| (ft_strncmp(str, "env", 4) == 0)
		|| (ft_strncmp(str, "export", 7) == 0)
		|| (ft_strncmp(str, "unset", 6) == 0)
		|| (ft_strncmp(str, "pwd", 6) == 0)
		|| (ft_strncmp(str, "exit", 5) == 0));
}

int	ck_if_bultin(t_parser *cmdl)
{
	return (is_bultin(cmdl->av[0]));
}

char	*ft_found_path(void)
{
	t_list	*tmp;

	tmp = g_all.g_lst_env;
	while (tmp)
	{
		if (ft_strncmp("PATH=", tmp->content, ft_strlen("PATH=")) == 0)
			return (tmp->content);
		tmp = tmp->next;
	}
	return (0);
}

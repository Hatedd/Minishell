/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouizar <mouizar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:17:29 by mouizar           #+#    #+#             */
/*   Updated: 2022/11/20 18:13:07 by mouizar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_unset_norm(t_list *tmp, t_list *remove_node, char *str)
{
	while (tmp->next)
	{
		if (tmp && !ft_strncmp(str, tmp->next->content, ft_strlen(str))
			&& (((char *)tmp->next->content)[ft_strlen(str)] == '\0'
			|| ((char *)tmp->next->content)[ft_strlen(str)] == '='))
		{
			remove_node = tmp->next;
			if (tmp->next->next)
				tmp->next = tmp->next->next;
			else
				tmp->next = NULL;
			remove_node->next = NULL;
			free_lst(&remove_node);
			break ;
		}
		tmp = tmp->next;
	}
}

void	unset_var(t_list **lst, char *str)
{
	t_list	*tmp;
	t_list	*prev;
	t_list	*remove_node;
	int		i;

	i = 0;
	prev = *lst;
	tmp = *lst;
	remove_node = NULL;
	if (*lst == NULL)
		return ;
	else if (!ft_strncmp(str, tmp->content, ft_strlen(str))
		&& (((char *)tmp->content)[ft_strlen(str)] == '\0'
		|| ((char *)tmp->content)[ft_strlen(str)] == '='))
	{
		g_all.g_lst_env = prev->next;
		prev->next = NULL;
		free_lst(&prev);
		tmp = NULL;
		return ;
	}
	else
	{
		ft_unset_norm(tmp, remove_node, str);
	}
}

int	valid_unset(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '=')
		return (0);
	if ((ft_isdigit(str[0]) || !ft_isalpha(str[0])) && str[i] != '_' )
	{
		ft_generate_errors(str, 3);
		return (89);
	}
	i = 1;
	while (ft_isalnum(str[i]) || ft_egal(str[i]))
	{
		if (str[i + 1] == '=')
			return (1);
		i++;
	}
	if (str[i] == '\0')
		return (1);
	return (0);
}

void	ft_parser_unset(t_parser *cmdl)
{
	int		i;
	t_list	*tmp;

	tmp = g_all.g_lst_env;
	i = 1;
	while (cmdl->av[i])
	{
		if (ft_found_inenv(tmp, cmdl->av[i]) == 1)
		{
			unset_var(&tmp, cmdl->av[i]);
		}
		else if (valid_unset(cmdl->av[i]) == 0)
		{
			ft_generate_errors(cmdl->av[i], 3);
			g_all.g_exit_status = 1;
		}
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <yobenali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 23:05:30 by mouizar           #+#    #+#             */
/*   Updated: 2022/11/21 01:38:26 by yobenali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	valid_export(char	*str)
{
	int	i;

	i = 0;
	if (str[i] == '=')
		return (0);
	if (str[i] == '_')
		i = 0;
	else
		i = 1;
	if ((ft_isdigit(str[0]) || !ft_isalpha(str[0])) && !ft_egal(str[0]))
		return (0);
	while ((ft_isalnum(str[i]) || ft_egal(str[i])
		||  (str[i] == '+' && str[i + 1] == '=')) && (str[i] != '='))
	{
		if (str[i + 1] == '=' || (str[i + 1] == '+' && str[i + 2] == '='))
			return (1);
		i++;
	}
	if (str[i] == '\0' || str[i] == '=')
		return (1);
	return (0);
}

int	ft_same_c(char c1, char c2)
{
	return (c1 - c2);
}

int	ft_search_variable(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (ft_same_c(s1[i], s2[i]) == 0 && s1[i])
		i++;
	if (s1[i] == '\0' && s2[i] == '=' )
		return (1);
	return (404);
}

int	ft_found_inenv(t_list	*lst, char	*str)
{
	t_list	*tmp;
	char	**variable;

	variable = ft_split((char *)str, '=');
	tmp = lst;
	while (tmp)
	{
		if (!ft_strncmp(variable[0], tmp->content, ft_strlen(variable[0]))
			&& (((char *)tmp->content)[ft_strlen(variable[0])] == '\0'
			|| ((char *)tmp->content)[ft_strlen(variable[0])] == '='))
		{
			ft_free_array(variable);
			return (1);
		}
		tmp = tmp->next;
	}
	ft_free_array(variable);
	return (404);
}

void	ft_modify_var(t_list *lst_env, char *value)
{
	t_list	*tmp;
	char	**variable;

	variable = ft_split(value, '=');
	tmp = lst_env;
	while (tmp)
	{
		if (!ft_strncmp(variable[0], tmp->content, ft_strlen(variable[0]))
			&& (((char *)tmp->content)[ft_strlen(variable[0])] == '\0'
			|| ((char *)tmp->content)[ft_strlen(variable[0])] == '='))
		{
			free(tmp->content);
			tmp->content = value;
			ft_free_array(variable);
			return ;
		}
		tmp = tmp->next;
	}
	ft_free_array(variable);
}

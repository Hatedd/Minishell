/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouizar <mouizar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:46:49 by mouizar           #+#    #+#             */
/*   Updated: 2022/11/19 18:40:26 by mouizar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_print_export(void)
{
	t_list	*envl_tmp;

	envl_tmp = sorting(g_all.g_lst_env, ft_cmpar);
	while (envl_tmp)
	{
		printing(envl_tmp->content);
		envl_tmp = envl_tmp->next;
	}
}

void	ft_export_body(t_parser *cmdl, int i)
{
	char	*str;

	str = ft_strdup(cmdl->av[i]);
	if (ft_strchr(cmdl->av[i], '=') && ft_found_inenv(g_all.g_lst_env,
			cmdl->av[i]) == 404 && !ft_strchr(cmdl->av[i], '+'))
		ft_lstadd_back(&g_all.g_lst_env,
			ft_lstnew(str));
	else if (ft_strchr(cmdl->av[i], '=') && ft_found_inenv(g_all.g_lst_env,
			cmdl->av[i]) == 1)
		ft_modify_var(g_all.g_lst_env, str);
	else if (!ft_strchr(cmdl->av[i], '=') && ft_found_inenv(g_all.g_lst_env,
			cmdl->av[i]) == 404 && !ft_strchr(cmdl->av[i], '+'))
	{
		ft_lstadd_back(&g_all.g_lst_env,
			ft_lstnew(str));
	}
	else
		free(str);
}

void	ft_parser_export(t_parser *cmdl)
{
	int	i;

	i = 0;

	
	if (cmdl->av[1] == 0)
		ft_print_export();
	else
	{
		while (cmdl->av[++i])
		{
			if (valid_export(cmdl->av[i]))
				ft_export_body(cmdl, i);
			else
				printf("minishell: export: `%s': not a valid identifier\n",
					cmdl->av[i]);// remove printfs in errors
			g_all.g_exit_status = 1;
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <yobenali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:46:49 by mouizar           #+#    #+#             */
/*   Updated: 2022/11/21 01:44:39 by yobenali         ###   ########.fr       */
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
	g_all.flag_exit_export = 0;
	if (cmdl->av[1] == 0)
		ft_print_export();
	else
	{
		while (cmdl->av[++i])
		{
			if (valid_export(cmdl->av[i]))
			{
				ft_export_body(cmdl, i);
				g_all.g_exit_status = 0;
			}
			else
			{
				g_all.flag_exit_export = 1;
				ft_generate_errors(cmdl->av[i], 1);
			}
		}
		if (g_all.flag_exit_export == 1)
			g_all.g_exit_status = 1;
	}
}

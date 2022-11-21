/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bult_in.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <yobenali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:42:41 by mouizar           #+#    #+#             */
/*   Updated: 2022/11/21 05:49:54 by yobenali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_build_env(void)
{
	int		i;
	char	*str;

	i = 0;
	g_all.g_lst_env = NULL;
	while (g_all.our_env[i])
	{
		str = ft_strdup(g_all.our_env[i]);
		ft_lstadd_back(&g_all.g_lst_env, ft_lstnew(str));
		i++;
	}
}

void	ft_fill_env(void)
{
	if (!g_all.g_lst_env)
	{
		g_all.flag_vide_env = 1;
		ft_lstadd_back(&g_all.g_lst_env, ft_lstnew(ft_strdup("SHLVL=1")));
		ft_lstadd_back(&g_all.g_lst_env, \
			ft_lstnew(ft_strdup("PWD=/Users/mouizar")));
		ft_lstadd_back(&g_all.g_lst_env, ft_lstnew(ft_strdup("OLDPWD=")));
	}
}

void	bult_in(t_parser *cmdl)
{
	g_all.flag_vide_env = 0;
	ft_fill_env();
	if (cmdl->flag == NOEXEC)
	{
		error_set(1);
		return ;
	}
	if (ft_strncmp(cmdl->av[0], "cd", 3) == 0)
		ft_parser_cd(cmdl);
	else if (ft_strncmp(cmdl->av[0], "echo", 5) == 0)
		ft_parser_echo(cmdl);
	else if (ft_strncmp(cmdl->av[0], "env", 4) == 0)
		ft_parser_env(cmdl);
	else if (ft_strncmp(cmdl->av[0], "export", 7) == 0)
		ft_parser_export(cmdl, 0);
	else if (ft_strncmp(cmdl->av[0], "unset", 6) == 0)
		ft_parser_unset(cmdl);
	else if (ft_strncmp(cmdl->av[0], "pwd", 6) == 0)
		ft_parser_pwd();
	else if (ft_strncmp(cmdl->av[0], "exit", 5) == 0)
		ft_exit_parser(cmdl);
}

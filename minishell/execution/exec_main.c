/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouizar <mouizar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 02:29:15 by mouizar           #+#    #+#             */
/*   Updated: 2022/11/20 01:16:08 by mouizar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	initial_dup_path(t_parser *cmdl)
{
	g_all.path = ft_split_path(cmdl);
	//dprintf(2, "%p\n", g_all.path);
	g_all.tmpp_in = dup(0);
	g_all.tmpp_out = dup(1);
}

int	ft_size(char **str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_norm(t_parser *tmp)
{
	//dprintf(2, "ok\n");
	//ft_free_array(g_all.path);
	ft_generate_erro2(tmp, 2);
}

void	ft_norm2(int id)
{
	ft_wait(id);
	signal(SIGINT, ft_handler);
	ft_free_array(g_all.path);
	g_all.path = NULL;
}

void	execution(t_parser *cmdl)
{
	t_parser		*tmp;
	int			id;
	struct stat	stats;
	int			i;
	
	tmp = cmdl;
	if (!tmp->av )
		return ;
	i = stat(cmdl->av[0], &stats);
	initial_dup_path(cmdl);
				// system("leaks minishell");
	//dprintf(2,"-- %p\n", cmdl->av[0]);
	if (!g_all.path && !ck_if_bultin(tmp) && !ft_strchr(tmp->av[0], '/'))
	{
		ft_generate_erro2(tmp, 4);	
		return ;
	}
	if (!S_ISDIR(stats.st_mode))
	{
		signal(SIGINT, SIG_IGN);
		if (ft_lstsize_cmd(tmp) == 1)
		{
			id = single_command(tmp);
		}
		else
			id = multiple_command(tmp);
		ft_norm2(id);
	}
	else
		ft_generate_erro2(tmp, 1);
	//dprintf(2,"-- %p\n", g_all.path);
	ft_free_array(g_all.path);
}

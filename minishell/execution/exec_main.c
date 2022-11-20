/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <yobenali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 02:29:15 by mouizar           #+#    #+#             */
/*   Updated: 2022/11/20 18:58:30 by yobenali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	initial_dup_path(t_parser *tmp)
{
	g_all.flag_norm_exec = 0;
	g_all.path = ft_split_path(tmp);
	g_all.tmpp_in = dup(0);
	g_all.tmpp_out = dup(1);
	if (!g_all.path && !ck_if_bultin(tmp) && !ft_strchr(tmp->av[0], '/'))
	{
		g_all.flag_norm_exec = 1;
		printf("minishell: %s: No such file or directory\n", tmp->av[0]);
		g_all.g_exit_status = 127;
		return ;
	}
}

int	ft_size(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_norm(t_parser *tmp)
{
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
	t_parser	*tmp;
	int			id;
	struct stat	stats;
	int			i;

	tmp = cmdl;
	if (!tmp->av)
		return ;
	i = stat(cmdl->av[0], &stats);
	initial_dup_path(cmdl);
	if (!S_ISDIR(stats.st_mode) && g_all.flag_norm_exec == 0)
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
	else if (g_all.path)
		ft_generate_erro2(tmp, 1);
	ft_free_array(g_all.path);
}

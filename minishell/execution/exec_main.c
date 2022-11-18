/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <yobenali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 02:29:15 by mouizar           #+#    #+#             */
/*   Updated: 2022/11/18 01:23:49 by yobenali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	initial_dup_path(t_parser *cmdl)
{
	g_all.path = ft_split_path(cmdl);
	// printf("in initial dup %p\n", g_all.path);
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
	ft_free_array(g_all.path);
	ft_generate_erro2(tmp, 2);
}

void	ft_norm2(int id)
{
	ft_wait(id);
	signal(SIGINT, ft_handler);
	ft_free_array(g_all.path);
}

void	execution(t_parser *cmdl)
{
	t_parser		*tmp;
	int			id;
	struct stat	stats;
	int			i;
	
	i = stat(cmdl->av[0], &stats);
	initial_dup_path(cmdl);
	tmp = cmdl;
	if (!tmp->av || !g_all.path)
		return ;
	if (!S_ISDIR(stats.st_mode))
	{

		signal(SIGINT, SIG_IGN);
		if (ft_lstsize_cmd(tmp) == 1)
			id = single_command(tmp);
		else
			id = multiple_command(tmp);
		ft_norm2(id);
	}
	else
		ft_generate_erro2(tmp, 1);
	// system("leaks minishell");
}

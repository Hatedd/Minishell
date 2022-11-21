/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <yobenali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 23:14:47 by mouizar           #+#    #+#             */
/*   Updated: 2022/11/21 03:20:51 by yobenali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_if_bultin(t_parser *tmp)
{
	if (ck_if_bultin(tmp))
	{
		bult_in(tmp);
		exit(g_all.g_exit_status);
		tmp->exec_flag = 1;
	}
}

void	ft_if_not_bultin(t_parser	*tmp)
{
	int		succs;
	int		i;

	i = 0;
	tmp->path = ft_split_path(tmp);
	if (tmp->exec_flag == 0)
	{
		while (tmp->path[i])
		{
			succs = access(tmp->path[i], X_OK);
			if (succs == 0)
				break ;
			i++;
		}
		if (succs == 0)
		{
			if (execve(tmp->path[i], tmp->av, g_all.our_env))
				ft_generate_erro2(tmp, 2);
		}
		else
			ft_generate_erro2(tmp, 2);
	}
}

int	ft_multi_pipes(t_parser *tmp)
{
	int		id;

	if (pipe(tmp->pipe) == -1)
		printf("pipe failed\n");
	id = fork();
	if (id == 0)
	{
		if (tmp->flag == NOEXEC)
			exit(1);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		ft_process_communication(tmp);
		ft_redirection(tmp);
		if (!tmp->av && tmp->flag == EXEC)
			exit (0);
		ft_if_bultin(tmp);
		ft_if_not_bultin(tmp);
	}
	else
	{
		close(tmp->pipe[1]);
		if (tmp->prev)
			close(tmp->prev->pipe[0]);
	}
	return (id);
}

void	exec_single(t_parser *tmp)
{
	int	i;
	int	sccs;

	if_invalid_path_cmd(tmp);
	i = 0;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	while (g_all.path[i])
	{
		sccs = access(g_all.path[i], X_OK);
		if (sccs == 0)
			break ;
		i++;
	}
	if (sccs == 0)
	{
		if (execve(g_all.path[i], tmp->av, g_all.our_env))
		{
			ft_generate_erro2(tmp, 2);
			exit(g_all.g_exit_status);
		}
	}
	else
		ft_generate_erro2(tmp, 2);
}

int	ft_singl_cmd(t_parser *tmp)
{
	int	id;

	id = fork();
	if (id == -1)
		perror("minishell ");
	if (id == 0)
	{
		if (tmp->flag == NOEXEC)
			exit (1);
		if (!tmp->av && tmp->flag == EXEC)
			exit (0);
		exec_single(tmp);
	}
	return (id);
}

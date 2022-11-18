/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <yobenali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 23:11:02 by mouizar           #+#    #+#             */
/*   Updated: 2022/11/18 00:30:11 by yobenali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	single_command(t_parser *tmp)
{
	int	id;

	id = 0;
	ft_redirection(tmp);
	if (ck_if_bultin(tmp) == 1)
		bult_in(tmp);
	else
		id = ft_singl_cmd(tmp);
	dup2 (g_all.tmpp_out, 1);
	dup2 (g_all.tmpp_in, 0);
	close (g_all.tmpp_in);
	close (g_all.tmpp_out);
	return (id);
}

int	multiple_command(t_parser *tmp)
{
	int	id;

	while (tmp)
	{
		id = ft_multi_pipes(tmp);
		dup2(g_all.tmpp_out, 1);
		dup2(g_all.tmpp_in, 0);
		tmp = tmp->next;
	}
	close(g_all.tmpp_in);
	close(g_all.tmpp_out);
	return (id);
}

void	ft_wait(int id)
{
	int		status;
	int		pid;

	while (1)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == -1)
			break ;
		if (pid == id)
		{
			if (WIFEXITED(status))
					g_all.g_exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
					g_all.g_exit_status = 128 + WTERMSIG(status);
		}
	}
	signal(SIGINT, ft_handler);
}

void	ft_redirection(t_parser *tmp)
{
	if (tmp->out_fd != 1)
	{
		dup2(tmp->out_fd, 1);
		close(tmp->out_fd);
	}
	if (tmp->in_fd != 0)
	{
		dup2(tmp->in_fd, 0);
		close (tmp->in_fd);
	}
}

void	ft_process_communication(t_parser *tmp)
{
	if (tmp->out_fd == -2 && tmp->next)
	{	
		if (dup2(tmp->pipe[1], 1) == -1)
			printf("dup failed\n");
		close (tmp->pipe[0]);
		close (tmp->pipe[1]);
	}
	if (tmp->in_fd == -2 && tmp->prev != NULL)
	{
		if (dup2(tmp->prev->pipe[0], 0) == -1)
			printf("dup failed\n");
		close (tmp->prev->pipe[1]);
		close (tmp->prev->pipe[0]);
	}
}

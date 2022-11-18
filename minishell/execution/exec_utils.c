/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <yobenali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 18:47:12 by mouizar           #+#    #+#             */
/*   Updated: 2022/11/18 17:05:35 by yobenali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_generate_errors(char *str, int flag)
{
	if (flag == 1)
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": not a valid identifier\n", 2);
	}
}

void	ft_generate_erro2(t_parser *tmp, int flag)
{
	if (flag == 2)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(tmp->av[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		g_all.g_exit_status = 127;
		exit(127);
	}
	else if (flag == 1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(tmp->av[0], 2);
		ft_putstr_fd(": is a directory\n", 2);
		g_all.g_exit_status = 126;
	}
	else if (flag == 3)
	{
		printf("minishell: %s: No such file or directory\n", tmp->av[1]);
		g_all.g_exit_status = 1;
	}
	else if (flag == 4)
	{
		printf("minishell: %s: No such file or directory\n", tmp->av[0]);
		g_all.g_exit_status = 127;
		
	}
}

void	ft_exit_error(t_parser *cmdl, int flag)
{
	if (flag == 1)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmdl->av[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		g_all.g_exit_status = 255;
		exit((unsigned short)g_all.g_exit_status);
	}
	else if (flag == 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			g_all.g_exit_status = 1;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <yobenali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:23:57 by mouizar           #+#    #+#             */
/*   Updated: 2022/11/18 00:27:20 by yobenali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_if_num(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-' && str[1] == '\0')
		return (0);
	while (str[i])
	{
		if (str[0] == '-' || str[0] == '+')
			i++;
		if (ft_isdigit(str[i]))
			i++;
		else
			break ;
	}
	if (str[i] == '\0')
		return (1);
	return (0);
}

void	ft_exit_value(t_parser *cmdl)
{
	if (ft_strncmp(cmdl->av[1], "--", 3) == 0)
	{
		g_all.g_exit_status = 255;
		exit((unsigned short)g_all.g_exit_status);
	}
	else
		ft_exit_error(cmdl, 1);
}

int	ft_num_alpha(char *str)
{
	int	i;

	i = 0;
	while ((str[i] && ft_isdigit(str[i])))
		i++;
	if (str[i] == '\0')
		return (0);
	else
		return (1);
}

// int	handel_two_negative(t_parser *cmdl, unsigned short exitt)
// {
// 	if (ft_strncmp(cmdl->av[1], "--", 3) == 0)
// 	{
// 		if (cmdl->av[2])
// 		{
// 			if (ft_atoi(cmdl->av[2]) >= SIZE_MAX && cmdl->av[2][0] != '-')
// 			{
// 				ft_exit_error(cmdl, 2);
// 				exitt = g_all.g_exit_status;
// 			}
// 			g_all.g_exit_status = ft_atoi_exit(cmdl->av[2]);
// 			exitt = g_all.g_exit_status;
// 		}
// 		g_all.g_exit_status = 0;
// 		exitt = g_all.g_exit_status;
// 	}
// 	return (exitt);
// }

void	ft_exit_parser(t_parser *cmdl)
{
	unsigned short	exitt;

	exitt = g_all.g_exit_status;
	if (!cmdl->prev)
		printf("exit\n");
	if (cmdl->av[1] == 0)
		exit(exitt);
	else if (cmdl->av[2] != NULL)
	{
		// exitt = handel_two_negative(cmdl, exitt);
		if (ft_num_alpha(cmdl->av[1]) == 0)
		{
			ft_exit_error(cmdl, 2);
			exitt = g_all.g_exit_status;
			return ;
		}
		else
		{
			ft_exit_error(cmdl, 2);
			exitt = g_all.g_exit_status;
		}
	}
	else if (cmdl->av[1])
		ft_exit_value(cmdl);
	exit(exitt);
}

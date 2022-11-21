/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <yobenali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:23:57 by mouizar           #+#    #+#             */
/*   Updated: 2022/11/21 04:10:06 by yobenali         ###   ########.fr       */
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
	if (str[i] == '\0' || (str[0] == '-'  && ft_isdigit (str[1])))
		return (0);
	else
		return (1);
}

unsigned short    ft_too_many(t_parser *cmdl, unsigned short exitt)
{
    ft_exit_error(cmdl, 2);
    exitt = 255;
    return (exitt);
}

void    ft_exit_parser(t_parser *cmdl)
{
    unsigned short    exitt;

    exitt = g_all.g_exit_status;
    if (!cmdl->prev)
        printf("exit\n");
    if (cmdl->av[1] == 0)
        exit(exitt);
    else if (cmdl->av[2] != NULL)
    {
        if (ft_num_alpha(cmdl->av[1]) == 0)
        {
            ft_exit_error(cmdl, 2);
            g_all.g_exit_status = 1;
            return ;
        }
        else
            exitt = ft_too_many(cmdl, exitt);
    }
    else if (cmdl->av[1] && ft_num_alpha(cmdl->av[1]) == 0)
        exitt = ft_atoi_exit(cmdl->av[1]);
    else if (cmdl->av[1])
        ft_exit_value(cmdl);
    exit(exitt);
}
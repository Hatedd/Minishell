/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <yobenali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:10:36 by mouizar           #+#    #+#             */
/*   Updated: 2022/11/21 19:45:47 by yobenali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_valid_n(char *str)
{
	int	i;

	i = 1;
	if (str[0] == '-' && str[1] == 'n')
	{
		while (str[i] == 'n' && str[i])
			i++;
		if (str[i] == '\0')
			return (1);
	}
	return (0);
}

int	ft_option_n(t_parser *cmdl, int j)
{
	int	i;

	i = 0;
	while (cmdl->av[j])
	{
		if (ft_valid_n(cmdl->av[j]) == 1)
			i++;
		else if (!(ft_valid_n(cmdl->av[j])))
			break ;
		j++;
	}
	return (i);
}

void	print_echo(t_parser *cmdl, int i)
{
	if (cmdl->av[i + 1] == 0)
		return ;
	else
	{
		while (cmdl->av[i++])
		{
			ft_putstr_fd(cmdl->av[i], 1);
			if (cmdl->av[i + 1] == 0)
				break ;
			write(1, " ", 1);
		}
	}
}

void	ft_parser_echo(t_parser	*cmdl)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	if (cmdl->av[j] == 0)
	{
		write(1, "\n", 1);
		return ;
	}
	i = ft_option_n(cmdl, j);
	if (cmdl->av[j] == 0)
		return ;
	print_echo(cmdl, i);
	g_all.g_exit_status = 0;
	if (ft_valid_n(cmdl->av[1]) == 0)
	{
		write(1, "\n", 1);
		return ;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouizar <mouizar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:01:35 by mouizar           #+#    #+#             */
/*   Updated: 2022/11/20 17:41:02 by mouizar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_parser_pwd(void)
{
	char	*buff;

	buff = getcwd(0, 0);
	if (!buff)
		return ;
	printf("%s\n", buff);
	free(buff);
}

void	ft_check_ul(unsigned long res, int signe, const char *str)
{
	if ((res > 9223372036854775807 && signe == 1)
		|| (res > 9223372036854775808UL && signe == -1))
	{
		ft_generate_errors((char *)str, 2);
		g_all.g_exit_status = 255;
		exit((unsigned short)g_all.g_exit_status);
	}
}

int	ft_atoi_exit(const char *str)
{
	unsigned long	res;
	int				i;
	int				signe;

	signe = 1;
	res = 0;
	i = 0;
	while (((str[i] == ' ') || (str[i] >= 9 && (str[i] <= 13))))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signe *= -1;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - 48);
		ft_check_ul(res, signe, str);
		i++;
	}
	return (res * signe);
}

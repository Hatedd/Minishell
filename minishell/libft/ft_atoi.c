/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouizar <mouizar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 16:19:53 by mouizar           #+#    #+#             */
/*   Updated: 2021/12/04 21:04:27 by mouizar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
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
		if (res > 9223372036854775807 && signe == 1)
			return (-1);
		else if (res > 9223372036854775808UL && signe == -1)
			return (0);
		i++;
	}
	return (res * signe);
}

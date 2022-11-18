/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <yobenali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 06:25:32 by yobenali          #+#    #+#             */
/*   Updated: 2022/11/18 00:20:43 by yobenali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_putchar(char c)
{
	write(2, &c, 1);
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return ;
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
}

int	check_word(t_meta *meta, int pos)
{
	if (meta->meta_str[pos] && (meta->meta_str[pos] != 'b'
			&& meta->meta_str[pos] != 'p' && meta->meta_str[pos] != 'w'
			&& meta->meta_str[pos] != 'r'))
		return (1);
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	if (!s1 || !s2)
		return (0);
	while (*s1 == *s2 && *s1 && *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

int	ft_matchnmatch(char *buffer, char *mbuffer, char *charset, char match)
{
	int	i;

	i = 0;
	while (buffer[i])
	{
		if (ft_strchr(charset, buffer[i]))
		{
			if (mbuffer[i] == match)
				return (1);
		}
		i++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <yobenali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 06:25:32 by yobenali          #+#    #+#             */
/*   Updated: 2022/11/15 03:25:12 by yobenali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**add_change(char **tab, char *str)
{
	int		i;
	char	**new;

	i = 0;
	if (!tab)
	{
		new = ft_calloc((i + 2), sizeof(char *));
		new[0] = ft_strdup(str);
		return (new);
	}
	while (tab[i])
		i++;
	new = ft_calloc((i + 2), sizeof(char *));
	i = 0;
	while (tab[i])
	{
		new[i] = tab[i];
		i++;
	}
	free(tab);
	new[i] = ft_strdup(str);
	return (new);
}

void	error_set(int nb)
{
	g_all.g_exit_status = nb;
	g_all.g_error_status = EXIT_FAILURE;
	return ;
}

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouizar <mouizar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 17:14:09 by yobenali          #+#    #+#             */
/*   Updated: 2022/11/18 23:02:24 by mouizar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

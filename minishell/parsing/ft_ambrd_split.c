/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ambrd_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <yobenali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 01:32:57 by yobenali          #+#    #+#             */
/*   Updated: 2022/11/18 00:20:43 by yobenali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	ft_cal(char *str)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == '\n' || str[i] == '\t' || str[i] == ' '))
			i++;
		if (str[i] && str[i] != '\n' && str[i] != '\t' && str[i] != ' ')
			nb++;
		while (str[i] && str[i] != '\n' && str[i] != '\t' && str[i] != ' ')
			i++;
	}
	return (nb);
}

void	help_all(char **tab, char *str, int i, int j)
{
	int	cou;

	*tab = malloc(j + 1);
	if (!tab[0])
		ft_free(tab);
	cou = 0;
	i -= j;
	while (str[i] && str[i] != '\n' && str[i] != '\t' && str[i] != ' ')
	{
		tab[0][cou] = str[i];
		cou++;
		i++;
	}
	tab[0][cou] = '\0';
}

char	**all(char *str, char **tab)
{
	int	i;
	int	k;
	int	j;

	i = 0;
	k = -1;
	while (str[i])
	{
		j = 0;
		while (str[i] && (str[i] == '\n' || str[i] == '\t' || str[i] == ' '))
			i++;
		while (str[i] && str[i] != '\n' && str[i] != '\t' && str[i] != ' ')
		{
			i++;
			j++;
		}
		if (j)
		{
			k++;
			help_all(&tab[k], str, i, j);
		}
	}
	return (tab);
}

char	**ft_split2(char *str)
{
	int		w_cal;
	char	**tab;

	w_cal = ft_cal(str);
	tab = malloc(sizeof(char *) * (w_cal + 1));
	if (!tab)
		return (NULL);
	all(str, tab);
	tab[w_cal] = 0;
	return (tab);
}

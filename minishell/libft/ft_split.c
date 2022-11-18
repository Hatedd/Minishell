/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouizar <mouizar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 21:14:01 by mouizar           #+#    #+#             */
/*   Updated: 2021/12/06 21:54:48 by mouizar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_compteur(const char *s, char c)
{
	size_t	i;
	size_t	w;

	i = 0;
	w = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			while (s[i] && s[i] != c)
				i++;
			w++;
		}
	}
	return (w);
}

static char	**ft_free(int j, char	**split)
{
	while (j >= 0)
	{
		free(split[j]);
		j--;
	}
	free(split);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**p;
	size_t	i;
	size_t	j;
	size_t	start;

	if (!s)
		return (NULL);
	i = 0;
	j = 0;
	p = malloc(sizeof(char *) * (ft_compteur(s, c) + 1));
	if (!p)
		return (NULL);
	while (j < ft_compteur(s, c))
	{
		while (s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		p[j++] = ft_substr(s, start, i - start);
		if (!p[j - 1])
			return (ft_free(j, p));
	}
	p[j] = NULL;
	return (p);
}

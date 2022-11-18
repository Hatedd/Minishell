/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouizar <mouizar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 07:46:48 by mouizar           #+#    #+#             */
/*   Updated: 2021/12/05 19:48:34 by mouizar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;
	ssize_t	lens1;
	ssize_t	lens2;

	if (!s1 || !s2)
		return (NULL);
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	p = malloc (sizeof(char) * (lens1 + lens2 + 1));
	if (!p)
		return (NULL);
	p[0] = '\0';
	ft_strlcat(p, s1, lens1 + 1);
	ft_strlcat(p, s2, lens1 + lens2 + 1);
	return (p);
}

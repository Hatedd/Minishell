/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouizar <mouizar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 07:17:38 by mouizar           #+#    #+#             */
/*   Updated: 2022/10/23 21:37:05 by mouizar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*str;
	int		i;

	i = 0;
	if (!s1)
		return (NULL);
	str = (char *) malloc (sizeof(char) * ft_strlen(s1) +1);
	if (!str)
		return (NULL);
	while (*s1)
		str[i++] = *s1++;
	str[i] = '\0';
	return (str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouizar <mouizar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 22:02:56 by mouizar           #+#    #+#             */
/*   Updated: 2021/12/05 09:49:52 by mouizar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	*s1;
	int				len;

	len = 0;
	s1 = (unsigned char *) s;
	while (*(s1 + len))
		len++ ;
	if (!s1)
		return (NULL);
	while (len >= 0)
	{
		if (s1[len] == (unsigned char)c)
			return ((char *)(s1 + len));
		len--;
	}
	return (NULL);
}

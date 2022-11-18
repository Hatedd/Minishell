/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouizar <mouizar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 08:17:21 by mouizar           #+#    #+#             */
/*   Updated: 2021/12/05 19:16:57 by mouizar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const	*s1, char const	*set)
{
	size_t	start;
	size_t	last;
	char	*str;

	start = 0;
	if (!s1)
		return (NULL);
	last = ft_strlen(s1);
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	while (s1[last - 1] && ft_strchr(set, s1[last - 1]) && start < last)
		last--;
	str = (char *)malloc(sizeof(char) * (last - start + 1));
	if (str)
		ft_strlcpy(str, &s1[start], last - start + 1);
	return (str);
}

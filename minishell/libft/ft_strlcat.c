/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouizar <mouizar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 07:59:04 by mouizar           #+#    #+#             */
/*   Updated: 2021/12/05 16:20:04 by mouizar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char	*dst, const char	*src, size_t dstsize)
{
	size_t	i;
	size_t	lendst;

	i = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	lendst = ft_strlen(dst);
	if (dstsize < lendst)
		return (dstsize + ft_strlen(src));
	while (src[i] && ((lendst + i) + 1) < dstsize)
	{
		dst[lendst + i] = src[i];
		i++;
	}
	dst[lendst + i] = '\0';
	return (lendst + ft_strlen(src));
}

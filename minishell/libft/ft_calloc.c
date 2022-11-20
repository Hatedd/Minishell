/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <yobenali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 21:57:21 by mouizar           #+#    #+#             */
/*   Updated: 2022/11/20 01:49:00 by yobenali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*p;

	p = malloc (count * size);
	if (!p)
	{
		perror("minishell ");
		exit(EXIT_FAILURE);
	}
	ft_bzero (p, count * size);
	return (p);
}

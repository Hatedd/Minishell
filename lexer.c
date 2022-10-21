/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <yobenali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:05:03 by yobenali          #+#    #+#             */
/*   Updated: 2022/10/20 21:06:08 by yobenali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    lexer_scan(t_token *token, t_meta *meta)
{
    int i = 0;
    int j;
    meta->len  = ft_strlen(meta->meta_str);
    while (meta->meta_str != '\0' && i < meta->len)
    {
        if (meta->meta_str[i] == 'b')
            i++;
        if (meta->meta_str[i] == 'u')
        {
            j = 1;
            while (meta->meta_str[i + i] == 'u')
            {
                 j++;
                 i++;  
            }
            i++; 
        }
        else if (meta->meta_str[i] == 'p')
        {
            
        }
    }
}
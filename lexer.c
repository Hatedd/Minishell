/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <yobenali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:05:03 by yobenali          #+#    #+#             */
/*   Updated: 2022/10/21 22:18:33 by yobenali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    trans_to_string(t_meta *meta, t_token *token, int pos)
{
    
}

void    init_data(t_meta *meta, t_token *token)
{
    meta->tokens[i] 
}

int     check_not_word(t_meta *meta, int pos)
{
    if (meta->meta_str[pos] == 'b' || meta->meta_str[pos] == '<' || meta->meta_str[pos] == '>' || meta->meta_str[pos] == '|')
        return (0);
    return (1);
}

int init_token(int type, int start, t_meta *meta)
{
    meta->tokens->type = type;
    while (check_not_word(meta, start))
    {
        meta->tokens->  
    }
}

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
                 j++; 
            while (i < i + j)
            {
                init_token(TOKEN_WORD, i, j, meta, token);
            }
        }
        else if (meta->meta_str[i] == 'p')
        {
            
        }
    }
}
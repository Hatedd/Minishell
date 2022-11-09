/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <yobenali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 22:23:15 by yobenali          #+#    #+#             */
/*   Updated: 2022/11/09 22:54:12 by yobenali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_expand(t_token *tokens)
{
    t_token *tmp;
    char    *old_meta;
    int     i;
    int     j;

    tmp = tokens;
    while (tmp)
    {
        if (!tmp->word)
            return ;
        tmp->old_word = ft_strdup(tmp->word);
        old_meta = ft_strdup(tmp->meta);
        if (!ft_strchr(tmp->meta, 'x') && !ft_strchr(tmp->meta, 'X') && \
                (ft_strchr(tmp->meta, 's') || ft_strchr(tmp->meta, 'd')))
        {
            j = 0;
            i = 0;
            while (tmp->meta[i])
            {
                if (tmp->meta[i] && (tmp->meta[i] != 'd' && tmp->meta[i] != 's'))
                {
                    tmp->word[j] = tmp->old_word[i];
                    old_meta[j] = tmp->meta[i];
                    j++;
                }
                i++;
            }
            tmp->word[j] = '\0';
            old_meta[j] = '\0';
            free (tmp->meta);
            tmp->meta = old_meta;
        }
        else if (ft_strchr(tmp->meta, 'x') || ft_strchr(tmp->meta, 'X'))// there is an expansion "x" or "X" 
        {
            j = i;
        }
        tmp = tmp->next;
    }
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <yobenali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 00:05:19 by yobenali          #+#    #+#             */
/*   Updated: 2022/10/02 03:37:37 by yobenali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>
int     ft_strlen(char *str)
{
    int i;

    i = 0;
    while(str[i])
        i++;
    return (i);
}

int     is_char(char c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        return (1);
    return (0);
}

int     ft_quote(char *av, t_meta *meta, int pos)
{
    if (av[pos] == '\'')
    {
        meta->m_str[pos++] = 's';
        while (av[pos] != '\'')
        {
            meta->m_str[pos] = 'Q';
            pos++;
        }
        meta->m_str[pos] = 's';
    }
    else if (av[pos] == '"')
    {
        meta->m_str[pos++] = 'd';
        while (av[pos] != '"')
        {
            if (av[pos] == '$')
                meta->m_str[pos] = 'x';
            else
                meta->m_str[pos] = 'q';
            pos++;
        }
        meta->m_str[pos] = 'd';
    }
    return (pos);
}

void    ft_trans_meta(char *av, t_meta *meta)
{
    int i;
    int len;

    i = 0;
    len = ft_strlen(av) + 1;
    meta->m_str = malloc(sizeof(char) * len);
    while (av[i])
    {
        if (is_char(av[i]))
            meta->m_str[i] = 'u';
        else if (av[i] == '|')
            meta->m_str[i] = 'p';
        else if (av[i] == '<')
            meta->m_str[i] = 'r';
        else if (av[i] == '>')
            meta->m_str[i] = 'w';
        else if (av[i] == ' ')
            meta->m_str[i] = 'b';
        else if (av[i] == '$')
        {
            if (av[i + 1] && is_char(av [i + 1]))
            {
                meta->m_str[i] = 'x';
            }
            else if (av[i + 1] && av[i + 1] == '?')
                meta->m_str[i] = 'X';
            else
                meta->m_str[i] = 'u';
        }
        else if (av[i] == '\'' || av[i] == '"')
            i = ft_quote(av, meta, i);
        else
            meta->m_str[i] = 'u';
        i++;
    }
    meta->m_str[i] = 0;
}

int main()
{
    int i = 0;
    t_meta *meta;
    
    char * a;

    a = strdup("\"$USER\"");
    meta = malloc(sizeof(t_meta));
    ft_trans_meta(a, meta);
    printf("%s\n", meta->m_str);
    return (0);
}
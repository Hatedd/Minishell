/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <yobenali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:05:03 by yobenali          #+#    #+#             */
/*   Updated: 2022/10/18 22:23:43 by yobenali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer *init_lexer(char *content)
{
    t_lexer *lexer;

    lexer = malloc(sizeof(t_lexer));
    lexer->i = 0;
    lexer->len = ft_strlen(content);
    lexer->content = content;
    lexer->c = content[lexer->i];
 
    return (lexer);
}

void    lexer_advance(t_lexer *lexer)
{
    if (lexer->c != '\0' && lexer->i < lexer->len)   
    {
        lexer->i++;
        lexer->c = lexer->content[lexer->i];
    }
}

void    lexer_skip_space(t_lexer *lexer)
{
    if (lexer->c == ' ' || lexer->c == '\n')
    {
        lexer_advance(lexer);   
    }
}

t_token *get_next_token(t_lexer *lexer)
{
    while (lexer->c != '\0' && lexer->i < lexer->len)
    {
        if (lexer->c == ' ' || lexer->c == '\n')
            lexer_skip_space(lexer);
        if (lexer->c == ''))
    }
}

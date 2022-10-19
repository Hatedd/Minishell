/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <yobenali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 00:05:08 by yobenali          #+#    #+#             */
/*   Updated: 2022/10/19 00:56:57 by yobenali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>

typedef struct s_meta
{
    char    *m_str;
    char    *token;
}   t_meta;

typedef struct s_lexer
{
    char	c;
    char	*content;
    int		i;
	int		len;
}   t_lexer;

typedef	struct s_token
{
	enum
	{
		TOKEN_ID,
		TOKEN_STRING,
		TOKEN_PIPE,
		TOKEN_READ,
		TOKEN_WRITE,
		TOKEN_LQOUTE,
		TOKEN_RQOUTE
	};
	char *content;
}	t_token;

int       ft_strlen(char *str);

#endif
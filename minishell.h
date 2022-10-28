/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <yobenali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 00:05:08 by yobenali          #+#    #+#             */
/*   Updated: 2022/10/28 01:16:24 by yobenali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
// # include "/Users/yobenali/readline/include/readline/readline.h"
// # include "/Users/yobenali/readline/include/readline/history.h"
# include <sys/wait.h>
# define TRUE	1
# define FALSE	0


typedef struct s_gdata
{
	char	g_error_status;
	int		g_exit_status;
	char	**our_env;
}	t_gdata;

typedef struct s_token
{
	enum
	{
		TOKEN_WORD,
		TOKEN_PIPE,
		TOKEN_DREAD,
		TOKEN_READ,
		TOKEN_DWRITE,
		TOKEN_WRITE,
	} e_type;
	char			*word;
	char			*meta;
	char			*old_word;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_meta
{
	char	*meta_str;
	char	*cmd;
	int		len;
	int		i;
	int		flag;
	t_token	*tokens;
}	t_meta;

int		ft_strlen(char *str);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memset(void *b, int c, size_t len);
void	ft_bzero(void	*s, size_t n);
void	ft_lstadd_back(t_token **lst, t_token *new);
t_token	*ft_lstlast(t_token *lst);
t_token	*lexer_scan(t_meta *meta);

#endif
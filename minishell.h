/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <yobenali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 00:05:08 by yobenali          #+#    #+#             */
/*   Updated: 2022/11/13 01:55:31 by yobenali         ###   ########.fr       */
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
# include "./libft/libft.h"
# define TRUE		1
# define FALSE		0
# define EXPAND		0
# define NO_EXPAND	1

# define EXEC		1
# define NOEXEC		0
# define FIRST		1
# define SECOND		2
# define ALL		3

# define read		0
# define write		1

typedef	struct	s_parser
{
	char			flag;
	int				index;
	int 			pipe[2];
	int				in_fd;
	int				out_fd;
	char 			**av;
	char 			*c_path;
	struct s_parser	*next;
	struct s_parser	*prev;
}	t_parser;

typedef struct s_gdata
{
	char	g_error_status;
	int		g_exit_status;
	char	**our_env;
}	t_gdata;

t_gdata			g_all;

typedef char	t_flag;

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
		TOKEN_RDAMB
	} e_type;
	char			*word;
	char			*meta;
	char			*old_word;
	char			*heredoc;
	t_flag			h_quoted;
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
	t_parser *parsing;
}	t_meta;

typedef	struct s_files
{
	char	*name;
	int		mode;
	int		permission;
}	t_files;

void	ft_dlstadd_back2(t_parser **lst, t_parser *new);
void	ft_dlstadd_back(t_token **lst, t_token *new);
void	join_free(char *s1, char *s2, short flag);
void	ft_trans_meta(char *av, t_meta *meta);
void	ft_heredoc(t_token *tokens, int fd);
void	ft_init_meta(t_meta *meta);
void    ft_expand(t_token *tokens);
void	lexer_scan(t_meta *meta);
void	ft_putstr(char *str);
void	error_set(int nb);
char	**trans_to_string(t_meta *meta, int pos, int len);
char	*ft_select(char **o_env, char *read_ln, int len);
char	*ft_strjoin_free(char *s1, char *s2, short flag);
char	**add_change(char **tab, char *str);
char	*ft_hexpand(char **read_ln);
int		ft_quote(char *av, t_meta *meta, int pos);
int		check_word(t_meta *meta, int pos);
int		ft_strcmp(char *s1, char *s2);
int		is_char(char c);
t_token	*ft_dlstlast(t_token *lst);

#endif

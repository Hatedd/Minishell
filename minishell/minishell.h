/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouizar <mouizar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 00:05:08 by yobenali          #+#    #+#             */
/*   Updated: 2022/11/19 20:36:54 by mouizar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include "./libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

# define TRUE		1
# define FALSE		0
# define EXPAND		0
# define NO_EXPAND	1

# define EXEC		1
# define NOEXEC		0
# define FIRST		1
# define SECOND		2
# define ALL		3

# define READ		0
# define WRITE		1

typedef void	(*t_sig) (int);
typedef char	t_flag;

typedef struct s_parser
{
	char			flag;
	int				index;
	int				pipe[2];
	int				in_fd;
	int				out_fd;
	char			**av;
	char			**path;
	int				exec_flag;
	struct s_parser	*next;
	struct s_parser	*prev;
}	t_parser;

typedef struct s_gdata
{
	char	g_error_status;
	int		g_exit_status;
	char	**our_env;
    t_list	*g_lst_env;
	int     tmpp_in;
	int     tmpp_out;
	char    **path;
	int		flag_vide_env;
}	t_gdata;
//call the fuction tha wizar build his env with in the linked list
t_gdata			g_all;

typedef struct s_token
{
	enum
	{
		T_WORD,
		T_PIPE,
		T_DREAD,
		T_READ,
		T_DWRITE,
		T_WRITE,
		T_AMBRD
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
	char		*meta_str;
	char		*cmd;
	int			len;
	int			i;
	int			flag;
	t_token		*tokens;
	t_parser	*parsing;
}	t_meta;

typedef struct s_files
{
	char	*name;
	int		mode;
}	t_files;

// parsing
void		ft_ambrd_parsing(t_token *tmp, t_parser *parsing);
void		ft_dlstadd_back2(t_parser **lst, t_parser *new);
void		ft_delimiter_name(t_token *tokens, char *name);
void		ft_delimiter_name(t_token *tokens, char *name);
void		ft_dlstadd_back(t_token **lst, t_token *new);
void		join_free(char *s1, char *s2, short flag);
void		ft_trans_meta(char *av, t_meta *meta);
void		ft_heredoc(t_token *tokens, int fd);
void		ft_starting_inti(char **env);
void		error_check(t_token *tokens);
void		ft_init_meta(t_meta *meta);
void		ft_expand(t_token *tokens);
void		lexer_scan(t_meta *meta);
void		ft_our_env(char **env);
void		ft_handler(int macro);
void		ft_putstr(char *str);
void		ft_sig_error(int nb);
void		error_set(int nb);

char		**trans_to_string(t_meta *meta, int pos, int len);
char		*ft_strjoin_free(char *s1, char *s2, short flag);
char		*ft_select(char **o_env, char *read_ln, int len);
char		**add_change(char **tab, char *str);
char		*ft_hexpand(char **read_ln);
char		**ft_split2(char *str);

int			ft_matchnmatch(char *buffer, char *mbuffer, char *charset, \
				char match);
int			ft_predirection(t_token *tokens, t_parser *parser, \
				t_files *redirects);
int			ft_ambrd_error(t_token *temp, t_parser *parser, \
				t_files *redirects);
int			ft_opening_check(t_files *redirects, t_parser **parsing, char flag);
int			ft_quote(char *av, t_meta *meta, int pos);
int			check_word(t_meta *meta, int pos);
int			ft_strcmp(char *s1, char *s2);
int			ft_heredoc_nb(t_token *lst);
int			main_helper(t_meta *meta);
int			is_char(char c);

t_parser	*init_parser(int i);
t_token		*ft_dlstlast(t_token *lst);
t_parser	*ft_dlstlast2(t_parser *lst);

// execution
t_list	*sorting(t_list *lst, int (*ft_cmpar)(char *, char *));
int		ft_cmpar(char *s1, char *s2);
void	printing(char *content);
int		valid_export(char *str);
void	ft_build_env(void);
int		ft_found_inenv(t_list *lst, char *str);
int		ft_search_variable(char *s1, char *s2);
void	ft_modify_var(t_list *lst_env, char *value);
int		ft_cmpar(char *s1, char *s2);
int		ft_same_c(char c1, char c2);
int		ft_search_variable(char *s1, char *s2);
int		ft_found_inenv(t_list *lst, char *str);
void	ft_modify_var(t_list *lst_env, char *value);
void	ft_free_array(char **str);
void	ft_build_env(void);
void	bult_in(t_parser *cmdl);
void	ft_parser_export(t_parser *cmdl);
void	execution(t_parser *cmdl);
void	ft_parser_cd(t_parser *cmdl);
int		ft_valid_n(char *str);
void	ft_parser_echo(t_parser *cmdl);
void	ft_parser_env(t_parser *cmdl);
void	ft_parser_export(t_parser *cmdl);
void	unset_var(t_list **lst, char *str);
void	ft_parser_unset(t_parser *cmdl);
void	ft_parser_env(t_parser *cmdl);
void	ft_parser_unset(t_parser *cmdl);
void	ft_parser_pwd(void);
void	ft_exit_parser(t_parser *cmdl);
int		ft_atoi_exit(const char *str);
void	free_lst(t_list **lst);
int		ft_lstsize_cmd(t_parser *lst);
int		ft_egal(char c);
int		ft_space(char c);
void	ft_generate_errors(char *str, int flag);
void	ft_generate_erro2(t_parser *tmp, int flag);
int		ft_multi_pipes(t_parser *tmp);
void	ft_redirection(t_parser *tmp);
int		ft_singl_cmd(t_parser *tmp);
int		ft_lstsize_cmd(t_parser *lst);
int		is_bultin(char *str);
int		ck_if_bultin(t_parser *cmdl);
char	*ft_found_path(void);
char	*join_frees1(char *s1, char *s2);
char	**generate_path(char **path, t_parser *cmdl, char *slash_path);
char	**ft_split_path(t_parser *cmdl);
int		single_command(t_parser *tmp);
int		multiple_command(t_parser *tmp);
void	ft_wait(int id);
void	ft_redirection(t_parser *tmp);
void	ft_process_communication(t_parser *tmp);
void	ft_if_bultin(t_parser *tmp);
void	ft_if_not_bultin(t_parser *tmp);
int		ft_multi_pipes(t_parser *tmp);
int		ft_singl_cmd(t_parser *tmp);
void	ft_exit_error(t_parser *cmdl, int flag);
char	*join_and_free(char *s1, char *s2);
#endif

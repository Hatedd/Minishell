/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <yobenali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 00:05:19 by yobenali          #+#    #+#             */
/*   Updated: 2022/11/12 01:01:49 by yobenali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_error(t_token *tmp)
{
	int	i;
	int	j;

	if (tmp->next->e_type == TOKEN_WORD)
	{
		tmp = tmp->next;
		i = 0;
		j = ft_strlen(tmp->meta);
		tmp->heredoc = ft_calloc(sizeof(char), (j + 1));
		if (!tmp->heredoc)
			return ;
		j = 0;
		while (tmp->meta[i])
		{
			if ((tmp->meta[i] == 'd' || tmp->meta[i] == 's'))
				i++;
			else
				tmp->heredoc[j++] = tmp->word[i++];
		}
		(j < i) && tmp->h_quoted++;
	}
}

void	redirections_error(t_token *tmp)
{
	write(2, "syntax error near unexpected token `", 37);
	if (tmp->next == NULL)
		ft_putstr_fd("newline'\n", 2);
	else
	{
		ft_putstr_fd(tmp->next->word, 2);
		write(2, "'\n", 2);
	}
	return (error_set(258));
}

void	error_check(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->e_type == TOKEN_PIPE && (tmp->prev == NULL \
			|| tmp->next == NULL))
		{
			write(2, "syntax error near unexpected token `|'\n", 39);
			return (error_set(258));
		}
		else if (tmp->e_type == TOKEN_PIPE && tmp->next->e_type == TOKEN_PIPE)
		{
			write(2, "syntax error near unexpected token `|'\n", 39);
			return (error_set(258));
		}
		else if ((tmp->e_type == TOKEN_DREAD || tmp->e_type == TOKEN_READ \
			|| tmp->e_type == TOKEN_DWRITE || tmp->e_type == TOKEN_WRITE) \
			&& (tmp->next == NULL || tmp->next->e_type != TOKEN_WORD))
			return (redirections_error(tmp));
		if (tmp->e_type == TOKEN_DREAD)
			heredoc_error(tmp);
		tmp = tmp->next;
	}
}

void	ft_our_env(char **env)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	while (env[i])
		i++;
	g_all.our_env = ft_calloc((i + 1), sizeof(char *));
	if (!g_all.our_env)
		return ;
	i = 0;
	while (env[i])
	{
		j = 0;
		len = ft_strlen(env[i]);
		g_all.our_env[i] = ft_calloc((len + 1), sizeof(char *));
		if (!g_all.our_env[i])
			return ;
		while (env[i][j])
		{
			g_all.our_env[i][j] = env[i][j];
			j++;
		}
		i++;
	}
}

int	ft_counting_cmd(t_token * tokens)
{
	t_token *tmp;
	t_token *new;
	int	i;

	i = 0;
	tmp = tokens;
	while (tmp)
	{
		if (tmp->e_type == TOKEN_PIPE)
			i++;	
		tmp = tmp->next;
	}
	return (i);
}

t_parser	*init_parser(void)
{
	t_parser	*head;

	head = (t_parser *)ft_calloc(sizeof(t_parser), 1);
	if (!head)
		return (NULL);
	head->flag = 1;
	head->index = 0;
	head->pipe[0] = 0;
	head->pipe[1] = 0;
	head->in_fd = 0;
	head->out_fd = 0;	
	head->av = NULL;
	head->c_path = NULL;
	head->next = NULL;
	head->prev = NULL;
	return (head);
}

void	ft_redirection(t_token *tokens, t_parser *parser)
{
	if (tokens->e_type == TOKEN_READ)
		parser->in_fd = open(tokens->next->word, O_RDONLY, 0600);
	else if (tokens->next->e_type == TOKEN_WRITE)
		parser->out_fd = open(tokens->next->word, O_CREAT, O_RDWR, 0600);
}

void	ft_parser(t_token *tokens, t_parser *parser)
{
	t_token *tmp;
	t_parser *temp;
	int	i;

	i = 0;
	tmp = tokens;
	temp = init_parser();
	while (tmp)
	{
		if((tmp->e_type == TOKEN_READ || tmp->e_type == TOKEN_WRITE) && tmp->next->e_type == TOKEN_WORD)
			ft_redirection(tmp, temp);
		else if (tmp->e_type == TOKEN_PIPE)
			temp->index = i++;
		tmp = tmp->next;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_meta	meta;
	t_token	*tmp;
	int		fd;

	(void)argc;
	(void)argv;
	tmp = NULL;
	fd = 0;
	ft_our_env(env);
	while (TRUE)
	{
		ft_init_meta(&meta);
		if (g_all.g_error_status)
			continue ;
		lexer_scan(&meta);
		error_check(meta.tokens);
		if (g_all.g_error_status)
			continue ;
		ft_heredoc(meta.tokens, fd);
		if (g_all.g_error_status)
			continue ;
		ft_expand(meta.tokens);
		if (g_all.g_error_status)
			continue ;
		// ft_counting_cmd(meta.tokens);
		// ft_parser(meta.tokens, meta.parser);
		//first you need to count how mani comands you have and allocat a linked list
		//that you will send to wizare in the coresponding count
		// example cat << l > out | echo helo | wc | ls
		//in this example we have 4 comands so we will allocate 4 nodes that will 
		// contain the redirection data and the command and it's arguments.
		/*
		here you need to make a function tha treat the redirection as follows:
		you need to check there permetions and whether they existe or not in turn using
		the function access and if all the redirections are valid then you will open 
		the last redirection file for read and for write respectevly.
		example : 
			echo > out1 > out2 < in1 >> out3 < in2 > out4 << in3 | ...
			in this case if we keep in mind that all the input files exist and all the out
			and in files have the right permissions, your fuction will open the files :
			in3 and out4
			-in case of an error at some point in the redirection processing you skip
			to the next pipe and repeat the process again
		*/
		tmp = meta.tokens;
		while (tmp)
		{
			printf("-----------------------------\n");
			printf("the word is |%s|\n", tmp->word);
			printf("the meta is |%s|\n", tmp->meta);
			printf("the type is |%u|\n", tmp->e_type);
			tmp = tmp->next;
		}
	}
	return (0);
}

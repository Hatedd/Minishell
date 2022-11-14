/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <yobenali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 00:05:19 by yobenali          #+#    #+#             */
/*   Updated: 2022/11/14 01:51:59 by yobenali         ###   ########.fr       */
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
		write(2, "\n", 2);
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
	int	i;

	i = 1;
	tmp = tokens;
	while (tmp)
	{
		if (tmp->e_type == TOKEN_PIPE)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

t_parser	*init_parser(int i)
{
	t_parser	*head;

	head = (t_parser *)ft_calloc(sizeof(t_parser), 1);
	if (!head)
		return (NULL);
	head->flag = EXEC;
	head->index = i;
	head->in_fd = -2;
	head->out_fd = -2;	
	head->av = NULL;
	head->c_path = NULL;
	head->next = NULL;
	head->prev = NULL;
	return (head);
}

void	filling_data(t_files *redirects, char *name, int mode)
{
	if (*redirects->name)
		free (redirects->name);
	redirects->name = ft_strdup(name);
	redirects->mode = mode; 
}

int	ft_redirection(t_token *tokens, t_parser *parser, t_files *redirects)
{
	t_files *tmp;
	t_token *temp;
	int		fd;

	tmp = redirects;
	temp = tokens;
	if (temp->e_type == TOKEN_READ && temp->next->e_type == TOKEN_WORD)
	{	
		if (access(temp->next->word, F_OK) != 0 || access(temp->next->word, R_OK) != 0)
		{
			redirects[READ].mode = -1;
			parser->flag = NOEXEC;
			return (1);
		}
		filling_data(&tmp[READ], temp->next->word, O_RDONLY);
	}
	else if ((temp->e_type == TOKEN_WRITE || temp->e_type == TOKEN_DWRITE) && temp->next->e_type == TOKEN_READ)
	{
		if (access(temp->next->word, F_OK) != 0)
		{
			fd = open(temp->next->word, O_CREAT | O_RDWR, 0600);
			if (fd == -1)
			{
				ft_putstr_fd("minishell: faild to creat file\n", 2);
				error_set(13);
				return (1);
			}
			close(fd);
		}
		else if (access(temp->next->word, W_OK) != 0)
		{
			redirects[WRITE].mode = -1;
			parser->flag = NOEXEC;
			return (1);
		}
		if (temp->e_type == TOKEN_WRITE)
			filling_data(&tmp[WRITE], temp->next->word, O_TRUNC | O_WRONLY);
		else if (temp->e_type == TOKEN_DWRITE)
			filling_data(&tmp[WRITE], temp->next->word, O_APPEND | O_WRONLY);
	}
	return (0);
}

t_parser	*creat_list(t_token *tokens)
{
	int			i;
	int			nb;
	t_parser	*temp;

	nb = ft_counting_cmd(tokens);
	i = 0;
	temp = NULL;
	while (nb)
	{
		ft_dlstadd_back2(&temp, init_parser(i));
		if (i == 0)
			temp->in_fd = 0;
		nb--;
		i++;
	}
	ft_dlstlast2(temp)->out_fd = 1;
	return (temp);
}

void	ft_opening_fd(t_files *redirects, t_parser *parsing, int type)
{
	if (type == READ)
	{
		parsing->in_fd = open(redirects->name, redirects->mode);
		if (parsing->in_fd == -1)
		{
			ft_putstr_fd("minishell: faild to creat file\n", 2);
			error_set(13);
		}
	}
	else if (type == WRITE)
	{
		parsing->out_fd = open(redirects->name, redirects->mode);
		if (parsing->out_fd == -1)
		{
			ft_putstr_fd("minishell: faild to creat file\n", 2);
			error_set(13);
		}
	}
}

void	ft_parser(t_token *tokens, t_parser *parsing)
{
	t_token		*tmp;
	t_files		*redirects;

	redirects = ft_calloc(sizeof(t_files), 2);
	redirects[READ].mode = -1;
	redirects[WRITE].mode = -1;
	tmp = tokens;
	while (tmp)
	{
		if (tmp->e_type == TOKEN_WORD)
			parsing->av = add_change(parsing->av, tmp->word);
		else if (tmp->e_type == TOKEN_READ || \
				tmp->e_type == TOKEN_WRITE || \
				tmp->e_type == TOKEN_DWRITE || \
				tmp->e_type == TOKEN_DREAD)
		{
			if (ft_redirection(tmp, parsing, redirects))
			{
				if (g_all.g_error_status)
					return ;
				while (tmp && tmp->e_type != TOKEN_PIPE)
					tmp = tmp->next;
				continue;
			}
		}
		else if (tmp->e_type == TOKEN_PIPE)
		{
			if (redirects[READ].mode != -1)
			{
				ft_opening_fd(redirects, parsing, READ);
			}
			if (redirects[WRITE].mode != -1)
			{
				ft_opening_fd(redirects, parsing, WRITE);
			}
			parsing = parsing->next;
		}
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
		if (meta.tokens == NULL)
			continue ;
		error_check(meta.tokens);
		if (g_all.g_error_status)
			continue ;
		ft_heredoc(meta.tokens, fd);
		if (g_all.g_error_status)
			continue ;
		ft_expand(meta.tokens);
		if (g_all.g_error_status)
			continue ;
		meta.parsing = creat_list(meta.tokens);
		ft_parser(meta.tokens, meta.parsing);
		if (g_all.g_error_status)
			continue ;
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

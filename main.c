/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <yobenali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 00:05:19 by yobenali          #+#    #+#             */
/*   Updated: 2022/11/02 02:23:18 by yobenali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

t_gdata	g_all;

void	ft_putchar(char c)
{
	write(2, &c, 1);
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return ;
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
}

int	is_char(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int	ft_quote(char *av, t_meta *meta, int pos)
{
	if (av[pos] == '\'')
	{
		meta->meta_str[pos++] = 's';
		while (av[pos] && av[pos] != '\'')
		{
			meta->meta_str[pos] = 'Q';
			pos++;
		}
		if (av[pos] == '\0')
		{
			write(2, "quotes not closed\n", 18);
			g_all.g_error_status = EXIT_FAILURE;
			g_all.g_exit_status = 258;
			return (EXIT_FAILURE);
		}
		meta->meta_str[pos] = 's';
	}
	else if (av[pos] == '"')
	{
		meta->meta_str[pos++] = 'd';
		while (av[pos] && av[pos] != '"')
		{
			if (av[pos] == '$')
				meta->meta_str[pos] = 'x';
			else
				meta->meta_str[pos] = 'q';
			pos++;
		}
		if (av[pos] == '\0')
		{
			write(2, "quotes not closed\n", 18);
			g_all.g_error_status = EXIT_FAILURE;
			g_all.g_exit_status = 258;
			return (EXIT_FAILURE);
		}
		meta->meta_str[pos] = 'd';
	}
	return (pos);
}

void	ft_trans_meta(char *av, t_meta *meta)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (is_char(av[i]))
			meta->meta_str[i] = 'u';
		else if (av[i] == '|')
			meta->meta_str[i] = 'p';
		else if (av[i] == '<')
			meta->meta_str[i] = 'r';
		else if (av[i] == '>')
			meta->meta_str[i] = 'w';
		else if (av[i] == ' ' || av[i] == '\t' || av[i] == '\n')
			meta->meta_str[i] = 'b';
		else if (av[i] == '$')
		{
			if (av[i + 1] && is_char(av [i + 1]))
			{
				meta->meta_str[i] = 'x';
			}
			else if (av[i + 1] && av[i + 1] == '?')
				meta->meta_str[i] = 'X';
			else
				meta->meta_str[i] = 'u';
		}
		else if (av[i] == '\'' || av[i] == '"')
			i = ft_quote(av, meta, i);
		else
			meta->meta_str[i] = 'u';
		if (g_all.g_error_status)
			return ;
		i++;
	}
}

void	ft_init_meta(t_meta *meta)
{
	meta->cmd = readline("minishell$ ");
	if (meta->cmd == NULL)
		exit (g_all.g_exit_status);// hna radi dir exit bakhir exit status 3andek
	add_history(meta->cmd);
	meta->len = ft_strlen(meta->cmd);
	meta->meta_str = ft_calloc(sizeof(char), meta->len + 1);
	meta->flag = 0;
	meta->i = 0;
	g_all.g_error_status = 0;
	meta->tokens = NULL; //"/dont forget to free the list" before making it null
	ft_trans_meta(meta->cmd, meta);
}

void	error_check(t_token *tokens)
{
	t_token *tmp;
	int		i;
	int 	j;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->e_type == TOKEN_PIPE && (tmp->prev == NULL || tmp->next == NULL))
		{
			write(2, "syntax error near unexpected token `|'\n", 39);
			g_all.g_exit_status = 258;
			g_all.g_error_status = EXIT_FAILURE;
			return ;
		}
		else if (tmp->e_type == TOKEN_PIPE && tmp->next->e_type == TOKEN_PIPE)
		{
			write(2, "syntax error near unexpected token `|'\n", 39);
			g_all.g_exit_status = 258;
			g_all.g_error_status = EXIT_FAILURE;
			return ;
		}
		else if ((tmp->e_type == TOKEN_DREAD || tmp->e_type == TOKEN_READ
			|| tmp->e_type == TOKEN_DWRITE || tmp->e_type == TOKEN_WRITE)
			&& (tmp->next == NULL || tmp->next->e_type != TOKEN_WORD))
		{	
			write(2, "syntax error near unexpected token `", 37);
			if (tmp->next == NULL)
				ft_putstr_fd("newline'\n", 2);
			else
			{
				ft_putstr_fd(tmp->next->word, 2);
				write(2, "'\n", 2);
			}
			g_all.g_exit_status = 258;
			g_all.g_error_status = EXIT_FAILURE;
			return ;
		}
		if (tmp->e_type == TOKEN_DREAD)
		{
			if (tmp->next->e_type == TOKEN_WORD)
			{
				tmp = tmp->next;
				i = 0;
				j = ft_strlen(tmp->meta);
				printf("%d\n", j);
				tmp->heredoc = malloc(sizeof(char) * (j + 1));
				if (!tmp)
					return ;
				j = 0;				
				while (tmp->meta[i] && (tmp->meta[i] == 'd' || tmp->meta[i] == 's'))
				{
					if (tmp->meta[i] == 'd' && tmp->meta[i])
					{
						i++;
						while (tmp->meta[i] != 'd')
						{
							tmp->heredoc[j] = tmp->word[i];
							i++;
							j++;
						}
						i++;
					}
					else if (tmp->meta[i] == 's' && tmp->meta[i])
					{
						i++;
						while (tmp->meta[i] != 's')
						{
							tmp->heredoc[j] = tmp->word[i];
							i++;
							j++;
						}
						i++;
					}
					else if (tmp->meta[i] != 's' && tmp->meta[i] != 'd' && tmp->meta[i])
					{
						tmp->heredoc[j] = tmp->word[i];
						i++;
						j++;
					}
				}
				tmp->heredoc[j] = '0';
				// printf("%s\n", tmp->heredoc);
			}
		}
		tmp = tmp->next;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_meta	meta;
	t_token	*tmp;

	(void)argc;
	(void)argv;
	(void)env;
	tmp = NULL;
	while (TRUE)
	{
		ft_init_meta(&meta);
		if (g_all.g_error_status)
			continue ;
		lexer_scan(&meta);
		error_check(meta.tokens);
		if (g_all.g_error_status)
			continue ;
		tmp = meta.tokens;
		while (tmp)
		{
			printf("-----------------------------\n");
			printf("the word is ¢ %s ¢\n", tmp->word);
			printf("the meta is ¢ %s ¢\n", tmp->meta);
			printf("the type is ¢ %u ¢\n", tmp->e_type);
			tmp = tmp->next;
		}
	}
	return (0);
}

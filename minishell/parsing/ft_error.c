/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <yobenali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 17:24:33 by yobenali          #+#    #+#             */
/*   Updated: 2022/11/20 22:54:32 by yobenali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	heredoc_error(t_token *tmp)
{
	int	i;
	int	j;

	if (tmp->next->e_type == T_WORD)
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
		if (tmp->e_type == T_PIPE && (tmp->prev == NULL \
			|| tmp->next == NULL))
		{
			write(2, "syntax error near unexpected token `|'\n", 39);
			return (error_set(258));
		}
		else if (tmp->e_type == T_PIPE && tmp->next->e_type == T_PIPE)
		{
			write(2, "syntax error near unexpected token `|'\n", 39);
			return (error_set(258));
		}
		else if ((tmp->e_type == T_DREAD || tmp->e_type == T_READ \
			|| tmp->e_type == T_DWRITE || tmp->e_type == T_WRITE) \
			&& (tmp->next == NULL || tmp->next->e_type != T_WORD))
			return (redirections_error(tmp));
		if (tmp->e_type == T_DREAD)
			heredoc_error(tmp);
		tmp = tmp->next;
	}
}

int	ft_ambrd_error(t_token *temp, t_parser *parser, t_files *redirects)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(temp->next->old_word, 2);
	ft_putstr_fd(": ambiguous redirect\n", 2);
	redirects[WRITE].mode = -1;
	parser->flag = NOEXEC;
	return (1);
}

void	error_set(int nb)
{
	g_all.g_exit_status = nb;
	g_all.g_error_status = EXIT_FAILURE;
	return ;
}

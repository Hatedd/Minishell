/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <yobenali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:05:03 by yobenali          #+#    #+#             */
/*   Updated: 2022/11/19 03:36:03 by yobenali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*init_token(int type, char **data)
{
	t_token	*head;
	int		i;

	i = -1;
	head = (t_token *)ft_calloc(sizeof(t_token), 1);
	if (!head || !data)
		return (NULL);
	head->e_type = type;
	head->word = ft_strdup(data[0]);
	head->meta = ft_strdup(data[1]);
	while (data[++i])
		free(data[i]);
	free(data);
	head->h_quoted = 0;
	head->heredoc = NULL;
	head->prev = NULL;
	head->next = NULL;
	return (head);
}

void	ft_lexer_write(t_meta *meta)
{
	if (meta->meta_str[meta->i + 1] == 'w')
	{
		ft_dlstadd_back(&meta->tokens, init_token(T_DWRITE,
				trans_to_string(meta, meta->i, meta->i + 2)));
		meta->i += 2;
	}
	else
	{
		ft_dlstadd_back(&meta->tokens, init_token(T_WRITE,
				trans_to_string(meta, meta->i, meta->i + 1)));
		meta->i++;
	}
}

void	ft_lexer_read(t_meta *meta)
{	
	if (meta->meta_str[meta->i + 1] == 'r')
	{
		ft_dlstadd_back(&meta->tokens, init_token(T_DREAD,
				trans_to_string(meta, meta->i, meta->i + 2)));
		meta->i += 2;
	}
	else
	{
		ft_dlstadd_back(&meta->tokens, init_token(T_READ,
				trans_to_string(meta, meta->i, meta->i + 1)));
		meta->i++;
	}
}

void	ft_lexer_word(t_meta *meta)
{
	int	len;

	len = 1;
	while (check_word(meta, meta->i + len))
		len++;
	ft_dlstadd_back(&meta->tokens, init_token(T_WORD,
			trans_to_string(meta, meta->i, meta->i + len)));
	meta->i = meta->i + len;
}

void	lexer_scan(t_meta *meta)
{
	while (meta->meta_str[meta->i] != '\0')
	{
		if (meta->meta_str[meta->i] == 'b')
			meta->i++;
		if (check_word(meta, meta->i))
			ft_lexer_word(meta);
		else if (meta->meta_str[meta->i] == 'p')
		{
			ft_dlstadd_back(&meta->tokens, init_token(T_PIPE,
					trans_to_string(meta, meta->i, meta->i + 1)));
			meta->i++;
		}
		else if (meta->meta_str[meta->i] == 'w')
			ft_lexer_write(meta);
		else if (meta->meta_str[meta->i] == 'r')
			ft_lexer_read(meta);
	}
}

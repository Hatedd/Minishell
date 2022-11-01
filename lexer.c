/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <yobenali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:05:03 by yobenali          #+#    #+#             */
/*   Updated: 2022/10/31 16:49:05 by yobenali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_word(t_meta *meta, int pos)
{
	if (meta->meta_str[pos] && (meta->meta_str[pos] != 'b'
			&& meta->meta_str[pos] != 'p' && meta->meta_str[pos] != 'w'
			&& meta->meta_str[pos] != 'r'))
		return (1);
	return (0);
}

char	**trans_to_string(t_meta *meta, int pos, int len)
{
	char	**tab;
	int		i;
	int		cal;

	i = 0;
	cal = 0;
	tab = malloc(sizeof(char *) * 3);
	if (!tab)
		return (NULL);
	cal = len - pos;
	cal++;
	tab[0] = ft_calloc(cal + 1, sizeof(char));
	tab[1] = ft_calloc(cal + 1, sizeof(char));
	tab[2] = NULL;
	while (pos < len && meta->cmd[pos] != '\0')
	{
		tab[0][i] = meta->cmd[pos];
		tab[1][i] = meta->meta_str[pos];
		pos++;
		i++;
	}
	return (tab);
}

t_token	*init_token(int type, char **data)
{
	t_token	*head;

	head = (t_token *)malloc(sizeof(t_token));
	if (!head || !data)
		return (NULL);
	head->e_type = type;
	head->word = *data;
	data++;
	head->meta = *data;
	head->prev = NULL;
	head->next = NULL;
	return (head);
}

t_token	*lexer_scan(t_meta *meta)
{
	int	j;

	while (meta->meta_str[meta->i] != '\0')
	{
		if (meta->meta_str[meta->i] == 'b')
			meta->i++;
		if (check_word(meta, meta->i))
		{
			j = 1;
			while (check_word(meta, meta->i + j))
				j++;
			ft_dlstadd_back(&meta->tokens, init_token(TOKEN_WORD,
					trans_to_string(meta, meta->i, meta->i + j)));
			meta->i = meta->i + j;
		}
		else if (meta->meta_str[meta->i] == 'p')
		{
			ft_dlstadd_back(&meta->tokens, init_token(TOKEN_PIPE,
					trans_to_string(meta, meta->i, meta->i + 1)));
			meta->i++;
		}
		else if (meta->meta_str[meta->i] == 'w')
		{
			if (meta->meta_str[meta->i + 1] == 'w')
			{
				ft_dlstadd_back(&meta->tokens, init_token(TOKEN_DWRITE,
						trans_to_string(meta, meta->i, meta->i + 2)));
				meta->i += 2;
			}
			else
			{
				ft_dlstadd_back(&meta->tokens, init_token(TOKEN_WRITE,
						trans_to_string(meta, meta->i, meta->i + 1)));
				meta->i++;
			}
		}
		else if (meta->meta_str[meta->i] == 'r')
		{
			if (meta->meta_str[meta->i + 1] == 'r')
			{
				ft_dlstadd_back(&meta->tokens, init_token(TOKEN_DREAD,
						trans_to_string(meta, meta->i, meta->i + 2)));
				meta->i += 2;
			}
			else
			{
				ft_dlstadd_back(&meta->tokens, init_token(TOKEN_READ,
						trans_to_string(meta, meta->i, meta->i + 1)));
				meta->i++;
			}
		}
	}
	return (NULL);
}

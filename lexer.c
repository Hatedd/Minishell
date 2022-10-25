/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <yobenali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:05:03 by yobenali          #+#    #+#             */
/*   Updated: 2022/10/25 01:06:57 by yobenali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_char_to_string(char **tab, t_meta *meta, int pos)
{
	tab[0] = ft_calloc(2, sizeof(char));
	tab[1] = ft_calloc(2, sizeof(char));
	tab[0][0] = meta->cmd[pos];
	tab[1][0] = meta->meta_str[pos];
	return (tab);
}

int	check_word(t_meta *meta, int pos)
{
    if (meta->meta_str[pos] == 's' || meta->meta_str[pos] == 'd')
        return (1);
    return (0);
}

char	**ft_check_quote(t_meta *meta, int pos, char **tab, int cal)
{
	int	i;

	i = 0;
	tab[0] = ft_calloc(cal, sizeof(char));
	tab[1] = ft_calloc(cal, sizeof(char));
	while (meta->meta_str[pos] != '\'' || meta->meta_str[pos] != '"')
	{
		tab[0][i] = meta->cmd[pos];
		tab[1][i] = meta->meta_str[pos];
		pos++;
		i++;	
	}
	tab[2] = 0;
	return (tab);
}

char	**trans_to_string(t_meta *meta, int pos, int len)
{
	char	**tab;
	int		i;
	int 	cal;

	i = 0;
	cal = 0;
	tab = malloc(sizeof(char *) * 3);
	if (!tab)
		return (NULL);
	// if (pos == len - 2)
	// 	return (ft_char_to_string(tab, meta, pos));
	cal = len - pos;
	if (check_word(meta, pos))
		return (ft_check_quote(meta, pos, tab, cal));
	else
		cal++;
	tab[0] = ft_calloc(cal, sizeof(char));
	tab[1] = ft_calloc(cal, sizeof(char));
    tab[2] = ft_calloc(1, sizeof(char));
	while (pos < len)
    {
        tab[0][i] = meta->cmd[pos];
		tab[1][i] = meta->meta_str[pos];
        pos++;
		i++;
    }
	// printf("word :%s\n", *tab);
	// tab++;
	// printf("meta :%s\n", *tab);
    return (tab);
}

t_token	*init_token(int type, char **data)
{
    int 	i;
	t_token *head;
	
    i = 0;
	head = (t_token *)malloc(sizeof(t_token));
	if (!head)
		return (NULL);
	head->prev = NULL;
    head->type = type;
	// while (data[0][i])
	// {
	printf("type :%d\n", head->type);
	head->word = *data;
	printf("word :%s\n", *data);
	data++;
	head->meta = *data;
	printf("meta :%s\n", *data);
		// i++;
	// }
	// data++;
	head->next = NULL;
	return (head);
}

void	get_token(t_token *tokens, t_token *lst, t_meta *meta)
{
	t_token *tmp;
	t_token *back;
	
	tmp = NULL;
	back = NULL;
	if(meta->flag == 0)
	{
		tokens = lst;
		meta->flag++;
		return ;
	}
	back = tokens;
	if (back->next == NULL)
	{
		back->next = lst;
		lst->prev = tokens;
	}
	else
	{
		ft_lstlast(back)->next = lst;
		tmp = back;
		lst->prev = back->next;
	}
}

void    lexer_scan(t_meta *meta)
{
    int i = 0;
    int j;
	
    while (meta->meta_str[i] != '\0' && i < meta->len)
    {
        if (meta->meta_str[i] == 'b')
            i++;
        if (check_word(meta, i) || meta->meta_str[i] == 'u')
        {
            j = 1;
            while (meta->meta_str[i + j] == 'u')
                 j++;
				printf("word lengh is %d\n", j);
           // if (i < i + j)
				// get_token(meta->tokens ,
				init_token(TOKEN_WORD, trans_to_string(meta, i, i + j));
			i = i + j;
		}
		else if (meta->meta_str[i] == '|')
		{
			get_token(meta->tokens, init_token(TOKEN_PIPE, trans_to_string(meta, i, i + 2)), meta);
			i++;
		}
		else if (meta->meta_str[i] == '>')
		{
			if (meta->meta_str[i + 1] == '>')
			{
				get_token(meta->tokens, init_token(TOKEN_DWRITE, trans_to_string(meta, i, i + 3)), meta);
				i = +2;
			}
			else
			{
				get_token(meta->tokens, init_token(TOKEN_WRITE, trans_to_string(meta, i, i + 2)), meta);
				i++;
			}
		}
		else if (meta->meta_str[i] == '<')
		{
			if (meta->meta_str[i + 1] == '<')
			{
				get_token(meta->tokens, init_token(TOKEN_DREAD, trans_to_string(meta, i, i + 3)), meta);
				i = +2;
			}
			else
			{
				get_token(meta->tokens, init_token(TOKEN_READ, trans_to_string(meta, i, i + 2)), meta);
				i++;
			}
		}
    }
	t_token *tmp = meta->tokens;
	printf("token :%d     word : %s     meta : %s", tmp->type, tmp->word, tmp->meta);
}
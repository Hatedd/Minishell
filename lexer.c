/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <yobenali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:05:03 by yobenali          #+#    #+#             */
/*   Updated: 2022/10/23 19:20:50 by yobenali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_char_to_string(char **tab, t_meta *meta, int pos)
{
	tab[0] = ft_calloc(2 * sizeof(char));
	tab[1] = ft_calloc(2 * sizeof(char));
	tab[0][0] = meta->cmd[pos];
	tab[1][0] = meta->meta_str[pos];
	return (tab);
}

char	**trans_to_string(t_meta *meta, t_token *token, int pos, int len)
{
	char	**tab;
	int		i;
	int 	cal;

	i = 0;
	cal = 0;
	tab = malloc(sizeof(char *) * 3);
	if (!tab)
		return (NULL);
	if (len == 1)
		ft_char_to_string(tab, meta, pos);
	cal = len - pos;
	if (!check_word(meta, pos))
		cal++;
	tab[0] = ft_calloc(cal * sizeof(char));
	tab[1] = ft_calloc(cal * sizeof(char));
    while (pos < len && len != 1)
    {
        tab[0][i] = meta->cmd[pos];
		tab[1][i] = meta->meta_str[pos];
        pos++;
		i++;
    }
	tab[2] = '\0';
    return (tab);
}

t_token	*init_token(int type, char **data, t_meta *meta)
{
    int 	i;
    int 	j;
	t_token *head;
	
    i = 0;
	head = (t_token *)malloc(sizeof(t_token));
	if (!head)
		return (NULL);
	head->prev = NULL;
    head->type = type;
	while (data[0][i])
	{
		head->word[i] = data[0][i];
		head->meta[i] = data[1][i];
		i++;
	}
	head->next = NULL;
	return (head);
}

int	check_word(t_meta *meta, int pos)
{
    if (meta->meta_str[pos] == 's' || meta->meta_str[pos] == 'd')
        return (1);
    return (0);
}

void	get_token(t_token *tokens, t_token *lst, t_meta *meta)
{
	t_token *tmp;
	t_token *back;
	
	tmp = NULL;
	back = NULL;
	if(meta->flag == 0)
	{
		tokens = lst->prev;
		meta->flag++;
		return ;
	}
	back = tokens;
	if (back->next != NULL)
	{
		back = ft_lstlast(back);
		 	
	}
	
}

void    lexer_scan(t_token *token, t_meta *meta)
{
    int i = 0;
    int j;
    meta->len  = ft_strlen(meta->meta_str);
    while (meta->meta_str != '\0' && i < meta->len)
    {
        if (meta->meta_str[i] == 'b')
            i++;
        if (check_word(meta, i) || meta->meta_str == 'u')
        {
            j = 1;
            while (meta->meta_str[i + j] == 'u')
                 j++;
            if (i < i + j)
				get_token(meta->tokens ,init_token(TOKEN_PIPE, trans_to_string(meta, token, i, i + j), meta));
        }
        else if (meta->meta_str[i] == 'p')
        {
            lexer_advance_token();
        }
    }
}
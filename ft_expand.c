/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <yobenali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 22:23:15 by yobenali          #+#    #+#             */
/*   Updated: 2022/11/15 03:24:06 by yobenali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_nexpand(char *str, int *pos)
{
	char	*tab;
	int		i;
	int		len;

	i = *pos;
	len = 0;
	while (ft_isalpha(str[i + len]) || ft_isdigit(str[i + len])
		|| str[i + len] == '_')
		len++;
	tab = ft_select(g_all.our_env, ft_substr(str, i, len), 0);
	*pos += len;
	return (tab);
}

int	ft_matchnmatch(char *buffer, char *mbuffer, char *charset, char match)
{
	int	i;

	i = 0;
	while (buffer[i])
	{
		if (ft_strchr(charset, buffer[i]))
		{
			if (mbuffer[i] == match)
				return (1);
		}
		i++;
	}
	return (0);
}

void	ft_expand(t_token *tokens)
{
	t_token	*tmp;
	char	*old_meta;
	char	*buffer;
	char	*mbuffer;
	char	*temp;
	int		i;
	int		j;

	tmp = tokens;
	while (tmp)
	{	
		if (!tmp->word)
			return ;
		tmp->old_word = ft_strdup(tmp->word);
		old_meta = ft_strdup(tmp->meta);
		if (!ft_strchr(tmp->meta, 'x') && !ft_strchr(tmp->meta, 'X') && \
				(ft_strchr(tmp->meta, 's') || ft_strchr(tmp->meta, 'd')))
		{
			j = 0;
			i = 0;
			while (tmp->meta[i])
			{
				if (tmp->meta[i] && (tmp->meta[i] != 'd' && \
					tmp->meta[i] != 's'))
				{
					tmp->word[j] = tmp->old_word[i];
					old_meta[j] = tmp->meta[i];
					j++;
				}
				i++;
			}
			tmp->word[j] = '\0';
			old_meta[j] = '\0';
			free (tmp->meta);
			tmp->meta = old_meta;
		}
		else if (ft_strchr(tmp->meta, 'x') || ft_strchr(tmp->meta, 'X'))
		{
			i = 0;
			buffer = NULL;
			mbuffer = NULL;
			while (tmp->meta[i])
			{
				j = 0;
				while (tmp->meta[i + j] != 's' && tmp->meta[i + j] != 'd' && \
					tmp->meta[i + j] != 'x' && tmp->meta[i + j] != 'X' && \
					tmp->meta[i + j])
					j++;
				buffer = ft_strjoin_free(buffer, ft_substr(tmp->word, i, j), \
					ALL);
				mbuffer = ft_strjoin_free(mbuffer, ft_substr(tmp->meta, i, j), \
				ALL);
				i += j;
				if (tmp->meta[i] == 's' || tmp->meta[i] == 'd')
					i++;
				else if (tmp->meta[i] == 'x')
				{
					i++;
					temp = ft_nexpand(tmp->word, &i);
					if (temp != NULL)
						mbuffer = ft_strjoin_free(mbuffer, \
							ft_memset(ft_strdup(temp), tmp->meta[i - 1], \
							ft_strlen(temp)), ALL);
					buffer = ft_strjoin_free(buffer, temp, ALL);
				}
				else if (tmp->meta[i] == 'X')
				{
					i++;
					temp = ft_itoa(g_all.g_exit_status);
					mbuffer = ft_strjoin_free(mbuffer, \
						ft_memset(ft_strdup(temp), tmp->meta[i++], \
						ft_strlen(temp)), ALL);
					buffer = ft_strjoin_free(buffer, temp, ALL);
				}
			}
			if ((buffer && *buffer == '\0') || \
				ft_matchnmatch(buffer, mbuffer, " \t\n", 'u'))
				tmp->e_type = TOKEN_AMBRD;
			free (tmp->word);
			tmp->word = buffer;
			free (tmp->meta);
			tmp->meta = mbuffer;
		}
		tmp = tmp->next;
	}
}

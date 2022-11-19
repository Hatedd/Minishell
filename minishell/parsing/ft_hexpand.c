/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexpand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <yobenali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 05:59:35 by yobenali          #+#    #+#             */
/*   Updated: 2022/11/19 06:15:55 by yobenali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**trans_to_string(t_meta *meta, int pos, int len)
{
	char	**tab;
	int		i;
	int		cal;

	i = 0;
	cal = 0;
	tab = ft_calloc(sizeof(char *), 3);
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

void	join_free(char *s1, char *s2, short flag)
{
	if (flag == FIRST || flag == ALL)
		free (s1);
	if (flag == SECOND || flag == ALL)
		free (s2);
}

char	*ft_strjoin_free(char *s1, char *s2, short flag)
{
	char	*str;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL)
	{
		str = ft_strdup(s2);
		join_free(s1, s2, flag);
		return (str);
	}
	if (s2 == NULL)
	{
		str = ft_strdup(s1);
		join_free(s1, s2, flag);
		return (str);
	}
	str = ft_strjoin(s1, s2);
	join_free(s1, s2, flag);
	return (str);
}

char	*ft_select(char **o_env, char *read_ln, int len)
{
	char	*tab;
	int		i;
	int		j;

	i = -1;
	while (o_env[++i])
	{
		j = 0;
		while (o_env[i][j] && read_ln[j] && o_env[i][j] == read_ln[j])
		{
			j++;
			if (o_env[i][j] == '=' && read_ln[j] == '\0')
			{
				j++;
				len = ft_strlen(o_env[i] + j);
				tab = ft_substr(o_env[i], j, len);
				if (!tab)
					return (NULL);
				free (read_ln);
				return (tab);
			}
		}
	}
	free (read_ln);
	return (NULL);
}

char	*ft_hexpand(char **read_ln)
{
	char	*tab;
	int		i;

	i = 0;
	if (**read_ln == '$')
		(*read_ln)++;
	else
		return (NULL);
	if (read_ln[0][i] == '_' || ft_isalpha(read_ln[0][i]))
	{
		i++;
		while (ft_isalpha(read_ln[0][i]) || ft_isdigit(read_ln[0][i])
			|| read_ln[0][i] == '_')
			i++;
		tab = ft_select(g_all.our_env, ft_substr(*read_ln, 0, i), 0);
		*read_ln += i;
		return (tab);
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <yobenali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 17:14:09 by yobenali          #+#    #+#             */
/*   Updated: 2022/11/21 05:40:31 by yobenali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**add_change(char **tab, char *str)
{
	int		i;
	char	**new;

	i = 0;
	if (!tab)
	{
		new = ft_calloc((i + 2), sizeof(char *));
		new[0] = ft_strdup(str);
		return (new);
	}
	while (tab[i])
		i++;
	new = ft_calloc((i + 2), sizeof(char *));
	i = 0;
	while (tab[i])
	{
		new[i] = tab[i];
		i++;
	}
	free(tab);
	new[i] = ft_strdup(str);
	return (new);
}

void	ft_free_tokens(t_token *tokens, t_parser *parsing)
{
	int	i;

	i = 0;
	if (tokens)
	{
		free(tokens->word);
		free(tokens->meta);
		free(tokens->old_word);
		free(tokens->heredoc);
	}
	if (parsing)
	{
		if (parsing->av)
		{
			while (parsing->av[i])
				free(parsing->av[i++]);
		}
		free(parsing->av);
		ft_free_array(parsing->path);
	}
}

void	ft_free_dlst(t_meta *meta)
{
	t_parser	*temp;
	t_token		*tmp;

	tmp = meta->tokens;
	while (tmp)
	{
		tmp = tmp->next;
		ft_free_tokens(meta->tokens, NULL);
		free(meta->tokens);
		meta->tokens = tmp;
	}
	temp = meta->parsing;
	while (temp)
	{
		temp = temp->next;
		ft_free_tokens(NULL, meta->parsing);
		free(meta->parsing);
		meta->parsing = temp;
	}
}

void	ft_lst_toarray(void)
{
	t_list	*tmp;
	char	*str;
	int		i;
	int		len;

	tmp = g_all.g_lst_env;
	i = 0;
	len = ft_lstsize(tmp);
	ft_free_array(g_all.our_env);
	g_all.our_env = ft_calloc(sizeof(char *), len + 1);
	if (!g_all.our_env)
		return ;
	while (tmp)
	{
		str = ft_strdup(tmp->content);
		g_all.our_env[i++] = str;
		tmp = tmp->next;
	}
	g_all.our_env[i] = NULL;
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

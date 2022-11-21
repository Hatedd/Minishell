/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <yobenali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 23:32:17 by yobenali          #+#    #+#             */
/*   Updated: 2022/11/21 05:30:14 by yobenali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_doubly_quote(char *av, t_meta *meta, int pos)
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
		error_set(258);
		return (g_all.g_error_status);
	}
	meta->meta_str[pos] = 'd';
	return (pos);
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
			error_set(258);
			return (g_all.g_error_status);
		}
		meta->meta_str[pos] = 's';
	}
	else if (av[pos] == '"')
		pos = ft_doubly_quote(av, meta, pos);
	return (pos);
}

int	ft_meta_expand(char	*av, t_meta	*meta, int i)
{
	if (av[i + 1] && (ft_isalpha(av [i + 1]) || av [i + 1] == '_'))
	{
		meta->meta_str[i] = 'x';
	}
	else if (av[i + 1] && av[i + 1] == '?')
		meta->meta_str[i] = 'X';
	else
		meta->meta_str[i] = 'u';
	return (i);
}

void	ft_trans_meta(char *av, t_meta *meta)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (ft_isalpha(av[i]))
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
			i = ft_meta_expand(av, meta, i);
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
	free (meta->cmd);
	meta->cmd = NULL;
	free (meta->meta_str);
	meta->meta_str = NULL;
	meta->cmd = readline("minishell$ ");
	if (meta->cmd == NULL)
		exit (g_all.g_exit_status);
	if (meta->cmd[0] == '\0')
	{
		g_all.g_error_status = 1;
		return ;
	}
	add_history(meta->cmd);
	meta->len = ft_strlen(meta->cmd);
	meta->meta_str = ft_calloc(sizeof(char), meta->len + 1);
	meta->flag = 0;
	meta->i = 0;
	g_all.g_error_status = 0;
	ft_free_dlst(meta);
	ft_trans_meta(meta->cmd, meta);
}

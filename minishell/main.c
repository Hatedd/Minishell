/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <yobenali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 00:05:19 by yobenali          #+#    #+#             */
/*   Updated: 2022/11/21 05:40:27 by yobenali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_counting_cmd(t_token *tokens)
{
	t_token	*tmp;
	int		i;

	i = 1;
	tmp = tokens;
	while (tmp)
	{
		if (tmp->e_type == T_PIPE)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

t_parser	*creat_list(t_token *tokens)
{
	int			i;
	int			nb;
	t_parser	*temp;

	nb = ft_counting_cmd(tokens);
	i = 0;
	temp = NULL;
	while (nb)
	{
		ft_dlstadd_back2(&temp, init_parser(i));
		if (i == 0)
			temp->in_fd = 0;
		nb--;
		i++;
	}
	ft_dlstlast2(temp)->out_fd = 1;
	return (temp);
}

int	ft_free_redirects(t_files *redirects)
{
	free(redirects[READ].name);
	free(redirects[WRITE].name);
	redirects[READ].name = NULL;
	redirects[WRITE].name = NULL;
	free(redirects);
	return (1);
}

void	ft_parser(t_token *tokens, t_parser *parsing, t_files *redirects)
{
	redirects[READ].mode = -1;
	redirects[WRITE].mode = -1;
	while (tokens)
	{
		if (tokens->e_type == T_WORD || tokens->e_type == T_AMBRD)
			ft_ambrd_parsing(tokens, parsing);
		else if (tokens->e_type >= T_DREAD && tokens->e_type <= T_WRITE)
		{
			if (ft_predirection(tokens, parsing, redirects))
			{
				if (g_all.g_error_status && ft_free_redirects(redirects))
					return ;
				while (tokens && tokens->e_type != T_PIPE)
					tokens = tokens->next;
				continue ;
			}
			tokens = tokens->next;
		}
		else if (tokens->e_type == T_PIPE)
			ft_opening_check(redirects, &parsing, TRUE);
		tokens = tokens->next;
	}
	ft_opening_check(redirects, &parsing, FALSE);
	ft_free_redirects(redirects);
}

int	main(int argc, char **argv, char **env)
{
	t_meta	*meta;

	(void)argc;
	(void)argv;
	meta = ft_calloc(sizeof(t_meta), 1);
	ft_starting_inti(env);
	while (TRUE)
	{
		if (main_helper(meta))
			continue ;
		meta->parsing = creat_list(meta->tokens);
		ft_parser(meta->tokens, meta->parsing, ft_calloc(sizeof(t_files), 2));
		if (g_all.g_error_status)
			continue ;
		execution(meta->parsing);
		ft_lst_toarray();
	}
	return (0);
}

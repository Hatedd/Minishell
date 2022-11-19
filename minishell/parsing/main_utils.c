/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <yobenali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 00:40:41 by yobenali          #+#    #+#             */
/*   Updated: 2022/11/19 23:03:15 by yobenali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main_helper(t_meta *meta)
{
	ft_init_meta(meta);
	if (g_all.g_error_status)
		return (1);
	lexer_scan(meta);
	if (meta->tokens == NULL)
		return (1);
	error_check(meta->tokens);
	if (g_all.g_error_status)
		return (1);
	ft_heredoc(meta->tokens, 0);
	if (g_all.g_error_status)
		return (1);
	ft_expand(meta->tokens);
	if (g_all.g_error_status)
		return (1);
	return (0);
}

void	ft_handler(int macro)
{
	if (macro == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ft_starting_inti(char **env)
{
	t_sig	f;

	f = &ft_handler;
	ft_our_env(env);
	// system("leaks minishell");
	// ft_build_env();
	signal(SIGINT, f);
	signal(SIGQUIT, SIG_IGN);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_help.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <yobenali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 17:16:02 by yobenali          #+#    #+#             */
/*   Updated: 2022/11/19 06:12:42 by yobenali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_heredoc_nb(t_token *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		if (lst->e_type == T_DREAD)
			i++;
		lst = lst->next;
	}
	return (i);
}

void	ft_fexited_sig(int nb)
{
	if (WEXITSTATUS(nb) == EXIT_FAILURE)
		return (error_set(1));
	else if (WEXITSTATUS(nb) == 2)
		exit (2);
	else if (WEXITSTATUS(nb) == 13)
		return (error_set(13));
	else if (WEXITSTATUS(nb) == 42)
		exit (42);
}

void	ft_sig_error(int nb)
{
	if (WIFEXITED(nb))
		ft_fexited_sig(nb);
	else if (WIFSIGNALED(nb))
	{
		if (WTERMSIG(nb) == SIGINT)
		{
			ft_putchar_fd('\n', 1);
			return (error_set(1));
		}
	}
}

void	ft_delimiter_name(t_token *tokens, char *name)
{
	t_token	*tmp;
	char	*ptr;
	int		nb;

	nb = 0;
	tmp = tokens;
	while (tmp)
	{
		if (tmp->e_type == T_DREAD)
		{
			tmp = tmp->next;
			ptr = ttyname(0);
			ptr = ft_strchr(ptr, '\0');
			name[12] = nb / 10 + '0';
			name[13] = nb % 10 + '0';
			name[16] = *--ptr;
			name[15] = *--ptr;
			name[14] = *--ptr;
			free (tmp->word);
			tmp->word = ft_strdup(name);
			nb++;
		}
		tmp = tmp->next;
	}
}

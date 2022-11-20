/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <yobenali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 18:09:18 by yobenali          #+#    #+#             */
/*   Updated: 2022/11/20 18:33:33 by yobenali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_parser	*init_parser(int i)
{
	t_parser	*head;

	head = (t_parser *)ft_calloc(sizeof(t_parser), 1);
	if (!head)
		return (NULL);
	head->flag = EXEC;
	head->index = i;
	head->in_fd = -2;
	head->out_fd = -2;
	head->av = NULL;
	head->path = NULL;
	head->next = NULL;
	head->prev = NULL;
	return (head);
}

void	ft_opening_fd(t_files *redirects, t_parser *parsing, int type)
{
	if (type == READ)
	{
		parsing->in_fd = open(redirects[type].name, redirects[type].mode);
		if (parsing->in_fd == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(redirects[type].name, 2);
			perror(":");
			error_set(13);
		}
		redirects[type].mode = -1;
	}
	else if (type == WRITE)
	{
		parsing->out_fd = open(redirects[type].name, redirects[type].mode);
		if (parsing->out_fd == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(redirects[type].name, 2);
			ft_putstr_fd(": Is a directory\n", 2);
			// perror("");
			error_set(13);
		}
		redirects[type].mode = -1;
	}
}

void	ft_ambrd_parsing(t_token *tmp, t_parser *parsing)
{
	char	**tab;
	int		i;

	i = 0;
	if (tmp->e_type == T_AMBRD)
	{
		tab = ft_split2(tmp->word);
		while (tab[i])
		{
			parsing->av = add_change(parsing->av, *(tab + i));
			i++;
		}
		i = 0;
		while (tab[i])
			free(tab[i++]);
		free(tab);
	}
	else
		parsing->av = add_change(parsing->av, tmp->word);
}

int	ft_opening_check(t_files *redirects, t_parser **parsing, char flag)
{
	if (redirects[READ].mode != -1)
		ft_opening_fd(redirects, *parsing, READ);
	if (redirects[WRITE].mode != -1)
		ft_opening_fd(redirects, *parsing, WRITE);
	if (flag == TRUE)
		*parsing = (*parsing)->next;
	return (1);
}

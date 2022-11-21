/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <yobenali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 17:27:12 by yobenali          #+#    #+#             */
/*   Updated: 2022/11/21 20:57:03 by yobenali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	filling_data(t_files *redirects, char *name, int mode)
{
	if (redirects->name)
		free (redirects->name);
	redirects->name = ft_strdup(name);
	redirects->mode = mode;
}

int	ft_redirection_norm(char *value)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(value, 2);
	ft_putstr_fd("faild to creat file\n", 2);
	error_set(13);
	return (1);
}

int	ft_redirection_help(t_token *temp, t_parser *parser, t_files *redirects)
{
	int	fd;

	if (temp->next->e_type == T_AMBRD)
		return (ft_ambrd_error(temp->next->old_word, parser, redirects));
	if (access(temp->next->word, F_OK) != 0)
	{
		fd = open(temp->next->word, O_CREAT | O_RDWR, 0600);
		if (fd == -1)
			if (ft_redirection_norm(temp->next->word))
				return (1);
		close(fd);
	}
	else if (access(temp->next->word, W_OK) != 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(temp->next->word, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		redirects[WRITE].mode = -1;
		parser->flag = NOEXEC;
		return (1);
	}
	return (0);
}

int	ft_redirection_read(t_token *temp, t_parser *parser, t_files *redirects)
{
	if (temp->next->e_type == T_AMBRD)
		return (ft_ambrd_error(temp->next->old_word, parser, redirects));
	if (access(temp->next->word, F_OK) != 0 || \
		access(temp->next->word, R_OK) != 0)
	{
		if (access(temp->next->word, F_OK) != 0)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(temp->next->word, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			redirects[READ].mode = -1;
			parser->flag = NOEXEC;
			return (1);
		}
		if (access(temp->next->word, R_OK) != 0)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(temp->next->word, 2);
			ft_putstr_fd(": Permission denied\n", 2);
			redirects[READ].mode = -1;
			parser->flag = NOEXEC;
			return (1);
		}
	}
	return (0);
}

int	ft_predirection(t_token *tokens, t_parser *parser, t_files *redirects)
{
	t_files	*tmp;
	t_token	*temp;

	tmp = redirects;
	temp = tokens;
	if ((temp->e_type == T_READ || temp->e_type == T_DREAD) && \
		(temp->next->e_type == T_WORD || temp->next->e_type == T_AMBRD))
	{
		if (ft_redirection_read(temp, parser, redirects))
			return (1);
		filling_data(&tmp[READ], temp->next->word, O_RDONLY);
	}
	else if ((temp->e_type == T_WRITE || temp->e_type == T_DWRITE) \
		&& (temp->next->e_type == T_WORD || temp->next->e_type == T_AMBRD))
	{
		if (ft_redirection_help(temp, parser, redirects))
			return (1);
		if (temp->e_type == T_WRITE)
			filling_data(&tmp[WRITE], temp->next->word, O_TRUNC | O_WRONLY);
		else if (temp->e_type == T_DWRITE)
			filling_data(&tmp[WRITE], temp->next->word, O_APPEND | O_WRONLY);
	}
	return (0);
}

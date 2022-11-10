/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <yobenali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 03:47:36 by yobenali          #+#    #+#             */
/*   Updated: 2022/11/10 12:28:43 by yobenali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	 ft_delimiter_name(t_token * tokens, char *name)
{
	t_token *tmp;
	char	*ptr;
	int		nb;

	nb = 0;
	tmp = tokens;
	while (tmp)
	{
		if (tmp->e_type == TOKEN_DREAD)
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

void	ft_heredoc_expand(char *rl, int fd, int h_quoted)
{
	char	*buffer;
	int		i;

	buffer = NULL;
	while (ft_strchr(rl, '$'))
	{
		i = 0;
		while (rl[i] != '$')
			i++;
		buffer = ft_strjoin_free(buffer, ft_substr(rl, 0, i), ALL);
		rl += i;
		if (h_quoted == EXPAND)
			buffer = ft_strjoin_free(buffer, ft_hexpand(&rl), ALL);
	}
	buffer = ft_strjoin_free(buffer, ft_strdup(rl), ALL);
	buffer = ft_strjoin_free(buffer, ft_strdup("\n"), ALL);
	ft_putstr_fd(buffer, fd);
	free (buffer);
}

int	ft_heredoc_creat(char *name, int nb, int fd)
{
	char	*ptr;

	ptr = ttyname(0);
	ptr = ft_strchr(ptr, '\0');
	name[12] = nb / 10 + '0';
	name[13] = nb % 10 + '0';
	name[16] = *--ptr;
	name[15] = *--ptr;
	name[14] = *--ptr;
	fd = open(name, O_CREAT | O_RDWR | O_TRUNC, 0600);
	if (fd == -1)
	{
		g_all.g_error_status = EXIT_FAILURE;
		g_all.g_exit_status = 13;
		exit (g_all.g_exit_status);
	}
	return (fd);
}

void	ft_rl_heredoc(t_token *tokens, char *name, int nb, int fd)
{
	t_token	*tmp;
	char	*rl;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->e_type == TOKEN_DREAD && tmp->next->e_type == TOKEN_WORD)
		{
			tmp = tmp->next;
			fd = ft_heredoc_creat(name, nb, fd);
			while (1)
			{
				rl = readline("> ");
				if (rl == NULL)
					break ;
				if (ft_strcmp(rl, tmp->heredoc))
					ft_heredoc_expand(rl, fd, tmp->h_quoted);
				else
					break ;
			}
			close(fd);
			nb++;
		}
		tmp = tmp->next;
	}
}

int	ft_heredoc_nb(t_token *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		if (lst->e_type == TOKEN_DREAD)
			i++;
		lst = lst->next;
	}
	return (i);
}

void	ft_heredoc(t_token *tokens, int fd)
{
	t_token	*temp;
	pid_t	pid;
	char	*name;
	int		nb;

	name = ft_strdup("/tmp/heredoc.....");
	pid = fork();
	temp = tokens;
	if (pid == 0)
	{
		nb = ft_heredoc_nb(temp);
		if (nb >= 16)
		{
			write(2, ": maximum here-document count exceeded\n", 40);
			exit(2);
		}
		ft_rl_heredoc(tokens, name, 0, fd);
		exit (EXIT_SUCCESS);
	}
	signal(SIGINT, SIG_IGN);
	pid = waitpid(pid, &nb, 0);
	if (pid == -1)
	{
		if (WIFEXITED(nb))
		{
			if (WEXITSTATUS(nb) == EXIT_FAILURE)
				error_set(1);
			else if (WEXITSTATUS(nb) == 2)// here you should exit
				error_set(2);
			else if (WEXITSTATUS(nb) == 13)
				error_set(13);
			else if (WEXITSTATUS(nb) == 42)// you shoud exit here too
				error_set(42);
		}
		else if (WIFSIGNALED(nb))
		{
			if (WTERMSIG(nb) == SIGINT)	
				error_set(1);
		}
		signal(SIGINT, SIG_DFL);// you need to replace SIG_DFL with you own handler
	}
	ft_delimiter_name(tokens, name);
	free(name);
	// check here if the child exited because of a signal
	
	//after checking both situations react to each one of them accourdingly
}
 
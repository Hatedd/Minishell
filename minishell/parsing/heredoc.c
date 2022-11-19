/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <yobenali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 03:47:36 by yobenali          #+#    #+#             */
/*   Updated: 2022/11/19 06:10:53 by yobenali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		if (tmp->e_type == T_DREAD && tmp->next->e_type == T_WORD)
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

void	ft_hchild_work(t_token *tokens, char *name, int fd, int nb)
{
	t_token	*temp;

	temp = tokens;
	nb = ft_heredoc_nb(temp);
	if (nb >= 16)
	{
		write(2, "minishell : maximum here-document count exceeded\n", 50);
		exit(2);
	}
	ft_rl_heredoc(tokens, name, 0, fd);
	exit (EXIT_SUCCESS);
}

void	ft_heredoc(t_token *tokens, int fd)
{
	pid_t	pid;
	char	*name;
	int		nb;
	sig_t	f;

	f = &ft_handler;
	name = ft_strdup("/tmp/heredoc.....");
	pid = fork();
	nb = 0;
	if (pid == 0)
		ft_hchild_work(tokens, name, fd, nb);
	signal(SIGINT, SIG_IGN);
	pid = waitpid(pid, &nb, 0);
	ft_sig_error(nb);
	signal(SIGINT, ft_handler);
	ft_delimiter_name(tokens, name);
	free(name);
}

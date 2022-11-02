/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <yobenali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 03:47:36 by yobenali          #+#    #+#             */
/*   Updated: 2022/11/02 05:29:02 by yobenali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	ft_heredoc_creat(char *name, int nb)
{
	char	*ptr;
	
	ptr = ttyname(0);
	ptr = ft_strchr(ptr, '\0');
	name[12] = nb / 10 + '0';
	name[13] = nb % 10 + '0';
	name[16] = *--ptr;
	name[15] = *--ptr;
	name[14] = *--ptr;
	printf("%s\n", name);
	open(name, O_CREAT | O_RDWR, 0600);// here you need to save the fd of the file and return it
}

void    ft_heredoc(t_token *tokens)
{
    t_token *tmp;
    pid_t   pid;
	char	*name;
	int		nb;
	
	name = ft_strdup("/tmp/heredoc.....");
    pid = fork();
    tmp = tokens;
	// printf("%s\n", ttyname(0));
	// exit (0);
    if (pid == 0)
    {
		nb = ft_heredoc_nb(tmp);
        if (nb >= 16)
			exit(write(2, ": maximum here-document count exceeded\n", 40));
		nb = 0;
		while (tmp)
		{
			if (tmp->e_type == TOKEN_DREAD && tmp->next->e_type == TOKEN_WORD)
			{
				ft_heredoc_creat(name, nb); // here you need to return the fd of the file that is newly created and opened
				// here you need to read from the user and save it in the heredoc name file you generated
				nb++;
			}
			tmp = tmp->next;
		}
		exit (99);
	}
	waitpid(pid, &nb, 0);
}

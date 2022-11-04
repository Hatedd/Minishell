/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <yobenali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 03:47:36 by yobenali          #+#    #+#             */
/*   Updated: 2022/11/05 00:30:49 by yobenali         ###   ########.fr       */
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
	fd = open(name, O_CREAT | O_RDWR, 0600);// here you need to save the fd of the file and return it
	if (fd == -1)
	{
		g_all.g_error_status = EXIT_FAILURE;
		g_all.g_exit_status = 13;
		exit (13);
	}
	return (fd);
}

char	*ft_select(char **o_env, char *read_ln)
{
	int i;
	int j;
	char *tab;
	
	i = 0;
	while (o_env[i])
	{
		j = 0;
		while (o_env[i][j] && o_env[i][j] != '=' && o_env[i][j] == read_ln[j])
		{
			j++;
			if (o_env == '=')
			{
				j = ft_strlen((o_env[i] + j));
				tab = ft_calloc((j + 1), sizeof(char));
				if (!tab)
					return (NULL);
			}
		}
		i++;
	}	
}

void	ft_expand(char *read_ln, char *heredoc)
{
	char	*tab;
	int		i;
	int 	j;

	j = 0;
	i = 0;
	while (read_ln[i])
	{
		if (read_ln[i] = '$')
		{
			i++;
			break;
		}
		i++;
	}
	j = i;
	if (read_ln[i] == '_' || ft_isalpha(read_ln[i]))
	{
		i++;
		while (ft_isalpha(read_ln[i]) || ft_isdigit(read_ln[i]) || read_ln[i] == '_')
			i++;
		tab = ft_select(g_all.our_env, (read_ln + j));
		j = i - j;
	}
}

void    ft_heredoc(t_token *tokens, int fd)
{
    t_token *tmp;
    pid_t   pid;
	char	*ptr;
	char	*name;
	int		nb;
	
	name = ft_strdup("/tmp/heredoc.....");
    pid = fork();
    tmp = tokens;
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
				tmp = tmp->next;
				fd = ft_heredoc_creat(name, nb, fd);
				while (1)
				{
					ptr = readline("> ");
					if (ptr == NULL)
						break;
					if (ft_strcmp(ptr, tmp->heredoc))
					{
						if (ft_strchr(ptr, '$'))
							ft_expand( ptr, tmp->heredoc);
						//check the flag to know if you need to expand or not, if you need to expnad expand 
						//pass the return of readline to a fuction that search for the dollar sign and check if the word after it is valid
						// and then if it is valid search for it in the env and then replace the word with it is value from the env
						// example : "hello $USER" ==> "hello yobenali"
						ft_putstr_fd(ptr, fd);
						ft_putchar_fd('\n', fd);
					}
					else
						break;
				}
				close(fd);
				nb++;
			}
			tmp = tmp->next;
		}
		exit (99);
	}
	waitpid(pid, &nb, 0);
}

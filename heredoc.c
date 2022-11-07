/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <yobenali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 03:47:36 by yobenali          #+#    #+#             */
/*   Updated: 2022/11/07 04:30:33 by yobenali         ###   ########.fr       */
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
	int	len;
	int k;
	char *tab;
	
	i = 0;
	k = 0;
	len = 0;
	// printf("%s\n", read_ln);
	while (o_env[i])
	{
			// printf("%d\n", len);
		j = 0;
		while (o_env[i][j] && o_env[i][j] == read_ln[j])
		{
			j++;
			if (o_env[i][j] == '=')
			{
				j++;
				len = ft_strlen(o_env[i] + j);
				len++;
				tab = ft_calloc((len), sizeof(char));
				if (!tab)
					return (NULL);
				while (o_env[i][j] != '\n' && o_env[i][j] && k < len)
				{
					tab[k] = o_env[i][j];
					k++;
					j++;
				}
				if (tab[0])
					return (tab);
			}
		}
		i++;
	}
	return (tab);
}

int	ft_expand(char *read_ln, int fd, int flag)
{
	char	*tab;
	int		i;

	i = 0;
	// printf("%s\n", (read_ln + i));
	if (read_ln[i] == '$')
		i++;
	else
		return (0);
	if (read_ln[i] == '_' || ft_isalpha(read_ln[i]))
	{
		i++;
		while (ft_isalpha(read_ln[i]) || ft_isdigit(read_ln[i]) || read_ln[i] == '_')
			i++;
		if (read_ln[i] != ' ' && read_ln[i])
			return (0);
		tab = ft_select(g_all.our_env, (read_ln + 1));
		// j--;
		// if (flag == 0)
		// {	
		// 	flag++;
		// }
		while (*tab)
		{
			if (flag == 1)
			{
				ft_putchar_fd(' ', fd);
				flag = 10;
			}
			ft_putchar_fd(*tab, fd);
			tab++;
		}
	}
	return (1);
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
						{
							while (*ptr != '$')
							{
								if (*ptr && *ptr != ' ' && *(ptr + 1) != '$')
									ft_putchar_fd(*ptr ,fd);
								ptr++;
							}
							ft_expand(ptr, fd, 1);
							if (*ptr == '$')
							{
								while (*ptr && *ptr != ' ' && *ptr != '\n')
									ptr++;
								ft_putstr_fd(ptr, fd);
								ft_putchar_fd('\n', fd);
								continue;
							}
						}
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

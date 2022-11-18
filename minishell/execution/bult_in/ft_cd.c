/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <yobenali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:08:07 by mouizar           #+#    #+#             */
/*   Updated: 2022/11/18 00:25:13 by yobenali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	join_pwd(t_list *tmp, char *temp, char *value)
{
	temp = ft_strdup(value);
	tmp->content = ft_strjoin("PWD=", temp);
	free(temp);
}

void	ft_modify_pwd(char *str, char *value, int flag)
{
	t_list	*tmp;
	char	*temp;

	tmp = g_all.g_lst_env;
	while (tmp)
	{
		if (!ft_strncmp(str, tmp->content, ft_strlen(str))
			&& (((char *)tmp->content)[ft_strlen(str)] == '\0'
			|| ((char *)tmp->content)[ft_strlen(str)] == '='))
		{
			free(tmp->content);
			if (flag == 1)
			{
				join_pwd(tmp, temp, value);
			}
			else
			{
				temp = ft_strdup(value);
				tmp->content = ft_strjoin("OLDPWD=", temp);
				free(temp);
			}
		}
		tmp = tmp->next;
	}
}

void	ft_parser_cd(t_parser *cmdl)
{
	struct stat	stats;
	char		*pwd;
	char		*oldpwd;
	int			i;

	if (!cmdl->av[1])
		return ;
	i = stat(cmdl->av[1], &stats);
	if (cmdl->av[1] && i == 0 && (S_ISDIR(stats.st_mode)))
	{
		oldpwd = getcwd(0, 0);
		chdir(cmdl->av[1]);
		pwd = getcwd(0, 0);
		if (!pwd)
			return ;
		ft_modify_pwd("PWD", pwd, 1);
		ft_modify_pwd("OLDPWD", oldpwd, 2);
		free(pwd);
		free(oldpwd);
	}
	else if (cmdl->av[1] == 0 && ft_strncmp(cmdl->av[0], "cd", 3) == 0)
		write(2, "cd with only a relative or absolute path\n", 42);
	else
		ft_generate_erro2(cmdl, 3);
	return ;
}

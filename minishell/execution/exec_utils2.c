/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouizar <mouizar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 23:08:06 by mouizar           #+#    #+#             */
/*   Updated: 2022/11/20 01:39:58 by mouizar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*join_and_free(char *s1, char *s2)
{
	char	*new;

	new = ft_strjoin(s1, s2);
	free(s1);
	return (new);
}

char	**generate_path(char **path, t_parser *cmdl, char *slash_path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		if (ft_strchr(cmdl->av[0], '/'))
		{
			free(path[i]);
			path[i] = ft_strdup(slash_path);
			return (path);
		}
		//system("leaks minishell");
		path[i] = join_and_free(path[i], "/");
		path[i] = join_and_free(path[i], cmdl->av[0]);
		i++;
	}
	return (path);
}

char	**ft_split_path(t_parser	*cmdl)
{
	char	*str;
	char	**var;
	char	**path;
	char	*slash_path;

	str = ft_found_path();
	if (!str || cmdl->av[0] == NULL)
		return (NULL);
	var = ft_split(str, '=');
	path = ft_split(var[1], ':');
	ft_free_array(var);
	slash_path = ft_strdup(cmdl->av[0]);
	path = generate_path(path, cmdl, slash_path);
	free(slash_path);
	return (path);
}

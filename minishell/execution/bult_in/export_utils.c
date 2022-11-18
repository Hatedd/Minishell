/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <yobenali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:52:32 by mouizar           #+#    #+#             */
/*   Updated: 2022/11/18 16:28:01 by yobenali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_list	*sorting(t_list *lst, int (*ft_cmpar)(char *, char *))
{
	t_list	*sv;
	char	*tmp;

	if (!lst)
		return 0;
	tmp = NULL;
	sv = lst;
	while (lst->next)
	{
		if ((*ft_cmpar)(lst->content, lst->next->content) == 0)
		{
			tmp = lst->next->content;
			lst ->next->content = lst->content;
			lst->content = tmp;
			lst = sv;
		}
		else
		lst = lst->next;
	}
	lst = sv;
	return (lst);
}

int	ft_cmpar(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] > s2[i])
			return (0);
		else if (s1[i] == s2[i])
			i++;
		else
			return (1);
	}
	return (1);
}

int	ft_strcmpme(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*sn1;
	unsigned char	*sn2 ;

	sn2 = (unsigned char *) s2;
	sn1 = (unsigned char *) s1;
	i = 0;
	while ((sn1[i] == sn2[i]) && sn1[i] && sn2[i])
		i++;
	return (sn1[i] - sn2[i]);
}

void	printing(char *content)
{
	size_t	len;
	char	*temp;
	char	**split;

	split = ft_split(content, '=');
	len = ft_strlen(content);
	if (!ft_strchr(content, '='))
		printf("declare -x %s\n", content);
	else
	{
		temp = ft_substr(content, ft_strlen(split[0]) + 1, len);
		printf("declare -x %s=\"%s\"\n", split[0],
			temp);
		free(temp);
	}
	ft_free_array(split);
}

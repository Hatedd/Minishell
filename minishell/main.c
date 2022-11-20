/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouizar <mouizar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 00:05:19 by yobenali          #+#    #+#             */
/*   Updated: 2022/11/20 01:14:32 by mouizar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_our_env(char **env)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	while (env[i])
		i++;
	g_all.our_env = ft_calloc((i + 1), sizeof(char *));
	if (!g_all.our_env)
		return ;
	i = 0;
	while (env[i])
	{
		j = 0;
		len = ft_strlen(env[i]);
		g_all.our_env[i] = ft_calloc((len + 1), sizeof(char *));
		if (!g_all.our_env[i])
			return ;
		while (env[i][j])
		{
			g_all.our_env[i][j] = env[i][j];
			j++;
		}
		i++;
	}
	//ft_build_env();
}

int	ft_counting_cmd(t_token *tokens)
{
	t_token	*tmp;
	int		i;

	i = 1;
	tmp = tokens;
	while (tmp)
	{
		if (tmp->e_type == T_PIPE)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

t_parser	*creat_list(t_token *tokens)
{
	int			i;
	int			nb;
	t_parser	*temp;

	nb = ft_counting_cmd(tokens);
	i = 0;
	temp = NULL;
	while (nb)
	{
		ft_dlstadd_back2(&temp, init_parser(i));
		if (i == 0)
			temp->in_fd = 0;
		nb--;
		i++;
	}
	ft_dlstlast2(temp)->out_fd = 1;
	return (temp);
}

void	ft_parser(t_token *tokens, t_parser *parsing, t_files *redirects)
{
	redirects[READ].mode = -1;
	redirects[WRITE].mode = -1;
	while (tokens)
	{
		if (tokens->e_type == T_WORD || tokens->e_type == T_AMBRD)
			ft_ambrd_parsing(tokens, parsing);
		else if (tokens->e_type == T_READ || tokens->e_type == T_WRITE || \
				tokens->e_type == T_DWRITE || tokens->e_type == T_DREAD)
		{
			if (ft_predirection(tokens, parsing, redirects))
			{
				if (g_all.g_error_status)
					return ;
				while (tokens && tokens->e_type != T_PIPE)
					tokens = tokens->next;
				continue ;
			}
			tokens = tokens->next;
		}
		else if (tokens->e_type == T_PIPE)
			ft_opening_check(redirects, &parsing, TRUE);
		tokens = tokens->next;
	}
	ft_opening_check(redirects, &parsing, FALSE);
	free (redirects->name);
	free (redirects);
}

void	ft_lst_toarray()
		{
			t_list *tmp = g_all.g_lst_env;
			char *str;
			// char ** array;
			int i = 0;
			int len = ft_lstsize(tmp);
			ft_free_array(g_all.our_env);
			g_all.our_env = malloc(sizeof(char *) * len + 1);
			if (!g_all.our_env)
				return ;
			
		//system("leaks minishell");
			while (tmp)
			{
				str = ft_strdup(tmp->content);
				//free(tmp->content);
				//dprintf(2, "str is %p\n",str);
				// dprintf(2, "env is %p\n",g_all.our_env[i]);
		//	dprintf(2, "tmp->content  is %p\n", tmp->content);
				g_all.our_env[i++] = str;
				//free(str);
				tmp = tmp->next;
			}
			g_all.our_env[i] = NULL;
		}

int	main(int argc, char **argv, char **env)
{
	t_meta		meta;
	// t_parser	*temp;
	// t_token		*tmp;
	// int			i;

	(void)argc;
	(void)argv;
	ft_starting_inti(env);
	while (TRUE)
	{
		if (main_helper(&meta))
			continue ;
		meta.parsing = creat_list(meta.tokens);
		ft_parser(meta.tokens, meta.parsing, ft_calloc(sizeof(t_files), 2));
		if (g_all.g_error_status)
			continue ;
		// tmp = meta.tokens;
		// while (tmp)
		// {
		// 	printf("-----------------------------\n");
		// 	printf("the word is |%s|\n", tmp->word);
		// 	printf("the meta is |%s|\n", tmp->meta);
		// 	printf("the type is |%u|\n", tmp->e_type);
		// 	tmp = tmp->next;
		// }
		// temp = meta.parsing;
		// while (temp)
		// {
		// 	printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
		// 	printf("the flag is |%d|\n", temp->flag);
		// 	printf("the index is |%d|\n", temp->index);
		// 	printf("the infile is |%d|\n", temp->in_fd);
		// 	printf("the outfile is |%d|\n", temp->out_fd);
		// 	printf("this is the av address |%p|\n", temp->av);
		// 	i = -1;
		// 	while (temp->av && temp->av[++i])
		// 		printf("the av[%d] is |%s|\n", i, temp->av[i]);
		// 	temp = temp->next;
		// }
		free(meta.cmd);
		free(meta.meta_str);
		execution(meta.parsing);
	 
		//ft_free_array(g_all.path);
	}
	return (0);
}

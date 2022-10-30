/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <yobenali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 00:05:19 by yobenali          #+#    #+#             */
/*   Updated: 2022/10/30 02:14:10 by yobenali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

t_gdata g_all;

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*buf;

	i = 0;
	buf = (unsigned char *) b;
	while (i < len)
	{
		buf[i] = (unsigned char) c;
		i++;
	}
	return ((void *) buf);
}

void	ft_bzero(void	*s, size_t n)
{
	ft_memset(s, 0, n);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char) c)
			return ((char *) s);
		s++;
	}
	if (*s == (char) c)
		return ((char *) s);
	return (0);
}

// int		ft_strcheck(const char *s1, const char *s2)
// {
// 	if (s1[0] == s2[0] && s2[1] == s2[1])
// 		return (1);
// 	return (0);
// }

void	*ft_calloc(size_t count, size_t size)
{
	size_t	t_count;
	char	*ptr;

	t_count = count * size;
	ptr = malloc(t_count);
	if (!ptr)
		return (NULL);
	ft_bzero((void *)ptr, t_count);
	return ((void *)ptr);
}

int	is_char(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int	ft_quote(char *av, t_meta *meta, int pos)
{
	if (av[pos] == '\'')
	{
		meta->meta_str[pos++] = 's';
		while (av[pos] && av[pos] != '\'')
		{
			meta->meta_str[pos] = 'Q';
			pos++;
		}
		if (av[pos] == '\0')
		{
			// write(2, "sed le7za9 dyal quotes alkhanez\n", 32);
			g_all.g_error_status = EXIT_FAILURE;
			return (EXIT_FAILURE);
			//chof akhona hna khassek terja3 otseti error  258 and exit code 
			// l258 and terja3 t3ti prompt jdid hadhi blama ngolik lblan 
			// dyal error msg.
		}
		meta->meta_str[pos] = 's';
	}
	else if (av[pos] == '"')
	{
		meta->meta_str[pos++] = 'd';
		while (av[pos] && av[pos] != '"')
		{
			if (av[pos] == '$')
				meta->meta_str[pos] = 'x';
			else
				meta->meta_str[pos] = 'q';
			pos++;
		}
		if (av[pos] == '\0')
		{
			// write(2, "sed le7za9 dyal quotes alkhanez\n", 32);
			g_all.g_error_status = EXIT_FAILURE;
			return (EXIT_FAILURE);
			//chof akhona hna khassek terja3 otseti error  258 and exit code
			//l258 and terja3 t3ti prompt jdid hadhi blama ngolik lblan dyal
			//error msg.
		}
		meta->meta_str[pos] = 'd';
	}
	return (pos);
}

void	ft_trans_meta(char *av, t_meta *meta)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (is_char(av[i]))
			meta->meta_str[i] = 'u';
		else if (av[i] == '|')
			meta->meta_str[i] = 'p';
		else if (av[i] == '<')
			meta->meta_str[i] = 'r';
		else if (av[i] == '>')
			meta->meta_str[i] = 'w';
		else if (av[i] == ' ' || av[i] == '\t' || av[i] == '\n')
			meta->meta_str[i] = 'b';
		else if (av[i] == '$')
		{
			if (av[i + 1] && is_char(av [i + 1]))
			{
				meta->meta_str[i] = 'x';
			}
			else if (av[i + 1] && av[i + 1] == '?')
				meta->meta_str[i] = 'X';
			else
				meta->meta_str[i] = 'u';
		}
		else if (av[i] == '\'' || av[i] == '"')
			i = ft_quote(av, meta, i);
		else
			meta->meta_str[i] = 'u';
		if (g_all.g_error_status)
			return ;
		i++;
	}
}

void	ft_init_meta(t_meta *meta)
{
	meta->cmd = readline("minishell$ ");
	if (meta->cmd == NULL)
		exit (113); // here you should exit with the last exit status you had
	meta->len = ft_strlen(meta->cmd);
	meta->meta_str = ft_calloc(sizeof(char), meta->len + 1);
	meta->flag = 0;
	meta->i = 0;
	meta->tokens = NULL; //"/dont forget to free the list" before making it null
	ft_trans_meta(meta->cmd, meta);
}

void	error_check(t_token *tokens)
{
	int		i;
	t_token *tmp;

	tmp = tokens;
	i = 0;
	while (tmp)
	{
		if (ft_strchr(tmp->meta, 'p') && i == 0)
			exit(258);
		else if (ft_strchr(tmp->meta, 'p') && ft_strchr(tmp->next->meta, 'p'))
			exit(258);
		else if ((ft_strchr(tmp->meta,'p') || ft_strchr(tmp->meta,'r') || ft_strchr(tmp->meta,'w')) && tmp->next == NULL)
			exit(258);
		i++;
		tmp = tmp->next;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_meta	meta;
	t_token	*tmp;

	(void)argc;
	(void)argv;
	(void)env;
	tmp = NULL;
	while (TRUE)
	{
		ft_init_meta(&meta);
		if (g_all.g_error_status)
			continue ;
		add_history(meta.cmd);
		lexer_scan(&meta);
		error_check(meta.tokens);
		if (g_all.g_error_status)
			continue ;
		tmp = meta.tokens;
		while (tmp)
		{
			printf("-----------------------------\n");
			printf("the word is ¢ %s ¢\n", tmp->word);
			printf("the meta is ¢ %s ¢\n", tmp->meta);
			printf("the type is ¢ %u ¢\n", tmp->e_type);
			tmp = tmp->next;
		}
	}
	return (0);
}

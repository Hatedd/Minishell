/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <yobenali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 00:05:19 by yobenali          #+#    #+#             */
/*   Updated: 2022/10/23 23:14:00 by yobenali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>
int     ft_strlen(char *str)
{
    int i;

    i = 0;
    while(str[i])
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

int     is_char(char c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        return (1);
    return (0);
}

int     ft_quote(char *av, t_meta *meta, int pos)
{
    if (av[pos] == '\'')
    {
        meta->meta_str[pos++] = 's';
        while (av[pos] != '\'')
        {
            meta->meta_str[pos] = 'Q';
            pos++;
        }
        meta->meta_str[pos] = 's';
    }
    else if (av[pos] == '"')
    {
        meta->meta_str[pos++] = 'd';
        while (av[pos] != '"')
        {
            if (av[pos] == '$')
                meta->meta_str[pos] = 'x';
            else
                meta->meta_str[pos] = 'q';
            pos++;
        }
        meta->meta_str[pos] = 'd';
    }
    return (pos);
}

void    ft_trans_meta(char *av, t_meta *meta)
{
    int i;
    int len;

    i = 0;
    len = ft_strlen(av) + 1;
    meta->meta_str = malloc(sizeof(char) * len);
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
        i++;
    }
    meta->meta_str[i] = 0;
}

void    ft_init_meta(t_meta *meta)
{
    meta->cmd = readline("minishell$");
    meta->len = ft_strlen(meta->cmd);
    meta->flag = 0;
    if (meta->cmd == NULL)
        exit (113); // here you should exit with the last exit status you had
    ft_trans_meta(meta->cmd ,meta);
}

// void    ft_init_data(t_token *token)
// {
    
// }

int main(int argc, char **argv, char **env)
{
    t_meta  meta;
    // t_token token;
    
    (void)argc;
    (void)argv;
    (void)env;
    // ft_init_data(token);
    while (TRUE)
    {
        ft_init_meta(&meta);
        add_history(meta.cmd);
        printf("%s\n", meta.meta_str);
        lexer_scan(&meta);
    }
    // char * a;
    // a = strdup("\"$USER\"");
    // meta = malloc(sizeof(t_meta));
    // ft_trans_meta(a, meta);
    return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multilines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 12:21:37 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/16 10:32:08 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*ending(t_main *m, char *s, char *shist, t_uint type)
{
	if (!(m->hist = history(ft_strdup(shist), m->hist, m->p->hnum)))
		malloc_error(m, s, READING);
	free(s);
	set_term_cano(m->base_term);
	// printf("sh = [%s]\n", shist);
	m->p->multi = 0;
	if (type == CTRL_C)
		return (NULL);
	if (type == CTRL_D)
	{
		printf("minish: unexpected EOF while looking for matching c\n");
		printf("minish: \e[0;31msyntax error\e[0m: unexpected end of file\n");
		m->exit_status = 258;
		return (NULL);
	}
	return (shist);
}

static int		check_quote(char *s, char c, int x)
{
	int		i;

	i = 0;
	if (x == -2)
		return (0);
	// printf("s = %s\n", s);
	while (s[i] && s[i] != c)
		i++;
	if (s[i] == c)
	{
		while (s[++i])
			if (s[i] == c)
				return (0);
		return (1);
	}
	return (0);
}

static int		check_pipe_and(char *s, char *c)
{
	int		i;

	i = 0;
	while (s[i] && s[i] != c[0])
		i++;
	if (s[i] == c[0])
	{
		if (ft_strlen(c) == 2)
		{
			i++;
			if (s[i] == c[1])
			{
				while (s[++i])
					if (s[i] > 32 && s[i] < 127)
						return (1);
			}
		}
		else
		{
			while (s[++i])
				if (s[i] > 32 && s[i] < 127)
					return (1);
		}
		return (0);
	}
	return (1);
}

static int		check_multi(char *s, t_token_type type, int x)
{
	if (type == SQUOTE)
		return (check_quote(s, '\'', x));
	if (type == DQUOTE)
		return (check_quote(s, '\"', x));
	if (type == PIPE)
		return (check_pipe_and(s, "|"));
	// if (type == DPIPE)
	// 	return (check_pipe_and(s, "||"));
	// if (type == AND)
	// 	return (check_pipe_and(s, "&&"));
	return (0);
}

char			*multilines(t_main *m, char *s, t_token_type type)
{
	int		ret;
	char	*shist;
	char 	buf[3];

	ret = -2;
	set_term_noncano();
	m->p->multi = 1;
	shist = ft_strdup(s);
	ft_bzero(buf, 3);
	buf[1] = 'm';
	while (!(check_multi(s, type, ret)))
	{
		ft_putstr("\e[0;32m> \e[0m");
		s[0] = '\0';
		while ((ret = reading(m, &s, buf)) > 0);
		if (type == SQUOTE || type == DQUOTE)
			shist = ft_strjoin_nl(shist, "\n");
		else
			shist = ft_strjoin_nl(shist, " ");
		shist = ft_strjoin_nl(shist, s);
		// printf("ret = %d\n", ret);
		if (ret == -1)
			return (ending(m, s, shist, buf[0]));
		m->p->lpos = 0;
		m->p->hnum = 0;
	}
	return (ending(m, s, shist, NO_BREAK));
}
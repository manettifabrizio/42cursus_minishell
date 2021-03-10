/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multilines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 12:09:55 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/10 01:08:39 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*reading(t_main *m, char *s, char *buf)
{
	read(STDOUT_FILENO, buf, 1);
	if (!(check_key(m, &s, buf)))
		s = str_print_and_handle(m, s, buf, *(m->pos));
	return (s);
}

static int		check_multi(char *s, char *c)
{
	int		i;

	i = 0;
	printf("s = %s\n", s);
	while (s[i] && s[i] != c[0])
		i++;
	if (s[i] == c[0])
	{
		i++;
		if (ft_strlen(c) == 2)
		{
			if (s[i] == c[1])
			{	
				while (s[i] && s[i] != '\n')
					if (ft_isprint(s[i]))
						return (1);
			}
		}
		else
		{	
			while (s[i] && s[i] != '\n')
				if (ft_isprint(s[i]))
					return (1);
		}
		return (0);
	}
	return (1);
}

char			*multilines_pipe(t_main *m, char *s, char *c)
{
	int		i;
	int		cnum;
	char	*shist;
	char	buf[2];

	i = 0;
	cnum = 1;
	set_term_noncano();
	shist = ft_strdup(s);
	while (!(check_multi(s, c)))
	{
		ft_putstr("> ");
		(s)[0] = '\0';
		ft_bzero(buf, 2);
		while (buf[0] != '\n')
		{
			if (!(m->hist = history(ft_strdup(s), m->hist, i++, m->pos->y)))
				malloc_error(m, s, READING);
			s = reading(m, s, buf);
			if (buf[0] == CTRL_C)
				break;
		}
		if (buf[0] == CTRL_C)
			break;
		shist = ft_strjoin_nl(shist, "\n");
		shist = ft_strjoin_nl(shist, s);
		m->pos->x = 0;
		m->pos->y = 0;
	}
	if (!(m->hist = history(ft_strdup(shist), m->hist, 1, m->pos->y)))
		malloc_error(m, s, READING);
	free(s);
	set_term_cano(m->base_term);
	return (shist);
}

//	CTRL-D
// 	bash-3.2$ echo "asdafasdfsdf
// 	> bash: unexpected EOF while looking for matching `"'
// 	bash: syntax error: unexpected end of file

char	*multilines(t_main *m, char *s, t_token_type type)
{
	if (type == PIPE)
		return (multilines_pipe(m, s, "|"));
	// if (type == S_QUOTE)
	// 	return (multilines_quote(m, s, '\''));
	// if (type == D_QUOTE)
	// 	return (multilines_quote(m, s, '\"'));
	return (NULL);
}

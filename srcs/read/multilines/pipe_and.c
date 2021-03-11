/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_and.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 12:25:57 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/11 20:58:25 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*reading(t_main *m, char *s, char *buf)
{
	read(STDOUT_FILENO, buf, 1);
	if (!(check_key(m, &s, buf)))
		s = str_print_and_handle(m, s, buf, *(m->p));
	return (s);
}

static int		check_multi(char *s, char *c)
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

char			*multi_pipe_and(t_main *m, char *s, char *c)
{
	int		i;
	char	*shist;
	char	buf[2];

	i = 0;
	set_term_noncano();
	printf("MULTI_PIPE\n");
	shist = ft_strdup(s);
	while (!(check_multi(s, c)))
	{
		ft_putstr("\e[0;32m> \e[0m");
		(s)[0] = '\0';
		ft_bzero(buf, 2);
		while (buf[0] != '\n')
		{
			if (!(m->hist = history(ft_strdup(s), m->hist, i++, m->p->hnum)))
				malloc_error(m, s, READING);
			s = reading(m, s, buf);
			if (buf[0] == CTRL_C)
				break;
		}
		if (buf[0] == CTRL_C)
			break;
		printf("s = %s\n", s);
		printf("shistb = %s\n", shist);
		shist = ft_strjoin_nl(shist, " ");
		shist = ft_strjoin_nl(shist, s);
		printf("shista = %s\n", shist);
		m->p->lpos = 0;
		m->p->hnum = 0;
	}
	if (!(m->hist = history(ft_strdup(shist), m->hist, 1, m->p->hnum)))
		malloc_error(m, s, READING);
	free(s);
	set_term_cano(m->base_term);
	return (shist);
}
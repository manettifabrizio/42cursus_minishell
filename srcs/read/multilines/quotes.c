/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 12:21:37 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/10 13:15:52 by fmanetti         ###   ########.fr       */
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

static int		check_multi(char *s, char c, int x)
{
	int		i;

	i = 0;
	if (x == 0)
		return (0);
	printf("s = %s\n", s);
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

char			*multi_quote(t_main *m, char *s, char c)
{
	int		i;
	char	*shist;
	char	buf[2];

	i = 0;
	set_term_noncano();
	shist = ft_strdup(s);
	while (!(check_multi(s, c, i)))
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
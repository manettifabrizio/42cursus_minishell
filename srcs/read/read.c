/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 13:06:59 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/16 00:49:29 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		reading(t_main *m, char **s, char *buf)
{
	if (!(m->hist = history(ft_strdup(*s), m->hist, m->p->hnum)))
			malloc_error(m, *s, READING);
	read(STDOUT_FILENO, buf, 1);
	if (!(check_key(m, s, buf)))
	{
		buf[1] = 0;
		*s = str_print_and_handle(m, *s, buf, m->p);
	}
	if (buf[0] == CTRL_C || buf[0] == CTRL_D)
		return (-1);
	if (buf[0] == '\n')
		return (0);
	// printf("s = [%s]\n", *s);
	return (1);
}

static char		*str_is_space(char *s)
{
	int		i;

	i = -1;
	while (s[++i])
		if (!(ft_isspace(s[i])))
			return (s);
	free(s);
	return (ft_strdup(""));
}

char	*line_read(t_main *m)
{
	char	*s;
	char	buf[2];
	
	s = ft_strdup("");
	// s[0] = 31;
	ft_bzero(buf, 2);
	while (reading(m, &s, buf) > 0);
	m->p->lpos = 0;
	m->p->hnum = 0;
	s = str_is_space(s);
	if (!(m->hist = history(ft_strdup(s), m->hist, m->p->hnum)))
		malloc_error(m, s, READING);
	set_term_cano(m->base_term);
	printf("s = [%s]\n", s);
	return (s);
}
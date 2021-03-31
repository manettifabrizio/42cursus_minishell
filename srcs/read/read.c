/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 13:06:59 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/30 14:34:40 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		reading(t_main *m, char **s, char *buf)
{
	read(STDOUT_FILENO, buf, 1);
	m->p->arr = split_keep(*s, '\n');
	if (!(check_key(m, s, buf)))
	{
		buf[1] = 0;
		*s = str_print_and_handle(*s, buf, m->p);
	}
	if (m->p->arr)
		ft_free_array(m->p->arr);
	if (buf[0] == CTRL_C)
		return (-1);
	if (buf[0] == '\n')
		return (0);
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
	// printf("s = %p\n", s);
	ft_bzero(buf, 2);
	if (!(m->hist = add_history(s, m->hist)))
		malloc_error(m, s, READING);
	// for (int i = 0; m->hist[i]; i++)
		// printf("m->hist[%d] = %p\n", i, m->hist[i]);
	while (reading(m, &s, buf) > 0)
		if (!(m->hist = history(s, m->hist, m->p->hnum)))
			malloc_error(m, s, READING);
	m->p->lpos = 0;
	m->p->hnum = 0;
	s = str_is_space(s);
	set_term_cano(m->base_term);
	return (s);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 13:06:59 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/10 19:26:18 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static char		*reading(t_main *m, char *s, char *buf)
{
	read(STDOUT_FILENO, buf, 1);
	if (!(check_key(m, &s, buf)))
		s = str_print_and_handle(m, s, buf, *(m->pos));
	return (s);
}

char	*line_read(t_main *m)
{
	t_uint	i;
	char	*s;
	char	buf[2];
	
	i = 0;
	ft_bzero(buf, 2);
	s = ft_strdup("");
	while (buf[0] != '\n')
	{
		if (!(m->hist = history(ft_strdup(s), m->hist, i++, m->pos->y)))
			malloc_error(m, s, READING);
		s = reading(m, s, buf);
		if (buf[0] == CTRL_C)
			break;
	}
	m->pos->x = 0;
	m->pos->y = 0;
	s = str_is_space(s);
	if (!(m->hist = history(ft_strdup(s), m->hist, 1, m->pos->y)))
		malloc_error(m, s, READING);
	set_term_cano(m->base_term);
	return (s);
}
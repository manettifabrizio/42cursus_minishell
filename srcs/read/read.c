/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 13:06:59 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/07 17:06:48 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*line_read(t_main *m)
{
	t_uint	i;
	char	*s;
	char	buf[2];
	
	i = 0;
	ft_bzero(buf, 2);
	if (!(s = malloc(1)))
		return (NULL);
	(s)[0] = '\0';
	while (buf[0] != '\n')
	{
		if (!(m->hist = history(ft_strdup(s), m->hist, i++, m->pos->y)))
			malloc_error(m, s, READING);
		read(STDOUT_FILENO, buf, 1);
		if (check_key(m, &s, buf))
		{
			if (buf[0] == CTRL_C)
				break;
		}
		else
			s = str_print_and_handle(m, s, buf, *(m->pos));
		// m->multi = multilines(s, buf);
	}
	m->pos->x = 0;
	m->pos->y = 0;
	// Set a[0] = s
	if (!(m->hist = history(ft_strdup(s), m->hist, 1, m->pos->y)))
		malloc_error(m, s, READING);
	config_term(0, m->base_term);
	return (s);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 13:06:59 by fmanetti          #+#    #+#             */
/*   Updated: 2021/02/27 20:39:33 by fmanetti         ###   ########.fr       */
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
		m->hist = history(s, m->hist, i++, m->pos->y);
		read(STDOUT_FILENO, buf, 1);
		if (check_key(&s, buf, m))
		{
			if (buf[0] == CTRL_C)
				break;
		}
		// without if backspace character is added to s
		else
			s = str_print_and_handle(s, buf, *(m->pos));
	}
	m->pos->x = 0;
	m->pos->y = 0;
	m->hist = history(s, m->hist, i, m->pos->y);
	set_term(0, m->base_term);
	return (s);
}
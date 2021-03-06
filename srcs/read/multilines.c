/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multilines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 12:09:55 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/06 12:48:27 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		how_many(char *s, char c)
{
	int		i;
	int		x;

	i = -1;
	x = 0;
	while (s[++i])
		if (s[i] == c)
			x++;
	return (x);
}

t_uint		multilines(t_main *m, char *s, char c)
{
	int		i;
	char	buf[2];

	i = 0;
	while (buf[0] != c)
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
			s = str_print_and_handle(m, s, buf, *(m->pos));
		// m->multi = multilines(s, buf);
	}
}

//	CTRL-D
// 	bash-3.2$ echo "asdafasdfsdf
// 	> bash: unexpected EOF while looking for matching `"'
// 	bash: syntax error: unexpected end of file
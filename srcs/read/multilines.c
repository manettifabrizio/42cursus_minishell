/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multilines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 12:21:37 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/18 17:21:29 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*ending(t_main *m, char *s, char *shist, t_uint type)
{
	free(s);
	set_term_cano(m->base_term);
	m->p->multi = 0;
	if (type == CTRL_C || type == CTRL_D)
	{
		if (!(m->hist = history(ft_strdup(shist), m->hist, m->p->hnum)))
			malloc_error(m, s, READING);
		if (type == CTRL_D)
		{
			printf("minish: unexpected EOF while looking for matching c\n");
			printf("minish: \e[0;31msyntax error\e[0m: unexpected end of file\n");
			m->exit_status = 258;
		}
		return (NULL);
	}
	return (shist);
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
	return (ending(m, s, shist, NO_BREAK));
}
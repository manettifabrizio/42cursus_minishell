/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multilines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 12:21:37 by fmanetti          #+#    #+#             */
/*   Updated: 2021/04/02 13:08:34 by fmanetti         ###   ########.fr       */
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
			malloc_error(m, NULL, NO_READING);
		if (type == CTRL_D)
		{
			status_error(m, NO_ERRNO, 258, "minish: unexpected EOF while \
looking for matching c");
			ft_putstr_fd("minish: ", STDERR_FILENO);
			ft_putstr_fd(SYNTAX_ERROR, STDERR_FILENO);
			ft_putstr_fd(": unexpected end of file\n", STDERR_FILENO); 
		}
		return (NULL);
	}
	return (shist);
}

static char		*join_multichar(char *shist, t_token_type type)
{
	if (type == SQUOTE || type == DQUOTE)
		shist = ft_strjoin_nl(shist, "\n");
	else if (type == BACKSLASH)
		shist[ft_strlen(shist) - 1] = '\0';
	else
		shist = ft_strjoin_nl(shist, " ");
	
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
	while ((ret = reading(m, &s, buf)) > 0)
		if (buf[0] == CTRL_D)
			return (ending(m, s, shist, buf[0]));
	shist = join_multichar(shist, type);
	shist = ft_strjoin_nl(shist, s);
	if (ret == -1)
		return (ending(m, s, shist, buf[0]));
	m->p->lpos = 0;
	m->p->hnum = 0;
	return (ending(m, s, shist, NO_BREAK));
}
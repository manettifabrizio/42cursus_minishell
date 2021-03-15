/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_print_and_handle.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 23:02:02 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/16 00:06:12 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		erase_and_print(char *s)
{
	ft_putstr(CLEAR_LINES);
	ft_putstr(SAVE_CURSOR);
	ft_putstr(s);
	ft_putstr(RESTORE_CURSOR);
}

static char		*inword_erase(char *s, t_cursor *p)
{
	int			i;
	t_uint		pos;
	char		*tmp;

	// printf("sa = [%s]\n", s);
	// ft_print_array(p->arr, "p");
	pos = (count_lines(s) == 1) ? p->lpos : p->spos;
	if (ft_strlen(s) == pos)
		return (s);
	i = ft_strlen(s) - pos;
	tmp = ft_substr(s, ft_strlen(s) - pos, pos);
	if (i > 0 && s[i - 1] != '\n')
		ft_putstr("\b \b");
	else if (s[i - 1] == '\n' && count_lines(s) > 1 && p->lnum > 0)
	{
		ft_putstr(CURSOR_UP);
		(p->lnum)--;
		// printf("lnum = %d\n", p->lnum);
		p->lpos = ft_strlen(p->arr[p->lnum]);
		// printf("p->multi = %d\n", p->multi);
		if (p->lnum == 0)
			p->lpos += (p->multi == 0) ? 9 : 2;
		end(p->arr[p->lnum], p);
	}
	s[i - 1] = '\0';
	erase_and_print(tmp);
	// printf("\ni = %d\n\ns[i - 1] = [%c]\n\ntmp = [%s]\n\ns = [%s]\n\n", i, s[i - 1], tmp, s);
	s = ft_strjoin_nl(s, tmp);
	free(tmp);
	return (s);
}

static char		*frankenstr(char *s, char *buf, char *s1)
{
	char	*s2;

	s2 = ft_substr(s, 0, ft_strlen(s) - ft_strlen(s1));
	s2 = ft_strjoin_nl(s2, buf);
	s2 = ft_strjoin_nl(s2, s1);
	free(s);
	return (s2);
}

static char		*inword_write(char *s, char *buf, t_cursor p)
{
	t_uint		pos;
	char		*tmp;

	pos = (count_lines(s) == 1) ? p.lpos : p.spos;
	tmp = ft_substr(s, ft_strlen(s) - pos, pos);
	ft_putchar(buf[0]);
	erase_and_print(tmp);
	s = frankenstr(s, buf, tmp);
	free(tmp);
	return (s);
}

char 	*str_print_and_handle(t_main *m, char *s, char *buf, t_cursor *p)
{
	if (buf[0] == '\n')
	{
		while ((p->lpos)--)
			ft_putstr(CURSOR_RIGHT);
		ft_putchar(buf[0]);
		return (s);
	}
	m->p->arr = split_keep(s, '\n');
	if (p->lpos == 0 && p->spos == 0 && (ft_isprint(buf[0])))
	{
		ft_putchar(buf[0]);
		s = ft_strjoin_nl(s, buf);
	}
	else if (p->lpos > 0 || p->spos > 0)
	{
		if (buf[0] == BACKSPACE)
			s = inword_erase(s, p);
		else
			s = inword_write(s, buf, *p);
	}
	// m->exit_status = 0;
	ft_free_array(m->p->arr);
	return (s);
}
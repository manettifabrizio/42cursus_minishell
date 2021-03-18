/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrows.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 13:35:38 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/16 10:32:10 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		arrow_up(char **s, char **h, t_cursor *p)
{
	int		i;

	i = -1;
	while (h[++i]);
	// printf("hnum = %d\n, i = %d\n", p->hnum, i);
	if ((p->hnum + 1) == (t_uint)i)
		return (1);
	if (p->hnum < (t_uint)(i - 1))
		(p->hnum)++;
	home(*s, p);
	ft_putstr(CLEAR_LINES);
	ft_putstr(h[p->hnum]);
	p->lpos = 0;
	p->spos = 0;
	p->lnum = count_lines(h[p->hnum]) - 1;
	if (p->hnum > 1)
		ft_free_array(p->arr);
	p->arr = split_keep(h[p->hnum], '\n'); // Problema con il fatto che se ci sono più \n di fila split ne considera 1
	free(*s);
	(*s) = ft_strdup(h[p->hnum]);
	return (1);
}

int		arrow_down(char **s, char **h, t_cursor *p)
{
	int		i;

	i = -1;
	while (h[++i]);
	home(*s, p);
	if (p->hnum > 0)
		(p->hnum)--;
	ft_putstr(CLEAR_LINES);
	ft_putstr(h[p->hnum]);
	p->lpos = 0;
	p->spos = 0;
	p->lnum = count_lines(h[p->hnum]) - 1;
	if (p->hnum > 1)
		ft_free_array(p->arr);
	p->arr = split_keep(h[p->hnum], '\n');
	free(*s);
	(*s) = ft_strdup(h[p->hnum]);
	return (1);
}

int		arrow_left(char *s, t_cursor *p)
{
	t_uint		len;

	// ft_print_array(p->arr, "a");
	// printf("s = %s\n", s);
	// printf("lnum = %d\n", p->lnum);
	// printf("p->lpos = %d lines = %d\n", p->lpos, count_lines(s));
	len = (count_lines(s) == 1) ? ft_strlen(s) : ft_strlen(p->arr[p->lnum]);
	// printf("p->lpos = %d\n lines = %d", p->lpos, count_lines(s));
	// printf("len = %d\n", len);
	if (p->lpos < len)
	{
		(p->lpos)++;
		ft_putstr(CURSOR_LEFT);
		if (count_lines(s) > 1)
			(p->spos)++;
	}
	else if (p->lpos == len && count_lines(s) > 1 && p->lnum > 0)
	{
		ft_putstr(CURSOR_UP);
		(p->spos)++;
		(p->lnum)--;
		p->lpos = ft_strlen(p->arr[p->lnum]);
		if (p->lnum == 0)
			p->lpos += (p->multi == 0) ? 9 : 2;
		// printf("multi = %d lpos = %d\n", p->multi, p->lpos);
		end(p->arr[p->lnum], p);
		p->lpos = 0;
	}
	return (1);
}

int		arrow_right(char *s, t_cursor *p)
{
	t_uint	nln;

	// ft_print_array(p->arr, "a");
	nln = count_lines(s) - 1;
	if (p->lpos > 0)
	{
		(p->lpos)--;
		ft_putstr(CURSOR_RIGHT);
		if (count_lines(s) > 1)
			(p->spos)--;
	}
	else if (p->lpos == 0 && nln > 0 && p->lnum < nln)
	{
		ft_putstr(CURSOR_DOWN);
		(p->spos)--;
		if (p->lnum == 0)
			home("minish $ ", p);
		p->lpos = 0;
		home(p->arr[p->lnum], p);
		(p->lnum)++;
		p->lpos = ft_strlen(p->arr[p->lnum]);
	}
	return (1);
}
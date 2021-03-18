/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_word_or_column.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 11:55:44 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/17 19:59:01 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		word_right(char *s, t_cursor *p)
{
	t_uint	i;
	t_uint	len;
	
	len = ft_strlen(s);
	i = len - p->spos;
	if (!len || i == len)
		return (1);
	if (ft_isalpha(s[i]) || ft_isdigit(s[i]))
		while ((ft_isalpha(s[i]) || ft_isdigit(s[i])) && p->spos > 0)
		{
			arrow_right(s, p);
			i++;
		}
	while (!(ft_isalpha(s[i]) || ft_isdigit(s[i])) && p->spos > 0)
	{
		arrow_right(s, p); 
		i++;
	}
	return (1);	
}

int		word_left(char *s, t_cursor *p)
{
	int		i;
	t_uint	len;
	
	len = ft_strlen(s);
	i = (len - 1) - p->spos;
	if (!len || i < 1)
		return (1);
	arrow_left(s, p);
	if (!(ft_isalpha(s[i]) || ft_isdigit(s[i])))
		while (!(ft_isalpha(s[i]) || ft_isdigit(s[i])) && p->spos < len)
		{
			arrow_left(s, p);
			i--;
		}
	while ((ft_isalpha(s[i]) || ft_isdigit(s[i])) && p->spos < len)
	{
		arrow_left(s, p);
		i--;
		if (i > 0 && !(ft_isalpha(s[i - 1]) || ft_isdigit(s[i - 1])))
			break;
	}
	return (1);	
}

int		column_up(char *s, t_cursor *p)
{
	t_uint lpos;

	if (p->lnum > 0)
	{
		lpos = p->lpos;
		if (lpos > ft_strlen(p->arr[p->lnum - 1]))
			lpos = ft_strlen(p->arr[p->lnum - 1]);
		arrow_left(s, p);
		while (p->lpos != lpos)
			arrow_left(s, p);
	}
	return (1);
}

int		column_down(char *s, t_cursor *p)
{
	t_uint lpos;

	if (p->lnum < (count_lines(s) - 1))
	{
		lpos = p->lpos;
		if (lpos > ft_strlen(p->arr[p->lnum + 1]))
		{	
			lpos = ft_strlen(p->arr[p->lnum + 1]);
			arrow_right(s, p);
			while (p->lpos != lpos)
				arrow_right(s, p);
		}
		arrow_right(s, p);
		while (p->lpos != lpos)
			arrow_right(s, p);
	}
	return (1);
}
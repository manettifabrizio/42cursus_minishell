/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 11:55:44 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/04 18:13:13 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		word_right(char *s, t_cursor *pos)
{
	t_uint	i;
	t_uint	len;
	
	len = ft_strlen(s);
	i = len - pos->x;
	if (!len || i == len)
		return (1);
	if (ft_isalpha(s[i]) || ft_isdigit(s[i]))
		while (s[i] != ' ' && pos->x > 0)
		{
			arrow_right(pos);
			i++;
		}
	while (!(ft_isalpha(s[i]) || ft_isdigit(s[i])) && pos->x > 0)
	{
		arrow_right(pos); 
		i++;
	}
	return (1);	
}

int		word_left(char *s, t_cursor *pos)
{
	int		i;
	t_uint	len;
	
	len = ft_strlen(s);
	i = (len - 1) - pos->x;
	if (!len || i < 1)
		return (1);
	arrow_left(s, pos);
	if (!(ft_isalpha(s[i]) || ft_isdigit(s[i])))
		while (!(ft_isalpha(s[i]) || ft_isdigit(s[i])) && pos->x < len)
		{
			arrow_left(s, pos);
			i--;
		}
	while ((ft_isalpha(s[i]) || ft_isdigit(s[i])) && pos->x < len)
	{
		arrow_left(s, pos);
		i--;
		if (i > 0 && !(ft_isalpha(s[i - 1]) || ft_isdigit(s[i - 1])))
			break;
	}
	return (1);	
}
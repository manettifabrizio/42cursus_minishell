/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   home_end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 20:12:50 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/15 12:41:57 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		home(char *s, t_cursor *p)
{
	int		i;

	// printf("len = %zu\n", ft_strlen(s));
	if (count_lines(s) == 1)
		i = ft_strlen(s) - p->lpos;
	else
		i = ft_strlen(s) - p->spos;
	// printf("i = %d\n", i);
	while (i--)
		arrow_left(s, p);
	return (1);
}

int		end(char *s, t_cursor *p)
{
	int		i;

	if (count_lines(s) == 1)
		i = p->lpos;
	else
		i = p->spos;
	while (i--)
		arrow_right(s, p);
	return (1);
}

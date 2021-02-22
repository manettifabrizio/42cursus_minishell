/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_print_and_handle.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 23:02:02 by fmanetti          #+#    #+#             */
/*   Updated: 2021/02/22 23:08:14 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*frankenstr(char *s, char *buf, char *s1)
{
	char *s2;

	s2 = ft_substr(s, 0, ft_strlen(s) - ft_strlen(s1));
	s2 = ft_strjoin_nl(s2, buf);
	s2 = ft_strjoin_nl(s2, s1);
	free(s);
	return (s2);
}

static char		*inword_erase()
{}

static char		*inword_write(char *s, char *buf, int len)
{
	char	*tmp;

	tmp = ft_substr(s, ft_strlen(s) - len, len);
	ft_putchar(buf[0]);
	ft_putstr(tmp);
	while (len--)
		ft_putstr(CURSOR_LEFT);
	s = frankenstr(s, buf, tmp);
	free(tmp);
	return (s);
}

char 	*str_print_and_handle(char *s, char *buf, t_cursor *pos)
{
	int		len;
	char	*s1;

	len = pos->x;
	if (buf[0] == '\n')
	{
		while (len--)
			ft_putstr(CURSOR_RIGHT);
		ft_putchar(buf[0]);
		return (s);
	}
	if (pos->x == 0)
	{
		ft_putchar(buf[0]);
		s = ft_strjoin_nl(s, buf);
	}
	else
		if (buf[0] == BACKSPACE)
			s = inword_erase();
		else
			s = inword_write(s, buf, len);
	// printf("*s = %s\n", s);
	return (s);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 13:06:59 by fmanetti          #+#    #+#             */
/*   Updated: 2021/02/22 22:57:46 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		check_key(char *s, char c, struct termios *base_term,
	t_cursor *pos)
{
	if (c == CTRL_C)
		return (control_c(s));
	if (c == CTRL_D && s[0] == '\0')
		return (control_d(base_term));
	if (c == BACKSPACE)
		return (backspace(s, pos));
	if (c == ESCAPE)
	{
		read(STDOUT_FILENO, &c, 1);
		if (c == '[')
		{
			read(STDOUT_FILENO, &c, 1);
			if (c == ARR_UP)
				return (arrow_up());
			if (c == ARR_DOWN)
				return (arrow_down());
			if (c == ARR_RIGHT)
				return (arrow_right(pos));
			if (c == ARR_LEFT)
				return (arrow_left(s, pos));
		}
	}
	return (0);
}

char	**line_read(struct termios *base_term, t_cursor *pos)
{
	char	*str;
	char	buf[2];
	
	buf[0] = '\0';
	if (!(str = malloc(1)))
			return (NULL);
	(str)[0] = '\0';
	while (buf[0] != '\n')
	{
		read(STDOUT_FILENO, buf, 1);
		buf[1] = '\0';
		if (check_key(str, buf[0], base_term, pos))
		{
			if (buf[0] == CTRL_C)
				break;
		}
		// without if backspace character is added to str
		else
			str = str_print_and_handle(str, buf, pos);
	}
	pos->x = 0;
	// printf("s = %s\n", str);
	// if ((ft_strlen(str) - 1) >= 0)
	// 	(str)[ft_strlen(str) - 1] = '\0';
	set_term(0, base_term);
	return (ft_split(str, ' '));
}
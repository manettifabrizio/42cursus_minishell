/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 13:06:59 by fmanetti          #+#    #+#             */
/*   Updated: 2021/02/25 19:31:36 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**line_read(struct termios *base_term, t_cursor *pos)
{
	char	*str;
	char	buf[2];
	
	ft_bzero(buf, 2);
	if (!(str = malloc(1)))
		return (NULL);
	(str)[0] = '\0';
	while (buf[0] != '\n')
	{
		read(STDOUT_FILENO, buf, 1);
		if (check_key(str, buf, base_term, pos))
		{
			if (buf[0] == CTRL_C)
				break;
		}
		// without if backspace character is added to str
		else
			str = str_print_and_handle(str, buf, *pos);
	}
	pos->x = 0;
	// printf("s = %s\n", str);
	// if ((ft_strlen(str) - 1) >= 0)
	// 	(str)[ft_strlen(str) - 1] = '\0';
	set_term(0, base_term);
	return (ft_split(str, ' '));
}